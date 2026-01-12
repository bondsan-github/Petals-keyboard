#include "Operating system\MSWindows.h"

#include "Operating system\MSWindows messages.h"
#include "Application.h"
#include "Output\Logging.h"

//#include <winuser.h>
//#include <wingdi.h>
#include <sstream>
#include <iomanip>

typedef unsigned __int64 QWORD; // 64-bit integer

MSWindows::MSWindows( Application * application )
: application( application )
{
    //OutputDebugString( L"\n MSWindows::MSWindows()" );
}

HWND MSWindows::initialise( Size client_size )
{
    if( client_size ) client_size_ = client_size;
    else fullscreen = true;

    instance = GetModuleHandleW( 0 );

    window_class.cbSize        = sizeof( WNDCLASSEX );
    window_class.style         = class_style;
    window_class.lpfnWndProc   = MSWindows::message_handler;
    window_class.hInstance     = instance; //instance that contains the window procedure for the class.
    window_class.lpszClassName = class_name;

    window_class.cbClsExtra    = 0; // extra memory after structure
    window_class.cbWndExtra    = 0; // extra bytes following the window instance.
    window_class.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_WINDOW + 1 ); //brush_background;
    window_class.hCursor       = LoadCursorW( nullptr , IDC_ARROW );
    window_class.hIcon         = LoadIconW( instance, L"IDI_ICON"); // predefined app. icon
    window_class.hIconSm       = LoadIconW( instance, L"IDI_ICON"); // predefined arrow 
    window_class.lpszMenuName  = nullptr;

    /* wcx.hIconSm = LoadImage( hinstance , // small class icon 
                                MAKEINTRESOURCE( 5 ) ,
                                IMAGE_ICON ,
                                GetSystemMetrics( SM_CXSMICON ) ,
                                GetSystemMetrics( SM_CYSMICON ) ,
                                LR_DEFAULTCOLOR );  */
    ATOM atom {};
    
    atom = RegisterClassExW( & window_class );

    if( ! atom ) error_exit( L"Unable to register class ex." );
    
    RECT desktop {};

    GetWindowRect( GetDesktopWindow() , & desktop );

    //int screen_width = GetSystemMetrics( SM_CXSCREEN );
    //int screen_height = GetSystemMetrics( SM_CYSCREEN );
    
    int result = GetDpiForWindow( GetDesktopWindow() );

    if( fullscreen )
    {
        client_size_.width( desktop.right - desktop.left );
        client_size_.height( desktop.bottom - desktop.top );
    }
    else
    {
        position_top_left.x( ( desktop.right - client_size_.width() ) / 2 );
        position_top_left.y( ( desktop.bottom - client_size_.height() ) / 2 );
    }
    
    /*
    const enum class dpi_aware : int { invalid = -1 , unaware , system , per_monitor }; // (UINT) -1
    if( result > 2 ) { window_dpi = result; }
    else {
        //if( result == -1 ) PostQuitMessage(0);
        if( result == 0 ) { window_dpi = 96; }
        else if( result == 1) { }
    UINT GetDpiForSystem } */

    RECT adjusted_window_size {};

    adjusted_window_size.right  = static_cast< long >( client_size_.width() );
    adjusted_window_size.bottom = static_cast< long >( client_size_.height() );

    //bool adjusted = AdjustWindowRect( & adjusted_window_size , WS_OVERLAPPEDWINDOW , FALSE );
        
    window_principle = CreateWindowExW( transparent ? style_extra_transparent : style_extra ,
                                        class_name ,
                                        title_text ,
                                        transparent ? window_style_transparent : window_style ,
                                        position_top_left.x() ,
                                        position_top_left.y() ,
                                        client_size_.width() ,
                                        client_size_.height() ,
                                        nullptr, //HWND_DESKTOP ,
                                        menu ,
                                        instance ,
                                        application ); // GWLP_USERDATA

    if( ! window_principle ) error_exit( L"Unable create principle window." );
 
    ShowWindow( window_principle , SW_SHOWNORMAL ); // set show state
    
    //window_rectangles();

    return window_principle;
}

void MSWindows::window_size_changed( uint width , uint height )
{
    Size new_size( width , height );

    if( new_size != client_size_ )
    {
        //application->window_size_change( width , height );
    }
    else
    {
        return;
    }
}

