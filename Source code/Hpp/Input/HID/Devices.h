#pragma once

#include "Input\HID\Types.h"
#include "Input\HID\Device.h"

#include "Output\Logging.h"

#include <vector>

namespace HID
{
    class Devices : public Logging
    {
        private:
            
            std::vector< RAWINPUTDEVICELIST > raw_device_list {};
            std::vector< Device >             input_devices   {};

        public:

            Devices();
            ~Devices();

            // copy, move = delete;

            void initialise();
            
            Device * device( HANDLE handle );

            std::wstring log;

            //add_contact( device, identifier );
            //update_contact_x( device, identifier, x);
            //update_contact_x( device, identifier, y);

            //void update_devices( RAWINPUT * in_hid_report , uint in_buffer_size );
            void update_devices( RAWINPUT * in_hid_report );
            
            void update_devices_buffered( RAWINPUT ** input_buffer, uint buffer_size );
            void update_device_buffered(  RAWINPUT ** input_buffer, uint buffer_size );
    };
}