#include "..\headers\hid_raw_device.h"

namespace hid
{
    hid_raw_device::hid_raw_device() 
    {
        OutputDebugString( L"\n hid_raw_device::default constructor" );
    }

    hid_raw_device::hid_raw_device( const hid_raw_device & copy )
    {
        OutputDebugString( L"\n hid_raw_device::copy constructor" );

        if( this != &copy ) *this = copy;
    }

    hid_raw_device::hid_raw_device( hid_raw_device && in_move ) noexcept
    {
        OutputDebugString( L"\n hid_raw_device::move constructor" );

        if( this != &in_move ) *this = std::move( in_move );
    }

    hid_raw_device & hid_raw_device::operator = ( const hid_raw_device & assign_copy )
    {
        OutputDebugString( L"\n hid_raw_device::assign copy" );

        if( this != &assign_copy )
        {
            device_pointer   = assign_copy.device_pointer;
            data_bytes       = assign_copy.data_bytes;
            capabilities     = assign_copy.capabilities;
            page             = assign_copy.page;
            usage            = assign_copy.usage;
        }

        return *this;
    }

    hid_raw_device & hid_raw_device::operator = ( hid_raw_device && assign_move ) noexcept
    {
        OutputDebugString( L"\n hid_raw_device::assign move" );

        if( this != &assign_move )
        {
            device_pointer   = std::move( assign_move.device_pointer );
            data_bytes       = std::move( assign_move.data_bytes );
            capabilities     = std::move( assign_move.capabilities );
            page             = std::move( assign_move.page );
            usage            = std::move( assign_move.usage );

            assign_move.reset();
        }

        return *this;
    }

    hid_raw_device::hid_raw_device( HANDLE in_device ) : device_pointer( in_device )
    {
        OutputDebugString( L"\n hid_raw_device::parametertised constructor" );

        uint data_size { 0 };

        GetRawInputDeviceInfo( device_pointer , request.data , nullptr , & data_size );

        data_bytes.resize( data_size );

        GetRawInputDeviceInfo( device_pointer , request.data , data_bytes.data() , & data_size );

        data_preparsed = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_bytes.data() );

        HidP_GetCaps( data_preparsed , & capabilities );

        page  = capabilities.UsagePage;
        usage = capabilities.Usage;
    }
    
    bool hid_raw_device::is_multi_touch()
    { 
        return ( page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD );
    }

    void hid_raw_device::reset()
    {
        device_pointer = nullptr;
        data_preparsed = nullptr;
        data_bytes.clear();
        capabilities.reset();
        page  = 0;
        usage = 0;
    }

    hid_raw_device::~hid_raw_device() 
    {
        OutputDebugString( L"\n hid_raw_device::de-constructor" );

        device_pointer = nullptr;
        data_preparsed = nullptr;
    }
}