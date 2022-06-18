#include "..\headers\hid_raw_device.h"

//#include "..\headers\globals.h"

namespace hid
{
    using namespace std;

    hid_raw_device::hid_raw_device( HANDLE in_device ) : device( in_device )
    {
        uint data_size {};

        GetRawInputDeviceInfo( device , requests.data , nullptr , & data_size );

        data_vector.resize( data_size );

        GetRawInputDeviceInfo( device , requests.data , data_vector.data() , & data_size );

        data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_vector.data() );

        HIDP_CAPS caps {};

        HidP_GetCaps( data , & caps );

        page        = caps.UsagePage;
        usage       = caps.Usage;
        item_amount = caps.NumberLinkCollectionNodes;

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

        // open i_o device for query 
        file_pointer = CreateFileW( path.data() ,
                                    0 ,                                  // access
                                    FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                    0 ,                                  // security
                                    OPEN_EXISTING ,                      // creation
                                    FILE_ATTRIBUTE_NORMAL ,              // flags
                                    0 );                                 // template


    }

    bool hid_raw_device::is_multi_touch() 
    { 
        return page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD;
    }

} // namespace hid