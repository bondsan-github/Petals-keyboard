#include "..\headers\hid_raw_device.h"

//#include <hidpi.h>
//#include <hidsdi.h>

namespace hid
{
    //hid_raw_device::hid_raw_device() { //OutputDebugString( L"hid_raw_device::default constructor\n" ); }
   
   /*
    hid_raw_device::hid_raw_device( const hid_raw_device & copy )
    {
        //OutputDebugString( L"hid_raw_device::copy constructor\n" );

        if( this != &copy ) *this = copy;
    }

    hid_raw_device::hid_raw_device( hid_raw_device && in_move ) noexcept
    {
        //OutputDebugString( L"hid_raw_device::move constructor\n" );

        if( this != &in_move ) *this = std::move( in_move );
    }
    
    hid_raw_device & hid_raw_device::operator = ( const hid_raw_device & assign_copy )
    {
        //OutputDebugString( L"hid_raw_device::assign copy\n" );

        if( this != &assign_copy )
        {
            device_pointer   = assign_copy.device_pointer;
            data_preparsed   = assign_copy.data_preparsed;
            capabilities     = assign_copy.capabilities;
            page             = assign_copy.page;
            usage            = assign_copy.usage;
        }

        return *this;
    }

    hid_raw_device & hid_raw_device::operator = ( hid_raw_device && assign_move ) noexcept
    {
        //OutputDebugString( L"hid_raw_device::assign move\n" );

        if( this != &assign_move )
        {
            device_pointer   = std::move( assign_move.device_pointer );
            data_preparsed   = std::move( assign_move.data_preparsed );
            capabilities     = std::move( assign_move.capabilities );
            page             = std::move( assign_move.page );
            usage            = std::move( assign_move.usage );

            //assign_move.reset();
        }

        return *this;
    }
    */

    hid_raw_device::hid_raw_device( const HANDLE &in_device ) 
    {
        //OutputDebugString( L"hid_raw_device::parametertised constructor\n" );
        //https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/

        device_pointer = in_device;

        NTSTATUS result { HIDP_STATUS_INVALID_PREPARSED_DATA };
        uint data_size { 0 };

        //RIDI_DEVICEINFO
        GetRawInputDeviceInfoW( device_pointer , request.data , nullptr , & data_size );

        data_preparsed.resize( data_size );
        
        GetRawInputDeviceInfoW( device_pointer , request.data , data_preparsed.data() , & data_size );
        //GetRawInputDeviceInfoW( device_pointer , request.data , data , & data_size );

        //GetPreparsedData( device_pointer , data );
        // getcaps requires * _hidp_preparsed_data = incomplete type not allowed
        result = HidP_GetCaps( reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) , &capabilities);

        page  = capabilities.UsagePage;
        usage = capabilities.Usage;
    }
    
    bool hid_raw_device::is_multi_touch()
    { 
        return ( page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD );
    }

    /*
    void hid_raw_device::reset()
    {
        device_pointer = nullptr;
        data_preparsed.clear();
        capabilities.reset();
        page  = 0;
        usage = 0;
    }
    */

    /*
    hid_raw_device::~hid_raw_device() 
    {
        //OutputDebugString( L"hid_raw_device::de-constructor\n" );
        //device_pointer = nullptr;
        //data_preparsed.clear();
    }
    */
}