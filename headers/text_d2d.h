#pragma once

#include "..\headers\constants.h"

#include < string >
#include < wrl.h >

#include < d2d1.h >
#include < dwrite.h >

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;
    
    using ms_text_format        = IDWriteTextFormat;
    using ms_brush_solid_colour = ID2D1SolidColorBrush;
    using ms_text_layout        = IDWriteTextLayout;

    using vertex                = D2D1_POINT_2F;
    using colours               = ColorF;
    using rectangle             = D2D_RECT_F;
    using rounded_rectangle     = D2D1_ROUNDED_RECT;
    using dimensions            = D2D_SIZE_F;

    struct rect_vertex_mid
    {
        vertex top    {};
        vertex right  {};
        vertex bottom {};
        vertex left   {};
    };

    class text
    {
            ComPtr< ms_text_format >        format {}; // simple version of text_layout
            ComPtr< ms_brush_solid_colour > brush  {};
            ComPtr< ms_text_layout >        layout {};

            wstring           content           {};
            vertex            position_center   {};
            vertex            position_top_left {};
            wstring           font              {}; // font family
            float             size              {}; // MS "size * 96.0f/72.0f"
            colours           colour            { ColorF::Yellow };
            float             radius            { 5.0f };
            dimensions        boundry           {};
            rounded_rectangle rrectangle        {};// .radiusX = raduis , .radiusY = radius };

        public:

            text( wstring    in_content = {}                     ,
                  vertex     in_center  = { 0.5f , 0.5f }        , // position 0..1
                  float      in_size    = { 15.0f }              ,
                  colours    in_colour  = { ColorF::Yellow }     ,
                  dimensions in_boundry = { 350.0f , 350.0f }    ,
                  wstring    in_font    = { L"Times New Roman" } );

            float           width();
            float           width_half();
            float           height();
            float           height_half();
            void            position( vertex in_center );
            vertex          top_left();

            void            reset();
            void            reset_brush();
            void            reset_format();
            void            reset_layout();

            void            set_content( wstring in_content );
            void            add( const wstring in_string );

            void            draw();
            void            draw_text();

            rect_vertex_mid middle_vertices();
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