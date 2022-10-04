#include "..\headers\hid_multi_touch.h"
#include "..\headers\hid_device.h"

#include "..\headers\locate.h"

namespace hid
{
    using namespace std;

    void hid_multi_touch::initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
    {
        gui_windows_ms::initialise( instance , parameters , show_flags );
        graphics.initialise( get_window() );
        //grid.initialise();
        write.initialise();
        usages.initialise();

        input.initialise();
    }

    int hid_multi_touch::begin()
    {
        return message_loop();
    }

    LRESULT hid_multi_touch::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
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
                //UpdateLayeredWindow
     
                /*Hit testing of a layered window is based on the shape and transparency of the window.
                This means that the areas of the window that are color-keyed or whose alpha value is zero 
                will let the mouse messages through. 
                However, if the layered window has the WS_EX_TRANSPARENT extended window style, 
                the shape of the layered window will be ignored 
                and the mouse events will be passed to other windows underneath the layered window.*/
            //https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/december/windows-with-c-layered-windows-with-direct2d
                
                page_window_pointer page = locate::graphics().get_page();

                BeginPaint( get_window() , & paint );
                
                if( page )
                {
                    page->BeginDraw();

                    page->SetTransform( Matrix3x2F::Identity() );

                    page->Clear( ColorF( 0.2f , 0.2f , 0.2f , 0.2f ) );

                    input.draw();

                    page->EndDraw();

                    long result = EndPaint( get_window() , & paint );
                    //if( result < 0 ) discard_resources();
                }
            } break;

            case WM_SIZE:
            {
               //graphics.resize();
            } break;

            case WM_KEYDOWN:
            {
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
            }

        } // switch( message )

        return DefWindowProc( in_window , message , wParam , lParam );

    } // message_handler


} // namespace hid


// touchpad HID - mouse + keyboard
// one finger navigation - mouse window_ptr | context | direct touch 
// two finger context
// ten finger 

/* references:
*    windows/driver samples/hid/hclient
*    www-user.tu-chemnitz.de/~heha/hsn/free.var , hidparse
*    stackoverflow.com
*    quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/
*    C++ How to program 10th edition , Deitel & Associates, Inc , ISBN-10: 0-13-444823-5 , ISBN-13: 978-0-13-444823-7
*/

// input_modifiers  ( buttons , values , features ) 
                  // output_modifiers
                  // 
                  // press over force threshold for capital letter
                  // delay after press for context 
                  // combined movement is mouse // 
                  // 
