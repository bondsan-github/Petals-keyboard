#pragma once

#include < string >
#include < d2d1.h >

#include "..\headers\main_window.h"

namespace hid
{
   using namespace std;

   class text_box : public d2d
   {
      private:

         wstring           text{};

         uint      width_device{ 250 };
         uint      height_device{ 100 };

         uint      width_item{ 200 };
         uint      height_item{ 100 };


         float             radius            { 5.0f };
         D2D_RECT_F        rectagle          {};
         D2D1_ROUNDED_RECT rounded_rectangle {};

      public:

      text_box( wstring in_text ) : text( in_text )
      {
         //write_factory->CreateTextLayout();
         //GetMetrics();
      }

      void draw()
      {
         //render_target->DrawTextLayout

         //render_target->DrawRoundedRectangle( rrect , text_brush );
      }

   };// class text_box
}