RECT MSWindows::client_position()
{
    RECT position {};

    // pixel at [ right, bottom ] lies immediately outside the rectangle.
    GetWindowRect( window_principle , & position );

    return position;
}

Size MSWindows::client_size()
{
    RECT area {};
    
    GetClientRect( window_principle , &area);

    return { area.right - area.left , area.bottom - area.top };
}

HWND MSWindows::window()
{
    return window_principle;
}

void MSWindows::process_input() //lParam
{
    uint header_size     = sizeof( RAWINPUTHEADER );
    uint buffer_size     = 0;
    uint result          = 0;
    //std::vector< RAWINPUT > raw_input;
    std::wstring message;

    //  minimum required buffer size in bytes
    result = GetRawInputBuffer( 0 , &buffer_size , header_size );
    //
   
    if( buffer_size > 0 )
    {
        buffer_size *= 16;

        PRAWINPUT pRawInput = ( PRAWINPUT ) malloc( buffer_size );

        message = std::format( L"\nbuffers size: {}" , buffer_size );
        OutputDebugString( message.data() );

        //buffer_size *= 8;
        //raw_input.resize( buffer_size );

        //result = GetRawInputBuffer( raw_input.data() , &buffer_size , header_size );
        //result = GetRawInputBuffer( pRawInput , &buffer_size , header_size );

        message = std::format( L"\nbuffers read: {}" , result );
        OutputDebugString( message.data() );

        UINT nInput = GetRawInputBuffer( pRawInput , &buffer_size , sizeof( RAWINPUTHEADER ) );

        if( nInput != 0 )
        {
            message = std::format( L"\nbuffers read: {}" , result );
            OutputDebugString( message.data() );

            PRAWINPUT * paRawInput = ( PRAWINPUT * ) malloc( sizeof( PRAWINPUT ) * nInput );

            if( paRawInput != NULL )
            {
                PRAWINPUT pri = pRawInput;

                for( UINT i = 0; i < nInput; ++i )
                {
                        //Log( _T( " input[%d] = @%p" ) , i , pri );
                    paRawInput[ i ] = pri;
                    pri = NEXTRAWINPUTBLOCK( pri );
                }

                free( paRawInput );
            }
        }

        free( pRawInput );

        // RAWINPUT.hid may be an array of RAWHID structures
        /*
        if( result > 0 )
        {
            for( auto & input : raw_input )
            {
                // for each input.data.hid
                application->update( input );

                if( input.data.hid.dwCount > 0 )
                    message = std::format( L"\nhid array amount: {}" , input.data.hid.dwCount );

                OutputDebugString( message.data() );
            }
        }
        else print_debug( L"\nGet raw input error: " );
        */
    }
    else print_debug( L"\nGet input buffer size error: ", 0);

    //raw_input.clear();
}

unsigned long long MSWindows::message_loop()
{
    MSG message {};
    int result = 0;

    Application * app = reinterpret_cast< Application * >( GetWindowLongPtrW( window_principle , GWLP_USERDATA ) );
    //process_input();

    while( ( result = GetMessage( &message, window_principle, 0, 0 ) ) != 0 )
    {
        if( result == -1 )
        {
            //print_debug( L"\nGetMessage error: ", 0 );
        }
        //else if( message.message == WM_INPUT ) app->process_input();
        else
        {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }

        //if( elapsed_time += frame_delta() > 16ms )
        //class_pointer->update();
        //class_pointer->render();
    }

    return message.wParam;
}

