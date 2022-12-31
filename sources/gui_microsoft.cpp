#include "..\headers\gui_microsoft.h"

#include <cassert>
//#include <windows.h>
#include <sstream>

#include "..\headers\locate.h"

namespace hid
{
    //gui_microsoft::gui_microsoft( void ) { OutputDebugString( L"\n gui_microsoft::default constructor" ); }

    gui_microsoft::gui_microsoft( const HINSTANCE in_instance , const LPWSTR in_parameters , const int in_show_flags )
    {
        OutputDebugString( L"\n gui_microsoft::parameterised constructor" );

        instance = in_instance; parameters = in_parameters; show_flags = in_show_flags;

        locate::set_windows( this );

        window_class.cbSize = sizeof( WNDCLASSEX );

        window_class.style         = class_style;
        window_class.lpfnWndProc   = gui_microsoft::main_window_process;
        window_class.hInstance     = instance; //instance that contains the window procedure for the class.
        window_class.lpszClassName = class_name;

        window_class.cbClsExtra    = 0; // extra memory after structure
        window_class.cbWndExtra    = 0; // extra bytes following the window instance.
        window_class.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 ); //( HBRUSH ) ( COLOR_GRAYTEXT + 1 );		//brush_background;
        window_class.hCursor       = LoadCursor( nullptr , IDC_ARROW );
        window_class.hIcon         = 0;
        window_class.hIconSm       = 0;
        window_class.lpszMenuName  = 0;

        /*
        wcx.hIconSm = LoadImage( hinstance , // small class icon 
                                 MAKEINTRESOURCE( 5 ) ,
                                 IMAGE_ICON ,
                                 GetSystemMetrics( SM_CXSMICON ) ,
                                 GetSystemMetrics( SM_CYSMICON ) ,
                                 LR_DEFAULTCOLOR );
        */
        ATOM atom {};
        atom = RegisterClassEx( & window_class );
        //error( L"register class ex" );
        
        RECT desktop {};
        RECT size    {};

        GetWindowRect( GetDesktopWindow() , & desktop );

        /*
        int result = GetDpiForWindow( GetDesktopWindow() );

        enum class dpi_aware : int { invalid = -1 , unaware , system , per_monitor }; // (UINT) -1
        
        if( result > 2 )
        {
            window_dpi = result;
        }
        else
        {
            //if( result == -1 ) PostQuitMessage(0);
            if( result == 0 ) 
            {
            window_dpi = 96;
            }
            else if( result == 1)
            { }
                UINT GetDpiForSystem();
        }
        */

        // position window to centre of screen
        desktop_size.width  = desktop.right; // static_cast from long to float
        desktop_size.height = desktop.bottom;

        desktop_center.x = static_cast< int >( desktop_size.width  / 2.0f );
        desktop_center.y = static_cast< int >( desktop_size.height / 2.0f );
        
        client_size_half.width  = static_cast< int >( client_size.width  / 2.0f );
        client_size_half.height = static_cast< int >( client_size.height / 2.0f );

        position_center.x = desktop_center.x;
        position_center.y = desktop_center.y;

        position_top_left.x = position_center.x - client_size_half.width;
        position_top_left.y = position_center.y - client_size_half.height;

        //size = { 0l, 0l, static_cast< long >( width ), static_cast< long >( height ) };
        //AdjustWindowRect( & size , WS_OVERLAPPEDWINDOW , FALSE );

        window_principle = CreateWindowEx( style_extra ,
                                           class_name ,
                                           title_text ,
                                           style ,
                                           position_top_left.x ,
                                           position_top_left.y ,
                                           client_size.width ,
                                           client_size.height ,
                                           parent_window , 
                                           menu ,
                                           instance ,
                                           this );

        //assert( window_principle != nullptr );

        //if( window_principle == nullptr ) error( L"create window ex" );

        //ShowWindow( window_principle , SW_MAXIMIZE );
        //UpdateWindow( window_principle );

        SetLayeredWindowAttributes( window_principle ,
                                    0 , // no color key     
                                    230 , // alpha value
                                    LWA_ALPHA );

