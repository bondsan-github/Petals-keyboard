#pragma once

#include "Source code/Hpp/Application.hpp"

#include "Source code/Hpp/Input/HID/HID_Devices.hpp"
#include "Source code/Hpp/Input/HID/HID_Usages.hpp"

//namespace HID
//{
    // One or more mutliple touch inputs for example touchpad , touchscreen. 
    class Multiple_touch : public Application , public HID::Devices // , public Usages
    {  
        private: 
            
        public:

            Multiple_touch( HINSTANCE instance , LPWSTR parameters , int show_flags );

            virtual void update();
            virtual void render();
    };
//}
