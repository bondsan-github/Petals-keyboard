#pragma once

#include < windows.h >
#include < string >
#include < d2d1.h >
#include < dwrite.h >

#include "globals.h"

namespace hid
{
   using namespace std;
   using namespace D2D1;

   struct window
   {
      protected:

         static HWND pointer;
   };

   struct d2d
   {
      protected:

         static IDWriteFactory        * write_factory;
         
   };
   
   class main_window : public window , public d2d// abstract
   {
      protected: // variables

         HWND                   ptr_parent   {};
   };

} // namespace hid