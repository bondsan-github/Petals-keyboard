#pragma once

#include < vector >

#include < hidsdi.h >
#include < hidpi.h >

#include "..\headers\hid_device.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    class hid_devices
    {
        protected:

            vector< hid_device > input; // multi-touch devices

        public:

            void initialise()
            {
                using raw_device_list = RAWINPUTDEVICELIST;

                uint                      amount   {};
                vector< raw_device_list > raw_list {};

                GetRawInputDeviceList( nullptr         , & amount , sizeof( raw_device_list ) );

                raw_list.resize( amount );

                GetRawInputDeviceList( raw_list.data() , & amount , sizeof( raw_device_list ) );

                for( auto & device : raw_list )
                {
                    hid_device new_device( device.hDevice );

                    if( new_device.is_multi_touch() )
                        input.emplace_back( move( new_device ) );
                }
            }

            void draw()
            {
                for( auto & device : input  )
                    device.draw();
            }

    }; // class hid_devices

} // namespace hid