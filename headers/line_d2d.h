#pragma once

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    class line_d2d 
    {
        private:

            point                             a      {};
            point                             b      {};
            float                             width  {};
            colours                           colour { ColorF::Yellow };
            ComPtr< ms_brush_solid_colour  >  brush  {};
            ComPtr< ms_stroke_style >         style  {};

        public:

                 line_d2d( point in_a ,
                       point in_b ,
                       float in_width = 1.0f ,
                       colours in_colour = colours( 0.4f , 0.4f , 0.2f , 0.2f ) );
            void draw();

    }; // class line

} // namespace hid