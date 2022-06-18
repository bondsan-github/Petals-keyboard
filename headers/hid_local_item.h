#pragma once

#include "..\headers\hid_item.h"
#include "..\headers\hid_main_item.h"

namespace hid
{
    struct hid_local_item : public hid_main_item
    {
        index  report          {};
        ushort report_amount   {};

        ushort bit_field       {};

        bool   is_absolute     {}; // or relative

        ushort origin_usage    {};
        ushort origin_page     {};

        bool   is_range        {};
        range  usages          {};
        index  data            {};
        range  datas           {};

        bool   has_strings     {};
        ushort string          {}; // HidD_GetIndexedString        
        range  strings         {};

        bool   has_designators {};
        ushort designator      {}; // describes body part recommended control. Index points to a designator in the Physical descriptor
        range  designators     {};

        //public:
        //void page( const ushort in_page ) { page = in_page; }

        wstring text();

    }; // struct hid_local_item

} // namespace hid