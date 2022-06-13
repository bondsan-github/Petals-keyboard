#pragma once

#include "..\headers\windows.h"
#include "..\headers\hid_devices.h"
#include "..\headers\graphics.h"
#include "..\headers\write.h"

// 1. transparent full screen draw contacts

namespace hid 
{
   using namespace std;

   // one or more mutli-touch inputs for example touchpad , touchscreen. 
    class multi_touch : public window , public graphics , public write , public hid_devices
    {
        virtual LRESULT message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter ) override;

        public:

        void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
        {
            window::initialise( instance , parameters , show_flags );
            graphics::initialise( window_ptr );
            write::initialise();
            hid_devices::initialise();
        }

        int begin()
        {
            if( input.empty() )
            {
                add( L"no precision multiple touch devices found" );
            }

            return message_loop();
        }

    }; //class multi_touch

    LRESULT multi_touch::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
    {
        switch( message )
        {
            case WM_DESTROY:
            {
                PostQuitMessage( 0 );
            } break;

            case WM_PAINT:
            {
                graphics::draw();
                write::draw();
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
