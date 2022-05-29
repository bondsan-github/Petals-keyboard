#pragma once

#include < string >
#include < d2d1.h >

#include "..\headers\item.h"

namespace hid
{
   using namespace std;

   class text_box 
   {
         wstring   text             {};

         item_type type             {};

         uint      width_device     { 250 };
         uint      height_device    { 100 };

         uint      width_item       { 200 };
         uint      height_item      { 100 };

         // brush

         float             radius   { 5.0f };
         D2D_RECT_F        position { 10.0f , 10.0f , 210.0f , 210.0f };
         D2D1_ROUNDED_RECT rrect    { position , radius , radius };

      public:

         text_box( wstring in_text ) : text( in_text )
         {
            //write_factory->CreateTextLayout();
            //GetMetrics();
         }

         void draw()
         {
            //render_target->DrawTextLayout
            if( render_target )
               render_target->DrawRoundedRectangle( rrect , text_brush );
         }

   };// class text_box
}