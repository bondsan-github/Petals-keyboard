#include "Operating system\MSWindows.h"

//#include "MSWindows messages.h"
#include "Application.h"
#include "Output\Logging.h"

//#include <winuser.h>
//#include <wingdi.h>

typedef unsigned __int64 QWORD; // 64-bit integer

MSWindows::MSWindows( Application * application )
: application { application }
{}

HWND MSWindows::initialise( Size in_client_size )
{
    if( in_client_size ) client_size_ = in_client_size;
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

    if( not atom ) error_exit( L"Unable to register class ex." );
    
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

    if( not window_principle ) error_exit( L"Unable create principle window." );
 
    ShowWindow( window_principle , SW_SHOWNORMAL ); // set show state
    
    //window_rectangles();

    return window_principle;
}

void MSWindows::window_size_changed( uint width , uint height )
{
    Size new_size( width , height );

    if( new_size not_eq client_size_ )
    {
        application->window_size_change( width , height );
    }
    else
    {
        return;
    }
}

RECT MSWindows::get_client_position()
{
    RECT position {};

    // pixel at [ right, bottom ] lies immediately outside the rectangle.
    GetWindowRect( window_principle , & position );

    return position;
}

Size MSWindows::get_client_size()
{
    RECT area {};
    
    GetClientRect( window_principle , &area);

    return { area.right - area.left , area.bottom - area.top };
}

HWND MSWindows::get_window() const
{
    return window_principle;
}

int MSWindows::message_loop()
{
    MSG message {};

    Application * class_pointer = reinterpret_cast< Application * >( GetWindowLongPtrW( window_principle , GWLP_USERDATA ) );

    while( message.message not_eq WM_QUIT )
    {
        if( PeekMessageW( & message , NULL , 0U , 0U , PM_REMOVE ) )
        {
            TranslateMessage( & message );
            DispatchMessage( & message );
        }

        //if( elapsed_time += get_delta() > 16ms )
        class_pointer->update();
        class_pointer->render();
    }

    // Return this part of the WM_QUIT message to Windows.
    return static_cast< char >( message.wParam );
}

//long long __stdcall MSWindows::message_handler( HWND window , UINT message , WPARAM wParam , LPARAM lParam )
LRESULT CALLBACK MSWindows::message_handler( HWND window , UINT message , WPARAM wParam , LPARAM lParam )
{
    /*
    static window_messages messages;
    std::wstring win_message = messages.message_text( message );
    OutputDebugStringW( win_message.c_str() );
    */

    Application * class_pointer = reinterpret_cast< Application * >( GetWindowLongPtrW( window , GWLP_USERDATA ) );

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
        if( class_pointer )
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

                case WM_INPUT:
                //case WM_TOUCH:
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
                    class_pointer->window_size_changed( static_cast< __int64 >( lParam ) & 0xFFFF,
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

void MSWindows::register_input_device( ushort page , ushort usage )
{
    RAWINPUTDEVICE raw_device
    {
        .usUsagePage = page ,
        .usUsage     = usage ,
        .dwFlags     = RIDEV_DEVNOTIFY , // | RIDEV_EXINPUTSINK | RIDEV_INPUTSINK // attached and detached
        .hwndTarget  = window_principle
    };

    RegisterRawInputDevices( &raw_device , 1 , sizeof( RAWINPUTDEVICE ) );
}

void MSWindows::get_window_rectangles()
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
}

MSWindows::~MSWindows()
{
    //OutputDebugString( L"MSWindows::de-constructor\n" );
}