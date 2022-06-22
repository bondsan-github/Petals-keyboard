#pragma once

#include "..\headers\constants.h"

#include "..\headers\hid_item.h"
#include "..\headers\hid_local_item.h"

namespace hid
{
    struct hid_global_item : public hid_local_item
    {
        link       main_item{};

        ushort     bit_amount{};
        ulong      unit_exponent{};
        ulong      unit{};

        bool       has_null{};
        bool       is_absolute{}; // or relative

        limits     physical{};
        limits     logical{};
    };

        // uint usages = identifiers_usage.maximum - identifiers_usage.minumum;
        //for( int index{} ; index < usages ; index++ )

} // namespace hid

