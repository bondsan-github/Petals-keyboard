#include "Input\HID\Devices.h"

#include "Custom types.h"
#include "Output\Logging.h"

#include "Multiple touch.h"

#include <windows.h>

namespace HID
{
    Devices::Devices( Multiple_touch & application )
    : application( application )
    {        
    }

    void Devices::initialise()
    {
        uint device_amount {};
        
        int result = GetRawInputDeviceList( 0 ,
                                            & device_amount ,
                                            sizeof( RAWINPUTDEVICELIST ) );

        if( result < 0 ) error_exit( L"Unable to get raw input device list." );

        raw_device_list.resize( device_amount );

        // get device list
        GetRawInputDeviceList( raw_device_list.data() ,
                               & device_amount ,
                               sizeof( RAWINPUTDEVICELIST ) );

        //message = L"\ndevices amount: " + std::to_wstring( device_amount ) + L"\n";
        //OutputDebugStringW( message.data() );

        Identity identity {};
        uint     device_index {}; // 4 / 8 /11
        uint     device_multiple_touch_index {};
        
        // find first precision touchpad
        for( ; device_index < raw_device_list.size() ; device_index++ )
        {
            //message = L"\ndevice index: " + std::to_wstring( device_index );
            //OutputDebugStringW( message.data() );

            Device new_device( raw_device_list.at( device_index ).hDevice , application );

            if( new_device.is_multi_touch() )
            {
                //message = L"\nmulti touch device at index: " + std::to_wstring( device_index );
                //OutputDebugStringW( message.data() );

                device_multiple_touch_index = device_index;

                identity = new_device.identity();

                input_devices.push_back( new_device );
                
                // Register Raw Input Devices
                application.register_input_device( new_device.page() ,
                                                   new_device.usage() );

                break; // leaves iterator at current position
            }
        }
        
        raw_device_list.clear();

        for( auto & device : input_devices )
        {
            device.collect_information();
        }

        //if( input.empty() )
        //    information.set_content( L"no precision multiple touch devices found" );
    }

    Device * Devices::device( HANDLE in_handle )
    {
        Device * pointer_device{ nullptr };

        for( auto & device : input_devices )
            if( device.handle() == in_handle )
            {
                pointer_device = &device;
                break;
            }

        return pointer_device;
    }

    // multiple devices
    void Devices::update_devices( RAWINPUT * in_hid_report )
    {
        for( auto & device : input_devices ) 
        {
            if( device.handle() == in_hid_report->header.hDevice )
                //device.update( in_hid_report.data.hid );
                device.update( in_hid_report );
                //device.update();
        }
    }

    void Devices::update_devices_buffered( RAWINPUT ** in_raw_input_buffer , uint in_buffer_size )
    {
        /*
        RAWINPUT * current_report = in_raw_input_buffer;

        // for each input report
        for( int index{ 0 }; index < in_buffer_size; index++ )
        {
            //in_raw_input_buffer[index] = current_report;

            for( auto & device : input_devices )
            {
                if( device.get_handle() == in_raw_input_buffer[ index ].header.hDevice )
                {
                    //device.update( in_raw_input_buffer[ index ] );
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

    void Devices::update_device_buffered( RAWINPUT ** in_raw_input_buffer , uint in_buffer_size )
    {
        input_devices.at(0).update_buffered( in_raw_input_buffer , in_buffer_size );
    }

    void Devices::draw()
    {
        //information.draw();
        for( auto & device : input_devices ) device.draw();
    }
}