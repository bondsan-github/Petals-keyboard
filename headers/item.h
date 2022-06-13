#pragma once

#include < vector >
#include < bitset >

#include "..\headers\globals.h"
#include "..\headers\usages.h"
//#include "..\headers\text.h"

namespace hid
{
    using namespace std;

    enum class item_type : unsigned long
    {
        undefined          , //
        physical           , // 0x00
        application        , // 0x01
        logical            , // 0x02
        report             , // 0x03
        named_array        , // 0x04
        usage_switch       , // 0x05
        usage_modifier     , // 0x06
        reserved_start     , // 0x07
        // ...
        reserved_end       , // 0x7F
        device             , // 0x80 // vendor_defined_start , // 0x80
        // ...
        vendor_defined_end , // 0xFF ,
    };

       // HID Usage Tables FOR Universal Serial Bus( USB ) Version 1.3
       // usb.org/sites/default/files/hut1_3_0.pdf
    const vector< wstring > item_type_text
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

    //using  link = vector< item >::const_reference;

    using link = ushort;
    //using ⛓   = link;

    // HIDP_CAPS
    struct main_item //: public write
    {
        item_type type     { item_type::undefined };

        ushort    page     {};
        ushort    usage    {};

        bool      is_alias {};

        link      origin   {}; // parent  
        ushort    amount   {}; // children
        link      first    {}; // child    
        link      next     {}; // sibling 

        wstring text() const
        {
            wstring text;

            text  = L"type\t: ";
            text += item_type_text.at( to_underlying( type ) );
            text += L"\npage\t: ";
            text += usages.page( page );
            text += L"\nusage\t: ";
            text += usages.usage( page , usage );

            if( amount )
            {
                text += L"\nlink amount\t: ";
                text += to_wstring( amount );
            }

            if( origin )
            {
                text += L"\norigin\t: ";
                text += to_wstring( origin );
            }

            if( next )
            {
                text += L"\nnext\t: ";
                text += to_wstring( next );
            }

            if( first )
            {
                text += L"\nfirst\t: ";
                text += to_wstring( first );
            }

            return text;
        }
    };
    
    struct range
    {
        long begin {};
        long end   {};
    };

    using index      = ushort;
    using identifier = index; // ♈♉♊♋♌♍♎♏♐♑♒♓

    struct local_item 
    {
        ushort page          {};

        index  report        {};
        ushort report_amount {};

        ushort bit_field     {};

        bool   is_alias      {};
        bool   is_absolute   {}; // or relative

        link   origin        {};
        ushort origin_usage  {};
        ushort origin_page   {};
        
        bool   is_range      {};
        ushort usage         {};
        range  usages        {};
        index  data          {};
        range  datas         {};

        bool   has_strings   {};
        ushort string        {}; // HidD_GetIndexedString        
        range  strings       {};

        bool   has_designators {};
        ushort designator      {}; // Determines the body part used for a control. Index points to a designator in the Physical descriptor
        range  designators     {};

        //public:
        //void page( const ushort in_page ) { page = in_page; }

        wstring text() const
        {
            wstring text;
        
            text += L"\npage\t: ";
            text += hid::usages.page( page );

            if( is_range )
            {
                text += L"\nusages\t: ";
            }
            else
            {
                text += L"\nusage\t: ";
                text += hid::usages.usage( page , usage );
            }

            text += L"\nreport\t: ";
            text += to_wstring( report );
            
            if( report_amount )
            { 
                text += L"\nreport amount\t: ";
                text += report_amount;
            }

            if( bit_field )
            {
                text += L"\nbit field\t: ";
                text += bitset<16>( bit_field ).to_string< wchar_t , char_traits<wchar_t>, allocator<wchar_t> >();
            }

            //text += is_absolute; // or relative
            //text += has_strings;
            //text += has_designators;

            return text;
        }
    };


    struct limits
    {
        long minumum{};
        long maximum{};
    };


    struct global_item
    {
        ushort     page            {};
        identifier report          {};
        link       main_item       {};
        
        ushort     bit_field       {}; 
        
        ushort     bit_amount      {};
        ulong      unit_exponent   {};
        ulong      unit            {};
        
        ushort     report_amount   {};

        bool       is_alias        {};
        bool       has_null        {};
        bool       is_absolute     {}; // or relative
        bool       is_range        {}; //
        bool       has_strings     {};
        bool       has_designators {};

        link       origin          {};
        ushort     origin_usage    {};
        ushort     origin_page     {};

        limits     physical        {};
        limits     logical         {};
    };
        // uint usages = identifiers_usage.maximum - identifiers_usage.minumum;
        //for( int index{} ; index < usages ; index++ )

        

} // namespace hid
