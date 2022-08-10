#pragma once

#include "..\headers\direct_2d.h"

#include "..\headers\hid_item.h"
// #include "..\headers\hid_local_item.h"

namespace hid
{
    struct hid_collection // HIDP_CAPS
    {
        using identifier = ushort;
        using amount     = ushort;

        ushort        index    {};
        hid_item_type type     { hid_item_type::undefined };
        identifier    page     { 0     };
        identifier    usage    { 0     };
        bool          is_alias { false };
        link          origin   { 0     }; // parent  
        amount        siblings { 0     }; // children
        link          first    { 0     }; // child     
        link          next     { 0     }; // sibling 

    public:

        wstring text();

        bool operator == ( const hid_collection & in_item ) const
        {
            return ( ( in_item.page == page ) && ( in_item.usage == usage ) );
        }
    };
}