#pragma once

#include "Source code/Hpp/Application.hpp"

#include "Source code/Hpp/Input/HID/HID_Devices.hpp"
#include "Source code/Hpp/Input/HID/HID_Usages.hpp"

namespace HID
{
    // One or more mutliple touch inputs for example touchpad , touchscreen. 
    class Multiple_touch : public Application , public Devices // , public Usages
    {  
        private: 
            
        public:

            Multiple_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );

            virtual void update();
            virtual void render();
    };
}
