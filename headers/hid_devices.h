#pragma once

#include "..\headers\hid_device.h"

//#include <windows.h> // RAWINPUTDEVICELIST
#include <vector>

namespace hid
{
    class hid_devices
    {
        private:
            
            uint                              device_amount   { 0 };
            std::vector< RAWINPUTDEVICELIST > raw_device_list {};
            std::vector< hid_device >         input_devices   {};

            //text information;

        public:

            hid_devices( void );
            ~hid_devices( void );

            void initialise();

            //std::vector< hid_device > & get_input_devices() { return input_devices; }

            void draw();
    };
}