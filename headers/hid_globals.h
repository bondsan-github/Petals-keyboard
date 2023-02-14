#pragma once

#include "..\headers\custom_types.h"

#include <hidpi.h>
#include <hidsdi.h>

#include <dwrite.h>
#include <vector>

namespace hid
{
    const enum class item_type { input , output , feature };

    struct device_identity
    {
        ulong vendor  {};
        ulong product {};

        bool operator == ( const device_identity & in_identity ) const
        {
            bool same = false;
             same = ( vendor == in_identity.vendor && product == in_identity.product );
             return same;
        }
    };

    struct page_and_usage
    {
        unsigned short page  {};
        unsigned short usage {};
    };

    struct report
    {
        ushort byte_amount            { 0 };

        ushort button_amount          { 0 };
        ushort value_amount           { 0 };
        ushort data_identifier_amount { 0 };

        //std::vector< hid_local_item >  buttons { 0 };
        //std::vector< hid_global_item > values  { 0 };

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

    const struct requests
    {
        uint data = ( 1 << 29 ) | 0x5; // 0x20'000'005
        uint path = ( 1 << 29 ) | 0x7; // return value in character amount, not byte size
        uint info = ( 1 << 29 ) | 0xB;
    };


    // was for reseting to known state after moving 

    class hid_capabilities : public _HIDP_CAPS
    {
        public:
    
        hid_capabilities() { reset(); }

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

    class hid_attributes : public _HIDD_ATTRIBUTES
    {
        public:

            hid_attributes() { reset(); }

            void reset()
            {
                Size          = 0;//sizeof( *this ); //sizeof( hid_attributes )
                VendorID      = 0;
                ProductID     = 0;
                VersionNumber = 0;
            }
    };

    class hid_attributes_extended : public _HIDP_EXTENDED_ATTRIBUTES
    {
        public:

            hid_attributes_extended() { reset(); }

            void reset()
            {
                NumGlobalUnknowns = 0;
                memset( Reserved , 0 , sizeof( uchar ) * 3 );
                GlobalUnknowns    = nullptr;
                memset( Data     , 0 , sizeof( ulong ) );
            }
    };

    class text_metrics : public DWRITE_TEXT_METRICS
    {
        public:

            text_metrics() { reset(); }

            void reset()
            {
                left         = 0.0f; // in device independant pixels
                top          = 0.0f;
                width        = 0.0f;
                widthIncludingTrailingWhitespace = 0.0f;
                height       = 0.0f;
                layoutWidth  = 0.0f;
                layoutHeight = 0.0f;
                maxBidiReorderingDepth = 0u;
                lineCount    = 0u;
            }
    };

} // namespace hid