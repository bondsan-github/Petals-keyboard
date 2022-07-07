#pragma once

#include "..\headers\direct_2d.h"

#include "..\headers\hid_item.h"

namespace hid
{
 
    struct hid_main_item // HIDP_CAPS
    {
        hid_item_type type     { hid_item_type::undefined };

        ushort        page     {};
        ushort        usage    {};
        bool          is_alias {};
        link          origin   {}; // parent  
        ushort        amount   {}; // children
        link          first    {}; // child    
        link          next     {}; // sibling 

        wstring text();
    };
}