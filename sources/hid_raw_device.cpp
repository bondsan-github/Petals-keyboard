#include "..\headers\hid_raw_device.h"

namespace hid
{
    using namespace std;

    hid_raw_device::hid_raw_device() 
    {
        OutputDebugString( L"\n hid_raw_device::default constructor" );
    }

    hid_raw_device::hid_raw_device( HANDLE in_device ) : device( in_device )
    {
        OutputDebugString( L"\n hid_raw_device::parametertised constructor" );

        uint data_size { 0 };

        GetRawInputDeviceInfo( device , requests.data , nullptr , & data_size );

        data_vector.resize( data_size );

        GetRawInputDeviceInfo( device , requests.data , data_vector.data() , & data_size );

        data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_vector.data() );

        HIDP_CAPS caps {};

        HidP_GetCaps( data , & caps );

        page              = caps.UsagePage;
        usage             = caps.Usage;
        collection_amount = caps.NumberLinkCollectionNodes;

        input.byte_amount              = caps.InputReportByteLength;
        input.button_amount            = caps.NumberInputButtonCaps;
        input.value_amount             = caps.NumberInputValueCaps;
        input.data_identifier_amount   = caps.NumberInputDataIndices;

        output.byte_amount             = caps.OutputReportByteLength;
        output.button_amount           = caps.NumberOutputButtonCaps;
        output.value_amount            = caps.NumberOutputValueCaps;
        output.data_identifier_amount  = caps.NumberOutputDataIndices;

        feature.byte_amount            = caps.FeatureReportByteLength;
        feature.button_amount          = caps.NumberFeatureButtonCaps;
        feature.value_amount           = caps.NumberFeatureValueCaps;
        feature.data_identifier_amount = caps.NumberFeatureDataIndices;

        uint path_char_amount {};

        GetRawInputDeviceInfo( device , requests.path , nullptr , & path_char_amount );

        path.resize( path_char_amount );

        GetRawInputDeviceInfo( device , requests.path , path.data() , & path_char_amount );  // wchar_t

        OutputDebugString( path.data() );

        // open i_o device for query 
        file_pointer = CreateFileW( path.data() ,
                                    0 ,                                  // access
                                    FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                    0 ,                                  // security
                                    OPEN_EXISTING ,                      // creation
                                    FILE_ATTRIBUTE_NORMAL ,              // flags
                                    0 );                                 // template


    }

    hid_raw_device::hid_raw_device( const hid_raw_device & copy ) 
    {
        OutputDebugString( L"\n hid_raw_device::copy constructor" );

        device = copy.device;
        page = copy.page;
        usage = copy.usage;

        file_pointer = copy.file_pointer;
        path = copy.path;
    }

    //hid_raw_device::hid_raw_device( const hid_raw_device && move )// noexcept { OutputDebugString( L"\n hid_raw_device::move constructor" ); * this = move; }

    //hid_raw_device & hid_raw_device::operator = ( const hid_raw_device & assignment ) { OutputDebugString( L"\n hid_raw_device::assignment constructor" ); return * this; }

    //hid_raw_device & hid_raw_device::operator = ( const hid_raw_device && assignment_move )// noexcept { OutputDebugString( L"\n hid_raw_device::assignment move constructor" ); return * this; }

    hid_raw_device::~hid_raw_device( void )
    {
        OutputDebugString( L"\n hid_raw_device::de-constructor" );

        CloseHandle( file_pointer );
    }

    bool hid_raw_device::is_multi_touch() const
    { 
        return ( page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD );
    }

}