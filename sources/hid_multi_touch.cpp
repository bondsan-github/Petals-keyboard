#include "..\headers\hid_multi_touch.h"

namespace hid
{
    using namespace std;

    void hid_multi_touch::initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
    {
        gui_windows_ms::initialise( instance , parameters , show_flags );
        graphics.initialise();
        write.initialise();

        usages.initialise();
        hid_devices::initialise();
    }

    int hid_multi_touch::begin()
    {
        if( input.empty() )
        {
            write.add( L"no precision multiple touch devices found" );
        }

        return message_loop();
    }

    LRESULT hid_multi_touch::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
    {
        switch( message )
        {
            case WM_DESTROY:
            {
                PostQuitMessage( 0 );
            } break;

            case WM_PAINT:
            {
                graphics.draw();
                write.draw();
                hid_devices::draw();
            } break;

            case WM_SIZE:
            {
               //paint.resize();
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
                        for( auto & device : input )
                            device.display_information();
                    }
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
