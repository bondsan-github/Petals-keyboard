#pragma once

#include "Source code/Hpp/Application.hpp"

//#include "..\headers\write_d2d.h"

#include "Source code/Hpp/Input/HID/HID_Devices.hpp"
#include "Source code/Hpp/Input/HID/HID_Usages.hpp"

namespace HID
{
    // One or more mutliple touch inputs for example touchpad , touchscreen. 
    class Multiple_touch : public Application // , public Usages , public Devices
    {  
        private: 
            
            //write_d2d     write;
            
            Usages    usages;
            Devices   input;

        public:

            Multiple_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );

            virtual void update();
            virtual void render();
    };

}
