#include "Input\HID\Devices.h"

#include "Aliases.h"

#include <cstring>

namespace HID
{
    Devices::Devices()
    { 
        //OutputDebugString( L"\n Devices::Devices()" );
        initialise();
    }

    Devices::~Devices()
    {
        //OutputDebugString( L"\n Devices::~Devices()" );
    }

    void Devices::initialise()
    {
        //OutputDebugString( L"\n\t Devices::initialise()" );

        uint amount {};
        
        int result = GetRawInputDeviceList( 0,
                                            & amount,
                                            sizeof( RAWINPUTDEVICELIST ) );

        if( result < 0 ) error_exit( L"Unable to get raw input device list.", result );

        raw_device_list.resize( amount );

        // get device list
        GetRawInputDeviceList( raw_device_list.data() ,
                               & amount ,
                               sizeof( RAWINPUTDEVICELIST ) );

        //std::wstring message = L"\n  devices amount: " + std::to_wstring( amount ) + L"\n";
        //print_debug( message.data() );

        uint device_index {};
                
        for( const auto & device : raw_device_list )
        {
            Device new_device( raw_device_list.at( device_index ).hDevice);

            if( new_device.is_multi_touch() )
            //if( new_device.manufacturer( 0x258a ) )
            {
                new_device.collect_information();

                input_devices.push_back( new_device );
            }
            device_index++;
        }
        
        raw_device_list.clear();
    }

    // multiple devices
    void Devices::update()
    {
        for( auto & device : input_devices ) device.update();
    }
}// namespace HID