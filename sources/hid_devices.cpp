#include "..\headers\hid_devices.h"

#include "..\headers\custom_types.h"
//#include "..\headers\hid_device.h"
#include "..\headers\locate.h"
#include "..\headers\utility.h"

#include <windows.h>

namespace hid
{
    void hid_devices::initialise()
    {
        locate::set_input_devices( this );

        uint device_amount { 0 };
        // get device amount
        int result = GetRawInputDeviceList( 0 , & device_amount , sizeof( RAWINPUTDEVICELIST ) );

        //print_debug( L"devices amount: %d\n" );//, result);

        if(result < 0 ) error_exit(L"get input device list error");

        raw_device_list.resize( device_amount );

        // get device list
        GetRawInputDeviceList( raw_device_list.data() , & device_amount , sizeof( RAWINPUTDEVICELIST ) );

        // todo: search device list for same company and device
        for( auto & device : raw_device_list )
        {
            hid_raw_device new_raw_device( device.hDevice );

            if( new_raw_device.is_multi_touch() )
            {
                input_devices.emplace_back( new_raw_device );
            }
        }

        raw_device_list.clear();

        for( auto & device : input_devices )
        {
            device.collect_information();
        }

        //if( input.empty() )
        //    information.set_content( L"no precision multiple touch devices found" );
        //else
        //    information.set_content( L"" );
    }

    void hid_devices::draw()
    {
        //information.draw();
            for( auto & device : input_devices ) device.draw();
    }
}