//long long __stdcall MSWindows::message_handler( HWND window, UINT message, WPARAM wParam, LPARAM lParam )
//__int64 
LRESULT CALLBACK MSWindows::message_handler( HWND window, UINT message, WPARAM wParam, LPARAM lParam )
{
    /*
    static window_messages messages;
    std::wstring win_message = messages.message_text( message );
    OutputDebugString( win_message.c_str() );
    */

    Application * application = reinterpret_cast< Application * >( GetWindowLongPtrW( window , GWLP_USERDATA ) );

    if( message == WM_CREATE )
    {
        // Save the Application * passed in to CreateWindow.
        CREATESTRUCTW * create_struct = reinterpret_cast< CREATESTRUCTW * >( lParam );
        
        SetWindowLongPtrW( window ,
                           GWLP_USERDATA , 
                           reinterpret_cast< LONG_PTR >( create_struct->lpCreateParams ) );
    }
    else
    {
        if( application ) // window creation complete
        {
            switch( message )
            {
                case WM_CLOSE: 
                { 
                    //"are you sure you want to exit application?" 
                    //if( MessageBox( window , L"Confirm exit" , L"Application" , MB_YESNOCANCEL ) == IDYES ) DestroyWindow( window );
                    //else return 0;
                } break;

                case WM_DESTROY:
                {
                    PostQuitMessage( 0 );
                } break;

                //https://learn.microsoft.com/en-us/windows/win32/inputdev/using-raw-input
                //https://ph3at.github.io/posts/Windows-Input/
                //https://stackoverflow.com/questions/28879021/winapi-getrawinputbuffer
                //https://docs.unity3d.com/6000.2/Documentation/ScriptReference/Windows.Input.ForwardRawInput.html
                //case WM_TOUCH:
                case WM_INPUT:
                {
                    std::wstring message;

                    uint buffer_size = 0;

                    GetRawInputData( ( HRAWINPUT ) lParam, RID_INPUT, NULL, &buffer_size, sizeof( RAWINPUTHEADER ) );

                    //uchar * buffer = new uchar[ buffer_size ];
                    RAWINPUT * buffer = new RAWINPUT[ buffer_size ];

                    message = std::format( L"\nbuffers size: {}" , buffer_size );
                    OutputDebugString( message.data() );

                    if( GetRawInputData( ( HRAWINPUT )lParam, RID_INPUT, buffer, & buffer_size, sizeof( RAWINPUTHEADER ) ) != buffer_size )
                        print_debug( L"\nGetRawInputData does not return correct size", 0 );

                    std::stringstream ss {};
                    for( int i=0; i < buffer_size; ++i )
                    //ss << std::setfill('0') << std::hex << std::setw(2) << (unsigned int)std::uint8_t(-1);
                        ss << std::setfill( '0' ) << std::hex << ( unsigned int ) buffer->data.hid.bRawData[ i ];
                    std::string mystr = ss.str();
                    
                    //message = std::format( L"\nhid data: 0x{}" , mystr );
                    //print_debug( message.data() );

                    print_debug( mystr.data() );

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

                case WM_DISPLAYCHANGE:
                case WM_PAINT:
                {
                    /*PAINTSTRUCT paint{};
                    BeginPaint( window , & paint );
                    EndPaint( window , &paint );*/
                    
                } break;

                case WM_SIZE:
                //case WM_EXITSIZEMOVE:
                {
                    application->window_size_changed( static_cast< __int64 >( lParam ) & 0xFFFF,
                                                      ( static_cast< __int64 >( lParam ) >> 16 ) & 0xFFFF );
                } break;

                case WM_KEYUP:
                case WM_KEYDOWN:
                //case WM_SYSKEYUP:
                {
                    uint wparameter = static_cast< uint >( wParam );

                    //class_pointer->key_pressed( wparameter );

                } break;

                default: 
                {
                    return DefWindowProcW( window , message , wParam , lParam );
                }

            } // switch message
        
        } // if gui

    } // message not_eq WM_CREATE

    return DefWindowProcW( window , message , wParam , lParam );

} // message_handler

void MSWindows::register_input_device( ushort page , ushort usage ) //, touchpad_amount
{
    RAWINPUTDEVICE raw_device
    {
        .usUsagePage = page,
        .usUsage     = usage,
        .dwFlags     = RIDEV_INPUTSINK, // RIDEV_DEVNOTIFY | RIDEV_EXINPUTSINK // attached and detached
        .hwndTarget  = window_principle
    };

    // 
    bool result = RegisterRawInputDevices( & raw_device, 1, sizeof( raw_device ) );

    if( ! result  ) print_debug( L"\nRegister input device error: ", 0 );
    else print_debug( L"\n registered device.");
}

/*void MSWindows::window_rectangles()
{
    EnumWindows( MSWindows::enumerate_windows ,
                 reinterpret_cast< LPARAM >( this ) );
}

BOOL CALLBACK MSWindows::enumerate_windows( HWND window , LPARAM parameter )
{
    RECT rectangle{};

    GetWindowRect( window , &rectangle );

    MSWindows * window_class = reinterpret_cast< MSWindows * >( parameter );

    window_class->window_recangles.insert( rectangle );

    return true;
}*/

MSWindows::~MSWindows()
{
    //OutputDebugString( L"\n MSWindows::~MSWindows()" );
}