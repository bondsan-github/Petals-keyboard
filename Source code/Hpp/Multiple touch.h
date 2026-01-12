#pragma once

#include "Application.h"

//#include "Operating system\targetver.h"
//#include <Windows.h>

#include "Input\HID\Devices.h"
#include "Input\HID\Usages.h"

namespace HID
{
    // One or more mutliple touch inputs for example touchpad, touchscreen. 
    class Multiple_touch : public Application, public HID::Devices, public HID::Usages
    {  
        public:

            Multiple_touch( HINSTANCE instance, LPWSTR parameters, int show_flags );

            virtual void update( RAWINPUT input ) final;
            virtual void render() final;
    };
}

/*
path: \\ ? \HID#VID_258A & PID_2016 & MI_01 & Col02#7 & 31c8c857 & 0 & 0001#{4d1e55b2 - f16f - 11cf - 88cb - 001111000030}
path: \\ ? \HID#VID_258A & PID_2016 & MI_01 & Col03#7 & 31c8c857 & 0 & 0002#{4d1e55b2 - f16f - 11cf - 88cb - 001111000030}
path: \\ ? \HID#VID_258A & PID_2016 & MI_01 & Col04#7 & 31c8c857 & 0 & 0003#{4d1e55b2 - f16f - 11cf - 88cb - 001111000030}
type: 258a 2016
Usage( page ) : 0x6 ( 0x1 )
Usage( page ) : 0x2 ( 0x1 )
Usage( page ) : 0x5 ( 0xd )
Usage( page ) : 0xe ( 0xd )
Usage( page ) : 0xc ( 0x1 )
Usage( page ) : 0x1 ( 0xff00 )
Usage( page ) : 0x1 ( 0xc )
*/