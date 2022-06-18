#pragma once

#include "..\headers\hid_item.h"

namespace hid
{
    // HIDP_CAPS
    struct hid_main_item
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

    }; // struct_main_item

} // namespace hid