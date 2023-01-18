#pragma once

#include "..\headers\hid_device.h"
#include "..\headers\hid_globals.h"

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
            //void update();// char * in_input, uint input_size );
            void update_devices( RAWINPUT in_hid_report );
            void draw();
    };
}