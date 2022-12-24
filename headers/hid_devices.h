#pragma once

#include "..\headers\hid_device.h"

namespace hid
{
    class hid_devices
    {
        private:
            
            uint                      device_amount{};
            vector< raw_device_list > raw_list{};

            std::vector< hid_device > input{};

            //text                      information {};

        public:

            hid_devices( void );
            //~hid_devices( void );

            void draw();

    };

}