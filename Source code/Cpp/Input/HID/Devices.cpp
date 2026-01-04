#include "Input\HID\Devices.h"

#include "Aliases.h"

#include <cstring>

namespace HID
{
    Devices::Devices()
    { 
        OutputDebugString( L"\n Devices::Devices()" );
        initialise();
    }

    Devices::~Devices()
    {
        OutputDebugString( L"\n Devices::~Devices()" );
    }

    void Devices::initialise()
    {
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

        std::wstring message = L"\n  devices amount: " + std::to_wstring( amount ) + L"\n";
        print_debug( message.data() );

        Identity identity {};
        uint     device_index {}; // 4 / 8 /11
        uint     device_multiple_touch_index {};
        
        // find first precision touchpad
        for( ; device_index < raw_device_list.size() ; device_index++ )
        {
            log = L"\ndevice index: " + std::to_wstring( device_index );
            OutputDebugString( log.data() );

            Device new_device( raw_device_list.at( device_index ).hDevice);//, mt );

            if( new_device.is_multi_touch() )
            {
                log = L"\nmulti touch device at index: " + std::to_wstring( device_index );
                OutputDebugString( log.data() );

                device_multiple_touch_index = device_index;

                identity = new_device.identity();

                input_devices.push_back( new_device );
                
                // Register Raw Input Devices
                //mt.register_input_device( new_device.page() ,
                //                          new_device.usage() );

                break; // leaves iterator at current position
            }
        }
        
        raw_device_list.clear();

        /*for( auto & device : input_devices )
        {
            device.collect_information();
        }*/

        //if( input.empty() )
        //    information.set_content( L"no precision multiple touch devices found" );
    }

    Device * Devices::device( HANDLE handle )
    {
        Device * pointer_device { nullptr };

        for( auto & device : input_devices )
        {
            if( device.handle() == handle )
            {
                pointer_device = & device;
                break;
            }
        }

        return pointer_device;
    }

    // multiple devices
    void Devices::update_devices( RAWINPUT * hid_report )
    {
        for( auto & device : input_devices ) 
        {
            if( device.handle() == hid_report->header.hDevice )
                //device.update( hid_report.data.hid );
                device.update( hid_report );
                //device.update();
        }
    }

    void Devices::update_devices_buffered( RAWINPUT ** raw_input_buffer, uint buffer_size )
    {
        /*
        RAWINPUT * current_report = raw_input_buffer;

        // for each input report
        for( int index{ 0 }; index < buffer_size; index++ )
        {
            //_raw_input_buffer[index] = current_report;

            for( auto & device : input_devices )
            {
                if( device.get_handle() == _raw_input_buffer[ index ].header.hDevice )
                {
                    //device.update( raw_input_buffer[ index ] );
                }
            }
        }
        */
        //NEXTRAWINPUTBLOCK();
        //long size = sizeof (unsigned long long); // =8 bytes // 4Ui64
        //long sizelong = sizeof (long); // =4bytes
        //#define RAWINPUT_ALIGN(x)   (((x) + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1))
        //NEXTRAWINPUTBLOCK(ptr) ((PRAWINPUT)RAWINPUT_ALIGN((ULONG_PTR)((char *)(ptr) + (ptr)->header.dwSize)))
    }

    void Devices::update_device_buffered( RAWINPUT ** raw_input_buffer, uint buffer_size )
    {
        input_devices.at(0).update_buffered( raw_input_buffer, buffer_size );
    }
}