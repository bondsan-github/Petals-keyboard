#pragma once

#include < wrl.h >
#include < d2d1.h >

#include "..\headers\globals.h"
#include "..\headers\locate.h"

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    class line 
    {
        private:

            point                             a      {};
            point                             b      {};
            float                             width  {};
            colours                           colour { ColorF::Yellow };
            ComPtr< ms_brush_solid_colour  >  brush  {};
            ComPtr< ms_stroke_style >         style  {};

        public:

            line( point in_a ,
                  point in_b ,
                  float in_width = 1.0f ,
                  colours in_colour = colours( 0.4f , 0.4f , 0.2f , 0.2f ) )
                : a( in_a ) , b( in_b ) , width( in_width ) , colour( in_colour )
            {
                graphics * graphics_ptr = locate::get_graphics();

                graphics_ptr->sheet_pointer()->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );
            
                //factory->createStrokeStyle
            };

            void draw()
            {
                if( locate::get_graphics()->sheet_pointer() )
                    locate::get_graphics()->sheet_pointer()->DrawLine( a , b , brush.Get() , width , style.Get() );
            }
    };

}