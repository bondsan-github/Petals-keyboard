#include "..\headers\hid_devices.h"
#include "..\headers\constants.h"
#include "..\headers\hid_device.h"
#include < windows.h >

namespace hid
{
    void hid_devices::initialise()
    {
        uint                      amount   {};
        vector< raw_device_list > raw_list {};

        GetRawInputDeviceList( nullptr , & amount , sizeof( raw_device_list ) );

        raw_list.resize( amount );

        GetRawInputDeviceList( raw_list.data() , & amount , sizeof( raw_device_list ) );

        for( auto & device : raw_list )
        {
            hid_device new_device( device.hDevice );

            if( new_device.is_multi_touch() )
                input.emplace_back( move( new_device ) );
        }

        //if( input.empty() )
            //locate
        //    information.set_content( L"no precision multiple touch devices found" );
        //else
        //    information.set_content( L"" );
    }

    void hid_devices::draw()
    {
        //information.draw();

        for( auto & device : input ) device.draw();
    }
}