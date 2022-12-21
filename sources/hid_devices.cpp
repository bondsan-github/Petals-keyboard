#include "..\headers\hid_devices.h"
#include "..\headers\constants.h"
#include "..\headers\hid_device.h"
#include < windows.h >

namespace hid
{
    hid_devices::hid_devices( void )
    {
        OutputDebugString( L"\n hid_devices::constructor" );

        uint                      amount   {};
        vector< raw_device_list > raw_list {}; // RAWINPUTDEVICELIST

        GetRawInputDeviceList( nullptr , & amount , sizeof( raw_device_list ) );

        raw_list.resize( amount );

        GetRawInputDeviceList( raw_list.data() , & amount , sizeof( raw_device_list ) );

        for( auto & device : raw_list )
        {
            hid_raw_device new_raw_device( device.hDevice );

            if( new_raw_device.is_multi_touch() )
            {
                hid_device new_hid_device( device.hDevice );
                input.emplace_back( move( new_hid_device ) );
            }
        }

        //if( input.empty() )
            //locate
        //    information.set_content( L"no precision multiple touch devices found" );
        //else
        //    information.set_content( L"" );
    }

    hid_devices::~hid_devices( void )
    {
        OutputDebugString( L"\n hid_devices::de-constructor" );
    }

    void hid_devices::draw()
    {
        //information.draw();

        for( auto & device : input ) device.draw();
    }
}