        //message_loop();
    }

    //gui_microsoft::~gui_microsoft() { OutputDebugString( L"\n gui_microsoft::de-constructor" ); }

    HWND gui_microsoft::get_window() const
    {
        return window_principle;
    }

    int gui_microsoft::message_loop()
    {
        while( GetMessage( &window_message , 0 , 0 , 0 ) )
        {
            TranslateMessage( &window_message );
            DispatchMessage( &window_message );
        }

        return window_message.message;
    }

    // to forward Windows messages from a global window procedure to member function window procedure
    // because we cannot assign a member function to WNDCLASS::lpfnWndProc.
    LRESULT CALLBACK gui_microsoft::main_window_process( HWND in_window , UINT message , WPARAM w_param , LPARAM l_param )
    {
        // If we are creating the window, set the window_ptr to the instance of CAppWindow associated with the window as the HWND's user data.
        // That way when we get messages besides WM_CREATE we can call the instance's WndProc and reference non-static member variables.

        if( message == WM_NCCREATE )
        {
            OutputDebugString( L"\n  main_window_process() - WM_NCCREATE" );

            CREATESTRUCT * create_ptr = reinterpret_cast< CREATESTRUCT * >( l_param );

            this_pointer = static_cast< gui_microsoft * >( create_ptr->lpCreateParams );

            SetWindowLongPtr( in_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( this_pointer ) );

            //this_ptr->window_ptr = window_ptr;   
        }
        else
        {
            //string wmessage { L"\n  main_window_process() - message = 0x" };
            //wmessage += to_wstring(message);
            //OutputDebugString( wmessage.c_str() );

            this_pointer = reinterpret_cast< gui_microsoft * >( GetWindowLongPtr( in_window , GWLP_USERDATA ) );
        }

        if( this_pointer )
            return this_pointer->message_handler( in_window , message , w_param , l_param );

        return DefWindowProc( in_window , message , w_param , l_param );
    }

    LRESULT gui_microsoft::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
    {
        switch( message )
        {
            case WM_CREATE:
            {
            } break;

            /*
            * https://docs.microsoft.com/en-us/windows/win32/hidpi/wm-dpichanged
            case WM_DPICHANGED:
            {
                g_dpi = HIWORD( wParam );
                UpdateDpiDependentFontsAndResources();

                RECT * const prcNewWindow = ( RECT * ) lParam;
                SetWindowPos( hWnd ,
                              NULL ,
                              prcNewWindow->left ,
                              prcNewWindow->top ,
                              prcNewWindow->right - prcNewWindow->left ,
                              prcNewWindow->bottom - prcNewWindow->top ,
                              SWP_NOZORDER | SWP_NOACTIVATE );
                break;
            }
            */
            case WM_DESTROY:
            {
                PostQuitMessage( 0 );
            } break;

            case WM_PAINT:
            {
                // UpdateLayeredWindow
                /*Hit testing of a layered window is based on the shape and transparency of the window.
                This means that the areas of the window that are color-keyed or whose alpha value is zero
                will let the mouse messages through.
                However, if the layered window has the WS_EX_TRANSPARENT extended window style,
                the shape of the layered window will be ignored
                and the mouse events will be passed to other windows underneath the layered window.*/
                //https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/december/windows-with-c-layered-windows-with-direct2d

                locate::get_graphics().draw();

            } break;

            case WM_SIZE:
            {
               //graphics.resize();
            } break;

            case WM_KEYDOWN:
            {
                // input.key_down( wParam );

                switch( wParam )
                {
                    case VK_ESCAPE:
                    {
                        PostQuitMessage( 0 );
                        //DestroyWindow( in_window );
                    } break;

                    case VK_SPACE:
                    {
                        //for( auto & device : input )
                          //  device.display_information();
                    } break;
                }
            } // WM_KEYDOWN

        } // switch( message )

        return DefWindowProc( in_window , message , wParam , lParam );

    } // message_handler

} // namespace hid


//GetClassInfo( hInst , thisClassName , &wincl ))

//SetWindowPos
      //HMONITOR monitor = MonitorFromWindow( GetModuleHandle(0) , MONITOR_DEFAULTTONEAREST);
      //MONITORINFO monitor_info {};
      //GetMonitorInfo( monitor , & monitor_info );
      //S_OK