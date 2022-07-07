#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
    class text
    {
        private:

            ComPtr< text_format >   format {}; // simple version of text_layout
            ComPtr< brush_solid >   brush  {}; 
            ComPtr< text_layout >   layout {};
            font_collection_pointer collection {};

            string                content           { L"empty " };
            string                locale            { L"en-us" };
            vertex                position_center   { 0.5 , 0.5 }; // position 0..1
            vertex                position_top_left {}; // in pixels
            string                font              { L"Times New Roman" }; // font family
            float                 size              { 15.0f }; // * dpi? // MS "size * 96.0f/72.0f"
            colours               colour            { colours::Yellow };
            brush_opactiy         opacity           { 1.0f                                  };
            text_style            style             { text_style::normal };
            text_weight           weight            { text_weight::regular };
            text_stretch          stretch           { text_stretch::normal };
            text_options          options           { text_options::none                    };
            // collection
            // family
            // spacing
            // trimming
            // wrapping
            // alignment_vertical
            // alignment_horizontal
            // direction_reading
            // direction_flow
            dimensions            boundry        { 150.0f , 150.0f };
            float                 boundry_width  { 2.0f };
            colours               boundry_colour { colours::AliceBlue };
            float                 radius            { 5.0f                                  };
            rounded_rectangle     rrectangle        { .radiusX = radius , .radiusY = radius };

            bool                  show_boundry      { true                                  };
            
        private:
            
            void reset();
            void reset_brush();
            void reset_format();
            void reset_layout();
            void reset_boundry();

            vertex top_left();

            void draw_text();
            void draw_boundry();

        public:

                  text( string in_content = L"empty" ,
                        vertex position_center = { 0.5f , 0.5f } ,
                        float size = { 10.0f } ,
                        colours in_colour = colours::Yellow );
            float width();
            float width_half();
            float height();
            float height_half();
            void  position( vertex in_center );
            
            void  set_content( string in_content );
            void  add( const string in_string );
            void  set_colour( colours in_colour );
            void  set_boundry( dimensions in_dimensions );
            void  set_boundry_colour( colours in_colour );
            void  set_boundry_width( float in_width );
            void  draw();

            rectangle_edge_middles middle_vertices();
            /*
            struct planes
            {
                float horizontal {};
                float vertical   {};
            };
            planes middle_planes( float in_width , float in_height )
            */
    }; // class text

} // namespace hid