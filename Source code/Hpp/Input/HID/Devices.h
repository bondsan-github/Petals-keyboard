#pragma once

#include "Input\HID\Types.h"
#include "Input\HID\Device.h"

#include "Output\Logging.h"

#include <vector>

namespace HID
{
    class Devices : public Logging
    {
        protected:
            
            std::vector< RAWINPUTDEVICELIST > raw_device_list {};
            std::vector< Device >             input_devices   {};

        public:

            Devices();
            ~Devices();

            // copy, move = delete;

            void initialise();
            
            std::wstring log;

            //add_contact( device, identifier );
            //update_contact_x( device, identifier, x);
            //update_contact_x( device, identifier, y);

            void update( RAWINPUT input );
    };
}