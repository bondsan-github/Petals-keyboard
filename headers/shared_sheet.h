#pragma once

#include < wrl.h >
#include < d2d1.h >

#include "..\headers\globals.h"

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    struct shared_sheet
    {
        static inline ComPtr< window_render_target > sheet{};
    };
}