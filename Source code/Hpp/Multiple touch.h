#pragma once

#include "Application.h"

#include "Input\HID\Devices.h"
#include "Input\HID\Usages.h"

namespace HID
{
    // One or more mutliple touch inputs for example touchpad , touchscreen. 
    class Multiple_touch : public Application, public Devices //, public Usages
    {  
        public:

            Multiple_touch( HINSTANCE instance, LPWSTR parameters, int show_flags );

            virtual void update();
            virtual void render();
    };
}
