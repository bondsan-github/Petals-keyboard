#pragma once

#include < string >

#include < d2d1.h >
#include < dwrite.h >

#include "..\headers\globals.h"

namespace hid
{
   using namespace D2D1;
   using namespace std;

   class d2d
   {
      protected:

         inline static IDWriteFactory        * write_factory{};
         inline static ID2D1Factory          * factory{};
         inline static ID2D1HwndRenderTarget * render_target{};
         inline static D2D1_SIZE_F             render_target_size{};

         IDWriteTextFormat    * text_format  {}; // simple version of text_layout
         IDWriteTextLayout    * text_layout  {};
         wstring                text_name    { L"Times New Roman" };
         uint                   text_size    { 15 }; // MS"size * 96.0f/72.0f"
         DWRITE_TEXT_METRICS  * text_metrics {};
         ColorF                 text_colour  { ColorF::LightYellow };
         ID2D1SolidColorBrush * text_brush   {};
   };

} // namespace hid