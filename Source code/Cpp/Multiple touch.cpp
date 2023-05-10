#include "Source code/Hpp/Multiple touch.hpp"

namespace hid
{
    Multiple_touch::Multiple_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
    {
        // window takes several cycles to fully initialise 
        //initialise( instance , parameters , show_flags );
        //initialise( Client_size::fullscreen );
        initialise();
        
        //input.initialise(); // window.register_input_device
        //write.initialise();
    }

    void Multiple_touch::update()
    {
    }
    
    void Multiple_touch::render()
    {
    }


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
