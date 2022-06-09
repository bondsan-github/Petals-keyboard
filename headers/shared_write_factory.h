#pragma once

#include "..\headers\globals.h"

//#include < windows.h >
#include < wrl.h >
//#include < d2d1.h >
#include < dwrite.h >

namespace hid
{
    using namespace Microsoft::WRL;

    struct shared_write_factory
    {
        static inline Microsoft::WRL::ComPtr< IDWriteFactory > write_factory {};
    };

}
