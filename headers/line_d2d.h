#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
    class line_d2d 
    {
        private:

            vertex                  a      {};
            vertex                  b      {};
            float                   width  { 1.0f };
            colours                 colour { D2D1::ColorF::Yellow };
            //ID2D1SolidColorBrush & brush;
            brush_solid_pointer brush {};
            ComPtr< stroke_style >  style  {};

        public:

            line_d2d( vertex in_a = { 0.0f , 0.0f } ,
                      vertex in_b = { 1.0f , 1.0f } ,
                      float in_width = 1.0f ,
                      colours in_colour = colours( 0.4f , 0.4f , 0.2f , 0.2f ) );

            void reset();

            void draw();

    };

}