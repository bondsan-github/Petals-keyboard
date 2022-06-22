#pragma once

#include "..\headers\constants.h"

#include < d2d1.h >
#include < wrl.h >

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    using vertex                = D2D1_POINT_2F;
    using colours               = ColorF;
    using ms_stroke_style       = ID2D1StrokeStyle;
    using ms_brush_solid_colour = ID2D1SolidColorBrush;

    class line_d2d 
    {
        private:

            vertex                            a      {};
            vertex                            b      {};
            float                             width  {};
            colours                           colour { D2D1::ColorF::Yellow };
            ComPtr< ms_brush_solid_colour  >  brush  {};
            ComPtr< ms_stroke_style >         style  {};

        public:

            line_d2d( vertex in_a ,
                      vertex in_b ,
                      float in_width = 1.0f ,
                      colours in_colour = colours( 0.4f , 0.4f , 0.2f , 0.2f ) );

            void reset();

            void draw();

    }; // class line

} // namespace hid