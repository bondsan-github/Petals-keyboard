#include "..\headers\gui_microsoft.h"

//#include <cassert>
#include <sstream>
#include <format>

#include "..\headers\locate.h"
#include "..\headers\window_messages.h"

namespace hid
{
    gui_microsoft::gui_microsoft( void )    
    {
        //OutputDebugString( L"gui_microsoft::default constructor\n" );
    }

    void gui_microsoft::initialise( const HINSTANCE in_instance , const LPWSTR in_parameters , const int in_show_flags )
    {
        //OutputDebugString( L"gui_microsoft::initialise\n" );

        instance = in_instance; parameters = in_parameters; show_flags = in_show_flags;

        locate::set_windows( this );

        window_class.cbSize = sizeof( WNDCLASSEX );

        window_class.style         = class_style;
        window_class.lpfnWndProc   = window_setup;
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
        atom = RegisterClassExW( & window_class );
        //error( L"register class ex" );
        
        /*
        RECT desktop {};
        RECT size    {};
        GetWindowRect( GetDesktopWindow() , & desktop );

        int result = GetDpiForWindow( GetDesktopWindow() );

        const enum class dpi_aware : int { invalid = -1 , unaware , system , per_monitor }; // (UINT) -1
        
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

        /*
        // position window to centre of screen
        desktop_size.width  = static_cast< uint >( desktop.right ); // static_cast from long to float
        desktop_size.height = static_cast< uint >( desktop.bottom );

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
        */

        window_principle = CreateWindowExW( style_extra ,
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

        //if( window_principle == nullptr ) error_exit( L"create window ex" );
        SetLayeredWindowAttributes( window_principle ,
                                    0 , // no color key     
                                    230 , // alpha value
                                    LWA_ALPHA );

        //ShowWindow( window_principle , SW_MAXIMIZE );
        //UpdateWindow( window_principle );
    }

    RECT gui_microsoft::get_client_rectangle()
    {
        RECT client {};

        GetWindowRect( window_principle , &client );

        return client;
    }

    HWND gui_microsoft::get_window() const
    {
        return window_principle;
    }

    uint gui_microsoft::update()
    {
        
        while( PeekMessageW( &window_message , nullptr , 0 , 0 , PM_REMOVE ) )
        //while( GetMessageW( &window_message , 0 , 0 , 0 ) )
        {
            TranslateMessage( &window_message );
            DispatchMessage( &window_message );

            if( window_message.message == WM_QUIT ) 
            {
                locate::get_application().set_state( states::ending );
                return 0;
            }
        }
        return window_message.message;
    }

    LRESULT CALLBACK gui_microsoft::window_setup( HWND in_window , UINT message , WPARAM w_param , LPARAM l_param )
    {
        if( message == WM_NCCREATE )
        {
            //OutputDebugString( L"window_setup::WM_NCCREATE\n" );

            const CREATESTRUCT * const create_ptr = reinterpret_cast< CREATESTRUCT * >( l_param );
            
            gui_microsoft * const class_pointer = static_cast< gui_microsoft * >( create_ptr->lpCreateParams );

            SetWindowLongPtr( in_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( class_pointer ) );
            SetWindowLongPtr( in_window , GWLP_WNDPROC , reinterpret_cast< LONG_PTR >( &gui_microsoft::message_handler ) );

            return class_pointer->message_handler( in_window , message , w_param , l_param );
        }

        //static window_messages messages;
        //std::wstring win_message = messages.message_text(message);
        //OutputDebugString( win_message.c_str() );

        return DefWindowProc( in_window , message , w_param , l_param );
    }

    LRESULT CALLBACK gui_microsoft::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
    {
        
        /*
        static window_messages messages;
        std::wstring win_message = messages.message_text( message );
        OutputDebugString( win_message.c_str() );
        */

        switch( message )
        {
            //case WM_CREATE: { } break;

            case WM_DESTROY:
            {
                PostQuitMessage( 0 );
                return 0;
            } break;

            case WM_INPUT:
            {
                RAWINPUT raw_input;// { nullptr };
                uint raw_input_size { 0 };
                
                GetRawInputData( ( HRAWINPUT )lParam , RID_INPUT , 0 , &raw_input_size , sizeof( RAWINPUTHEADER ) );
                GetRawInputData( ( HRAWINPUT )lParam , RID_INPUT , &raw_input , &raw_input_size , sizeof( RAWINPUTHEADER ) );

                //uint hid_data_size = raw_input.data.hid.dwCount * raw_input.data.hid.dwSizeHid;
                //uchar * data = new uchar[ hid_data_size ];
                //memmove(data, raw_input.data.hid.bRawData, hid_data_size );
                locate::get_input_devices().update_devices( raw_input );

                //std::string message = "\n" + std::to_string(data[hid_data_size]);
                //OutputDebugStringA( message.c_str() );

                //delete[] data;
                return 0;
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
               
            } break;
            */

            //case WM_PAINT:
            //{
                // UpdateLayeredWindow
                /*Hit testing of a layered window is based on the shape and transparency of the window.
                This means that the areas of the window that are color-keyed or whose alpha value is zero
                will let the mouse messages through.
                However, if the layered window has the WS_EX_TRANSPARENT extended window style,
                the shape of the layered window will be ignored
                and the mouse events will be passed to other windows underneath the layered window.*/
                //https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/december/windows-with-c-layered-windows-with-direct2d

            //} break;

            //case WM_SIZE:
            //{
               //graphics.resize();
            //} break;

            case WM_KEYDOWN:
            {
                // input.key_down( wParam );

                switch( wParam )
                {
                    case VK_ESCAPE:
                    {
                        PostQuitMessage( 0 );
                    } break;

                    //case VK_SPACE:
                    //{
                        //for( auto & device : input )
                          //  device.display_information();
                    //} break;
                }
            } // WM_KEYDOWN

        } // switch( message )

       return DefWindowProc( in_window , message , wParam , lParam );

    } // message_handler

    gui_microsoft::~gui_microsoft()
    {
        //OutputDebugString( L"gui_microsoft::de-constructor\n" );

        //DestroyWindow( window_principle );
        //UnregisterClassW( class_name , instance );
    }

} // namespace hid


//GetClassInfo( hInst , thisClassName , &wincl ))

//SetWindowPos
      //HMONITOR monitor = MonitorFromWindow( GetModuleHandle(0) , MONITOR_DEFAULTTONEAREST);
      //MONITORINFO monitor_info {};
      //GetMonitorInfo( monitor , & monitor_info );
      //S_OK