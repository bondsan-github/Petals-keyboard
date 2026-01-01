#pragma once

#include "Custom types.h"

//#include <hidpi.h>
#include <hidsdi.h>
#include <WinUser.h>

namespace HID
{
    using collection_node = _HIDP_LINK_COLLECTION_NODE;
    using button_caps     = _HIDP_BUTTON_CAPS;
    using value_caps      = _HIDP_VALUE_CAPS;
    using raw_device_list = RAWINPUTDEVICELIST;

    enum class report_type     { input, output, feature };
    enum class value_type      { logical, physical, usage, string, disignator, data_index };
    enum class raw_device_type { mouse, keyboard, hid }; // Microsoft windows input types
    //const vector< wstring > raw_device_type_text{ L"Mouse", L"Keyboard", L"Human interface device", L"unknown device type" };

    struct Identity
    {
        ulong vendor  {};
        ulong product {};

        bool operator == ( const Identity & identity ) const
        {
            return vendor == identity.vendor && product == identity.product;
        }
    };

    struct Report
    {
        ushort byte_amount            {};
        ushort button_amount          {};
        ushort value_amount           {};
        ushort data_identifier_amount {};

        //std::vector< hid_local_item >  buttons {};
        //std::vector< hid_global_item > values  {};

        void reset()
        {
            byte_amount            = 0u; // change from assign = to initialisation {}
            button_amount          = 0u;
            value_amount           = 0u;
            data_identifier_amount = 0u;
            //buttons.clear();
            //values.clear();
        }
    };

    const struct Requests
    {
        uint data = ( 1 << 29 ) | 0x5; // 0x20'000'005
        uint path = ( 1 << 29 ) | 0x7; // return value in character amount, not byte size
        uint info = ( 1 << 29 ) | 0xB;
    };

    struct Range
    {
        long minimum{ 0 };
        long maximum{ 0 };

        //range() {}
        //range( const long & in_minimum , const long & in_maximum ) : minimum( in_minimum ) , maximum( in_maximum ) {}
    };

} // namespace hid

    // was for reseting to known state after moving 
    /*
    class Capabilities : public _HIDP_CAPS
    {
        public:
    
        Capabilities() { reset(); }

        //hid_capabilities( HIDP_CAPS & in_caps ) { }
        
        void reset()
        {
            Usage                     = 0;
            UsagePage                 = 0;

            InputReportByteLength     = 0;
            OutputReportByteLength    = 0;
            FeatureReportByteLength   = 0;

            memset( Reserved , 0 , sizeof(ushort) * 17 );

            NumberLinkCollectionNodes = 0;

            NumberInputButtonCaps     = 0;
            NumberInputValueCaps      = 0;
            NumberInputDataIndices    = 0;

            NumberOutputButtonCaps    = 0;
            NumberOutputValueCaps     = 0;
            NumberOutputDataIndices   = 0;

            NumberFeatureButtonCaps   = 0;
            NumberFeatureValueCaps    = 0;
            NumberFeatureDataIndices  = 0;
        }
    };

    class Attributes : public _HIDD_ATTRIBUTES
    {
        public:

            Attributes() { reset(); }

            void reset()
            {
                Size          = 0;//sizeof( *this ); //sizeof( hid_attributes )
                VendorID      = 0;
                ProductID     = 0;
                VersionNumber = 0;
            }
    };

    class Attributes_extended : public _HIDP_EXTENDED_ATTRIBUTES
    {
        public:

            Attributes_extended() { reset(); }

            void reset()
            {
                NumGlobalUnknowns = 0;
                
                memset( Reserved , 0 , sizeof( uchar ) * 3 );

                GlobalUnknowns    = nullptr;

                memset( Data     , 0 , sizeof( ulong ) );
            }
    };
*/
   

