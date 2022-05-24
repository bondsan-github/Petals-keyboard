#pragma once

#include < string >

#include "window.h"

class text_box : public d2d
{
   using namespace std;

   //text_box() { }; // "If any non - default constructors are declared , the compiler doesn't provide a default constructor" 
   private:

      wstring           text{};

      float             radius{};
      D2D_RECT_F        rectagle{};
      D2D1_ROUNDED_RECT rounded_rectangle{};

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
};
