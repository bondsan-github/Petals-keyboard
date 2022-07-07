#pragma once

#include "..\headers\hid_device.h"

namespace hid
{
    class hid_devices
    {
        protected:

            std::vector< hid_device > input;
            //text                      information {};

        public:

            void initialise();
            void draw();

    };

}