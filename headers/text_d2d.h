//https://learn.microsoft.com/en-us/windows/win32/direct2d/improving-direct2d-performance#use-a-multithreaded-device-context
//https://learn.microsoft.com/en-us/windows/win32/directwrite/rendering-by-using-direct2d
#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
    class text
    {
        private: // variables

            //text_format_pointer     format     {};
            IDWriteTextFormat * format;
            //brush_solid_pointer     brush      {}; 
            ID2D1SolidColorBrush * brush;
            //text_layout_pointer     layout     {};
            IDWriteTextLayout * layout;
            //font_collection_pointer collection {};
            //ComPtr< IDWriteFontCollection > collection;

            string                content           { L"empty"             };
            string                font_locale       { L"en-us"             }; // en-GB
          //vertex                position_center   { 10.0f , 10.0f        }; // dips
            vertex                position_top_left { 0.0f , 0.0f          }; // in dips
            string                font_face         { L"Times New Roman"   }; // font family
            float                 font_size         { 15.0f                }; // * dpi? // MS "size * 96.0f/72.0f"
            colours               font_colour       { colours::Yellow      };
            float                 font_opacity      { 1.0f                 };
            //font_style            _font_style       { font_style::normal   };
            DWRITE_FONT_STYLE     font_style { DWRITE_FONT_STYLE_NORMAL };
            DWRITE_FONT_WEIGHT    font_weight { DWRITE_FONT_WEIGHT_NORMAL };
            //font_weight         font_weight      { font_weight::regular };
            DWRITE_FONT_STRETCH   font_stretch     { DWRITE_FONT_STRETCH_NORMAL };
            //font_options          font_options     { font_options::none   };
            // collection
            // family
            // spacing
            // trimming
            // wrapping
            // alignment_vertical
            // alignment_horizontal
            // direction_reading
            // direction_flow
            
            // A DIP equals 1 / 96 inch = 0.3 mm 
            D2D1_SIZE_F           layout_size      { 150.0f , 150.0f    };
            DWRITE_TEXT_METRICS   layout_metrics   {                    };

            //float paragraph_width { 100 };
            
            bool                  rectangle_show   { false               };
            rectangle             rectangle_size   { 150.0f , 150.0f };
            float                 rectangle_inner_margin { 0.0f               };
            float                 rectangle_line_width  { 1.0f               };
            colours               rectangle_line_colour { colours::Yellow    };
            float                 rectangle_radius { 0.0f               };
            D2D1_ROUNDED_RECT     rounded_rectangle{ .radiusX = rectangle_radius ,
                                                     .radiusY = rectangle_radius };
            
        private: // functions
            
            void reset           ();
            void reset_format    ();
            void reset_layout    ();
            void reset_rectangle ();
            void reset_brush     ();
            
            D2D1_SIZE_F get_layout_size() { return layout_size; }
            float  get_layout_width       ();
            float  get_layout_width_half  ();
            float  get_layout_height      ();
            float  get_layout_height_half ();
            planes get_middle_planes();

            void draw_text();
            void draw_rectangle();
            
        public:

            //text( void );
            //~text( void );
            //text( text const &  copy );
            //text( text && move );
            //text & operator = (  text const &  assignment );
            //text & operator = (  text const && assignment_move );
            
            void    set_content( string in_content );
            string  get_content() { return content; }
            void    add_content( string in_string       ); // add to end
            void    set_font_locale( string in_locale );
            string  get_font_locale() { return font_locale; }
            void    set_font_face( string in_font_face );
            void    set_font_size( float in_font_size );
            void    set_font_colour( colours in_font_colour ); // bool true set worked false set failed
            void    set_font_opacity( float in_font_opacity );
            void    set_font_style( DWRITE_FONT_STYLE in_font_style );
            void    set_font_weight( DWRITE_FONT_WEIGHT in_font_weight );
            void    set_font_stretch( DWRITE_FONT_STRETCH in_font_stretch );
            //void  set_font_options( font_options in_font_options );
            //font_options get_font_options();
            void    set_position_top_left( vertex in_position );
            vertex  get_position_top_left();
            void    set_layout_size( D2D1_SIZE_F in_layout_size );
            //dimensions   get_layout_size();
            void    set_rectangle_size( rectangle in_rectangle_size );
            //rectangle get_rectangle_size() ;
            void    set_rounded_rectangle_radius( float in_radius );
            void    set_rectangle_line_colour( colours in_colour );
            void    set_rectangle_line_width( float in_width );

            rectangle_edge_middles get_middle_vertices();
            //rectangle              get_formated_rectangle();

            void draw();

    }; // class text

} // namespace hid