#pragma once

#include "..\headers\constants.h"

#include < vector >
#include < string >

namespace hid
{
    using namespace std;

    enum class hid_item_type : unsigned long
    {
        undefined          , // 0x00
        physical           , // 0x01
        application        , // 0x02
        logical            , // 0x03
        report             , // 0x04
        named_array        , // 0x05
        usage_switch       , // 0x06
        usage_modifier     , // 0x07
        reserved_start     , //
        // ...
        reserved_end       , // 0x7F
        device             , // 0x80 // vendor_defined_start , // 0x80
        // ...
        vendor_defined_end , // 0xFF ,
    };

    // HID Usage Tables FOR Universal Serial Bus( USB ) Version 1.3
    // usb.org/sites/default/files/hut1_3_0.pdf
    const vector< wstring > hid_item_type_text
    {
        L"undefined"          , //
        L"physical"           , //
        L"application"        , // 
        L"logical"            , // 
        L"report"             , //
        L"named array"        , //
        L"usage switch"       , //
        L"usage modifier"     , //
        L"reserved start"     , //
        L"reserved end"       , //
        L"device"             , //
        L"vendor defined end" , //
    };

    //using link = vector< item >::const_reference;

    using link = ushort;
    //using ⛓   = link;
    
    struct range
    {
        long begin {};
        long end   {};
    };

    using index      = ushort;
    using identifier = index; // ♈♉♊♋♌♍♎♏♐♑♒♓

    struct limits
    {
        long minumum {};
        long maximum {};
    };
    
} // namespace hid
