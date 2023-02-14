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
        //std::wstring message {};
        
        int result = GetRawInputDeviceList( 0 , & device_amount , sizeof( RAWINPUTDEVICELIST ) );
        if( result < 0 ) error_exit( L"\nget input device list error" );

        raw_device_list.resize( device_amount );

        // get device list
        GetRawInputDeviceList( raw_device_list.data() , & device_amount , sizeof( RAWINPUTDEVICELIST ) );

        //message = L"\ndevices amount: " + std::to_wstring( device_amount ) + L"\n";
        //OutputDebugStringW( message.data() );

        device_identity identity {};
        uint device_index {0}; // 4 / 8 /11
        uint device_multiple_touch_index { 0 };
        
        // find first precision touchpad
        for( ; device_index < raw_device_list.size() ; device_index++ )
        {
            //message = L"\ndevice index: " + std::to_wstring( device_index );
            //OutputDebugStringW( message.data() );

            hid_device new_device( raw_device_list.at(device_index).hDevice);

            if( new_device.is_multi_touch() )
            {
                //message = L"\nmulti touch device at index: " + std::to_wstring( device_index );
                //OutputDebugStringW( message.data() );

                device_multiple_touch_index = device_index;
                identity = new_device.get_identity();

                input_devices.push_back( new_device );
                
                // Register Raw Input Devices
                locate::get_windows().register_input_device( new_device.get_page_and_usage() );

                break; // leaves iterator at current position
            }
        }
        
        /*
        device_index = 0;
        // find same device in raw devices list
        for( ; device_index < raw_device_list.size() ; device_index++ )
        {
            // dont re-add multiple touch device
            if( device_index == device_multiple_touch_index )
            {
                message = L"\nskipping index: " + std::to_wstring( device_index );
                OutputDebugStringW( message.data() );
            }
            else
            {
                message = L"\ndevice index: " + std::to_wstring( device_index );
                OutputDebugStringW( message.data() );

                hid_device new_device( raw_device_list.at( device_index ).hDevice );
            
                if( new_device.is_same_device( identity ) )
                {
                    message = L"\nadding device index: " + std::to_wstring( device_index );
                    OutputDebugStringW( message.data() );

                    input_devices.push_back( new_device );
                }
            }
        }
        */
        raw_device_list.clear();

        for( auto & device : input_devices )
        {
            device.collect_information();
        }

        //if( input.empty() )
        //    information.set_content( L"no precision multiple touch devices found" );
    }

    hid_device * hid_devices::get_device( HANDLE in_handle )
    {
        hid_device * pointer_device{ nullptr };

        for( auto & device : input_devices )
            if( device.get_handle() == in_handle )
            {
                pointer_device = &device;
                break;
            }

        return pointer_device;
    }

    // multiple devices
    void hid_devices::update_devices( RAWINPUT * in_hid_report )
    {
        for( auto & device : input_devices ) 
        {
            if( device.get_handle() == in_hid_report->header.hDevice )
                //device.update( in_hid_report.data.hid );
                device.update( in_hid_report );
                //device.update();
        }
    }

    void hid_devices::update_devices_buffered( RAWINPUT ** in_raw_input_buffer , uint in_buffer_size )
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

    void hid_devices::update_device_buffered( RAWINPUT ** in_raw_input_buffer , uint in_buffer_size )
    {
        input_devices.at(0).update_buffered( in_raw_input_buffer , in_buffer_size );
    }

    void hid_devices::draw()
    {
        //information.draw();
        for( auto & device : input_devices ) device.draw();
    }
}