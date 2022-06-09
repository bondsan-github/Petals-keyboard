#pragma once

#include < windows.h >

namespace hid
{
    struct shared_window_pointer
    {
       inline static HWND window_ptr {};
    };
}