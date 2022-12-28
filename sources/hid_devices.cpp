#include "..\headers\hid_devices.h"

#include "..\headers\custom_types.h"
#include "..\headers\hid_device.h"

#include <windows.h>

namespace hid
{
    hid_devices::hid_devices( void )
    {
        // get device amount
        GetRawInputDeviceList( nullptr , & device_amount , sizeof( raw_device_list ) );

        raw_device_list.resize( device_amount );

        // get device list
        GetRawInputDeviceList( raw_device_list.data() , & device_amount , sizeof( raw_device_list ) );

        // copy only multiple touch devices to input vector
        for( auto & device : raw_device_list )
        {
            hid_raw_device new_raw_device( device.hDevice );

            if( new_raw_device.is_multi_touch() )
            {
                hid_device new_hid_device( new_raw_device );
                input.push_back( new_hid_device );
                //input.emplace_back( new_raw_device );
            }
        }

        raw_device_list.clear();

        for( auto & device : input )
        {
            device.collect_information();
        }


        //if( input.empty() )
        //    information.set_content( L"no precision multiple touch devices found" );
        //else
        //    information.set_content( L"" );
    }

    //hid_devices::~hid_devices( void ) { OutputDebugString( L"\n hid_devices::de-constructor" ); }

    void hid_devices::draw()
    {
        //information.draw();

        for( auto & device : input ) device.draw();
    }
}