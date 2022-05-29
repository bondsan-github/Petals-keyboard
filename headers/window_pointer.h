#pragma once

#include < windows.h >

struct window_pointer
{
   inline static HWND window_ptr {};

   ~window_pointer()
   {// window_ptr;
   //   window_ptr = nullptr;
   }
};
