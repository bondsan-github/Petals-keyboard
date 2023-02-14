#include "..\headers\hid_multiple_touch.h"

#include "..\headers\locate.h"

namespace hid
{
    hid_multiple_touch::hid_multiple_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
    {
        //OutputDebugString( L"hid_multi_touch::paramatised constructor\n" );

        locate::set_application( this );

        // window takes several cycles to fully initialise 
        window.initialise( instance , parameters , show_flags );
        //Sleep(1000);
        graphics.initialise( window.get_window() );
        write.initialise();
        input.initialise(); // window.register_input_device
        //window.set_graphics( &graphics );
        window.message_loop();
    }

    /*
    void hid_multiple_touch::start()
    {
        // calls to unitialised window fail
        //graphics.initialise();
        //write.initialise();
        //input.initialise();

        //if( window == ready
        //    graphics.get_state() == states::ready and
        //    write.get_state() == states::ready

        update();
    }*/

    /*
    void hid_multiple_touch::start()
    {
         //window.message_loop();
            //graphics.draw_begin();
            //input.update();
            //input.draw();
            //graphics.draw_end();
    }*/

    /*hid_multiple_touch::~hid_multiple_touch()
    {
        //OutputDebugString( L"hid_multi_touch::de-constructor\n" );
    }*/

} // namespace hid


// touchpad HID - mouse + keyboard
// one finger/point = context
// two finger = navigation - mouse window_ptr | context | direct touch 
// three = move window
// 
// five = keyboard
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
