#pragma once

#include "..\headers\hid_device.h"

//#include <windows.h> // RAWINPUTDEVICELIST
#include <vector>

namespace hid
{
    class hid_devices
    {
        private:
            
            std::vector< RAWINPUTDEVICELIST > raw_device_list {};
            std::vector< hid_device >         input_devices   {};

            //text information;

        public:

            void initialise();

            void draw();
    };
}