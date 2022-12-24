#include "..\headers\hid_raw_device.h"

namespace hid
{
    using namespace std;

    // hid_raw_device::hid_raw_device() { OutputDebugString( L"\n hid_raw_device::default constructor" ); }

    hid_raw_device::hid_raw_device( HANDLE in_device ) : device_pointer( in_device )
    {
        //OutputDebugString( L"\n hid_raw_device::parametertised constructor" );

        uint data_size { 0 };

        GetRawInputDeviceInfo( device_pointer , request.data , nullptr , & data_size );

        data_bytes.resize( data_size );

        GetRawInputDeviceInfo( device_pointer , request.data , data_bytes.data() , & data_size );

        data_preparsed = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_bytes.data() );

        HidP_GetCaps( data_preparsed , & capabilities );

        page              = capabilities.UsagePage;
        usage             = capabilities.Usage;
    }
    
    bool hid_raw_device::is_multi_touch()
    { 
        return ( page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD );
    }

    //hid_raw_device::~hid_raw_device( void ) { OutputDebugString( L"\n hid_raw_device::de-constructor" ); }
}