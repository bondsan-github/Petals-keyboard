#pragma once

#include "targetver.h"
#include "Application.h"

#include "Input\HID\Devices.h"
#include "Input\HID\Usages.h"

namespace HID
{
    // One or more mutliple touch inputs for example touchpad, touchscreen. 
    class Multiple_touch : public Application, public HID::Devices, public HID::Usages
    {  
        public:

            Multiple_touch( HINSTANCE instance, LPWSTR parameters, int show_flags );

            virtual void update() final;
            virtual void render() final;
    };
}
