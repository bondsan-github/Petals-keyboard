#pragma once

#include "Input\HID\Globals.h"
#include "Input\HID\Device.h"

#include "Graphics\DWrite\Text.h"

#include "Output\Logging.h"

//#include <windows.h> // RAWINPUTDEVICELIST
#include <vector>

namespace HID
{
    class Multiple_touch;

    class Devices : public Logging
    {
        private:
            
            std::vector< RAWINPUTDEVICELIST > raw_device_list {};
            std::vector< Device >             input_devices   {};

            Text information {};

            Multiple_touch & application;

        public:

            Devices( Multiple_touch & application );

            void initialise();
            
            Device * device( HANDLE in_handle );
            //add_contact( device, identifier );
            //update_contact_x( device, identifier, x);
            //update_contact_x( device, identifier, y);

            //void update_devices( RAWINPUT * in_hid_report , uint in_buffer_size );
            void update_devices( RAWINPUT * in_hid_report );
            
            void update_devices_buffered( RAWINPUT ** in_raw_input_buffer, uint in_buffer_size );
            void update_device_buffered( RAWINPUT ** in_raw_input_buffer, uint in_buffer_size );

            void draw();
    };
}