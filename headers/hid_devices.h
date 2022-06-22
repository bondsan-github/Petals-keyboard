#pragma once

#include < vector >

#include "..\headers\hid_device.h"

namespace hid
{
    using namespace std;

    class hid_devices
    {
        protected:

            vector< hid_device > input; // multi-touch devices

        public:

            void initialise();
            void draw();

    }; // class hid_devices

} // namespace hid