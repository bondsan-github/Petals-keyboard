#pragma once

namespace hid
{
    using namespace std;
    using namespace Microsoft::WRL;

    class text
    {
            ComPtr< ms_text_format >        format {}; // simple version of text_layout
            ComPtr< ms_brush_solid_colour > brush  {};
            ComPtr< ms_text_layout >        layout {};

            wstring           content    {};
            point             center     {}; // from top left
            wstring           font       { L"Times New Roman" }; // font family
            float             size       { 15.0f }; // MS "size * 96.0f/72.0f"
            colours           colour     { colours::Yellow };
            area              dimensions {};
            float             radius     { 5.0f };
            rectangle         bounds     {};
            rounded_rectangle rrectangle {};// .radiusX = raduis , .radiusY = radius };

        public:

            text( wstring                 in_content    = {}                     ,
                  point                   in_center     = { 0.5f , 0.5f }        , // position 0..1
                  float                   in_size       = { 15u }                ,
                  colours                 in_colour     = { colours::Yellow }    ,
                  area                    in_dimensions = { 150.0f , 100.0f }    ,
                  wstring                 in_font       = { L"Times New Roman" } );

            float           width();
            float           width_half();
            float           height();
            float           height_half();
            //void          position( point in_center );
            point           top_left();

            void            reset();
            void            reset_brush();
            void            reset_format();
            void            reset_layout();

            void            set_content( wstring in_content );
            void            add( const wstring in_string );

            void            draw();
            void            draw_text();

            rect_points_mid middle_points();
            /*
            void reset_bounds()
            void draw_bounds()
            struct planes
            {
                float horizontal {};
                float vertical   {};
            };
            planes middle_planes( float in_width , float in_height )
            */
    }; // class text

} // namespace hid