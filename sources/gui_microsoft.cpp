#include "..\headers\gui_microsoft.h"

//#include <cassert>
#include <sstream>
#include <format>

#include "..\headers\locate.h"
#include "..\headers\window_messages.h"
#include "..\headers\utility.h"

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

        WNDCLASS wincl;

        GetClassInfo( in_instance , class_name , &wincl );

        window_class.cbSize = sizeof( WNDCLASSEX );

        window_class.style         = class_style;
        window_class.lpfnWndProc   = &window_setup;
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

        ShowWindow( window_principle , SW_MAXIMIZE ); // set show state
        UpdateWindow( window_principle ); // send WM_PAINT message
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

    void gui_microsoft::message_loop()
    {
        // get message and not peek message as to stay idle until touch input
        while( GetMessageW( &window_message , 0 , 0 , 0 ) != 0 ) // or > 0 // Microsoft BOOL = int
        {
            TranslateMessage( &window_message );
            DispatchMessageW( &window_message );

            //locate::get_devices().update();
            locate::get_graphics().draw_begin();
            locate::get_input_devices().draw();
            locate::get_graphics().draw_end();
        }
    }

    /*/void gui_microsoft::message_loop()
    {
        MSG msg {};

        while( msg.message != WM_QUIT )
        {
            if( PeekMessage( &msg , NULL , 0U , 0U , PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        }
    }*/

    long long __stdcall gui_microsoft::window_setup( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter )
    {
        gui_microsoft * class_pointer {nullptr};
        // use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
        if( message == WM_NCCREATE )
        //if( message == WM_CREATE )
        {
            CREATESTRUCT * create_struct = reinterpret_cast< CREATESTRUCTW * >( l_parameter );
            //gui_microsoft * class_pointer = static_cast< gui_microsoft * >( create_struct->lpCreateParams );
            class_pointer = static_cast< gui_microsoft * >( create_struct->lpCreateParams );

            // set WinAPI-managed user data to store ptr to window class
            SetWindowLongPtrW( in_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( class_pointer ) );

            // set message proc to normal (non-setup) handler now that setup is finished
            SetWindowLongPtrW( in_window , GWLP_WNDPROC , reinterpret_cast< LONG_PTR >( &gui_microsoft::message_handler ) );
            //SetWindowLongPtrW( in_window , GWLP_WNDPROC , (LONG_PTR)&gui_microsoft::message_handler  );

            // forward message to window class message handler
            return class_pointer->message_handler( in_window , message , w_parameter , l_parameter );
        }
            
        //static window_messages messages;
        //std::wstring win_message = messages.message_text( message );
        //OutputDebugStringW( win_message.c_str() );

        // if there is a message before the WM_NCCREATE message, handle with default handler
        return DefWindowProcW( in_window , message , w_parameter , l_parameter );
    }

    long long __stdcall gui_microsoft::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
    {
        //OutputDebugString( L"\nmessage_handler::" );

        //static window_messages messages;
        //std::wstring win_message = messages.message_text( message );
        //OutputDebugStringW( win_message.c_str() );

        //https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/multimedia/Direct2D/SimpleDirect2DApplication/SimpleDirect2dApplication.cpp

        gui_microsoft * class_pointer = reinterpret_cast< gui_microsoft * >( static_cast< LONG_PTR >( GetWindowLongPtrW( in_window , GWLP_USERDATA ) ) );

        //fprintf(stderr, "\nmessages");

        switch( message )
        {
            //case WM_CREATE: { } break;

            case WM_CLOSE: 
            { 
                //"are you sure you want to exit application?" 
                //if( MessageBox( in_window , L"Confirm exit" , L"Multiple touch" , MB_YESNOCANCEL ) == IDYES ) DestroyWindow( in_window );
                //else return 0;
            } break;

            case WM_DESTROY:
            {
                PostQuitMessage( 0 );
                class_pointer->window_principle = nullptr;
                //result = 1;
                class_pointer->message_handled = true;

            } break;

            case WM_INPUT:
            //case WM_TOUCH:
            {
                std::wstring message{};
                RAWINPUT     raw_input {};
                RAWINPUT *   raw_input_buffer { nullptr };

                uint raw_input_size { 0 };
                uint reports_read   { 0 };
                uint header_size    = sizeof RAWINPUTHEADER;
                uint bytes_copied   { 0 };

                //uint hid_buffer_amount { 0 };
                //HidD_GetNumInputBuffers( file_handle , &hid_buffer_amount );

                //single report read 
                //GetRawInputData( reinterpret_cast< HRAWINPUT >(lParam) , RID_INPUT , 0 , &raw_input_size , header_size );
                //GetRawInputData( reinterpret_cast< HRAWINPUT >(lParam) , RID_INPUT , 0 , &class_pointer->raw_input_size , class_pointer->header_size );
                //bytes_copied = GetRawInputData( reinterpret_cast< HRAWINPUT >(lParam) , RID_INPUT , &raw_input , &raw_input_size , header_size );
                //bytes_copied = 
                //GetRawInputData( reinterpret_cast< HRAWINPUT >(lParam) , RID_INPUT , &class_pointer->raw_input , &class_pointer->raw_input_size , class_pointer->header_size );
                //locate::get_input_devices().update_devices( raw_input );

                // errorcode = max unsigned int? 4294967295
                
                //multiple report read
                //https://learn.microsoft.com/en-gb/windows/win32/inputdev/using-raw-input
                //Sleep( 1000 );

                uint result = GetRawInputBuffer( 0 , &raw_input_size , header_size );

                //if( result != (UINT)-1 && raw_input_size > 0 ) //uint-1=0xffff'fffff
                //{
                    raw_input_size *= 8;
                    message += L"\nbuffer_size bytes:" + std::to_wstring( raw_input_size );

                    reports_read = GetRawInputBuffer( raw_input_buffer , &raw_input_size , header_size );
                    message += L"\nreports read:" + std::to_wstring( reports_read );
                    //if( reports_read != (UINT)-1 && reports_read > 0 )
                    //{
                        raw_input_buffer = new RAWINPUT[ raw_input_size ];

                        locate::get_input_devices().update_devices_buffered( raw_input_buffer , reports_read );

                        delete[] raw_input_buffer;
                    //}
                    //else print_error( L"\nget input buffer error: " );
                //}
                //else print_error( L"\nget buffer size error: " ); 
                
                //result = 0;
                class_pointer->message_handled = true;

                OutputDebugStringW( message.c_str() );

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

            /*
            case WM_PAINT:
            {
                BeginPaint( in_window , &class_pointer->paint );
                // UpdateLayeredWindow
                //Hit testing of a layered window is based on the shape and transparency of the window.
                //This means that the areas of the window that are color-keyed or whose alpha value is zero
                //will let the mouse messages through.
                //However, if the layered window has the WS_EX_TRANSPARENT extended window style,
                //the shape of the layered window will be ignored
                //and the mouse events will be passed to other windows underneath the layered window.
                //https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/december/windows-with-c-layered-windows-with-direct2d
                if( class_pointer->graphics )
                {
                    class_pointer->graphics->draw_begin();
                    locate::get_input_devices().draw();
                    class_pointer->graphics->draw_end();
                }
                EndPaint( in_window , &class_pointer->paint );

            } break;
            */

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

            } break;// WM_KEYDOWN

            //default: return DefWindowProc( in_window , message , wParam , lParam );

        } // switch( message )
        
        if( not class_pointer->message_handled ) return DefWindowProc( in_window , message , wParam , lParam );

        return class_pointer->result;

    } // message_handler

    gui_microsoft::~gui_microsoft()
    {
        //OutputDebugString( L"gui_microsoft::de-constructor\n" );

        DestroyWindow( window_principle );
        UnregisterClassW( class_name , instance );
    }

} // namespace hid


//GetClassInfo( hInst , thisClassName , &wincl ))

//SetWindowPos
      //HMONITOR monitor = MonitorFromWindow( GetModuleHandle(0) , MONITOR_DEFAULTTONEAREST);
      //MONITORINFO monitor_info {};
      //GetMonitorInfo( monitor , & monitor_info );
      //S_OK