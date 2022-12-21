#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
    class text
    {
        private: // variables

            //text_format_pointer     format     {};
            ComPtr< IDWriteTextFormat > format { nullptr };
            //ID2D1SolidColorBrush brush;
            //brush_solid_pointer     brush      {}; 
            ComPtr< ID2D1SolidColorBrush > brush { nullptr };
            //text_layout_pointer     layout     {};
            ComPtr< IDWriteTextLayout > layout { nullptr };
            //font_collection_pointer collection {};
            ComPtr< IDWriteFontCollection > collection { nullptr };

            string                content           { L"empty"             };
            string                font_locale       { L"en-us"             };
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
            
            dimensions            layout_size      { 150.0f , 150.0f    };
            text_metrics          layout_metrics   {                    };
            
            bool                  rectangle_show   { true               };
            rectangle             rectangle_size   { 150.0f , 150.0f };
            float                 rectangle_margin { 0.0f               };
            float                 rectangle_width  { 1.0f               };
            colours               rectangle_colour { colours::Yellow    };
            float                 rectangle_radius { 0.0f               };
            rounded_rectangle     rrectangle       { .radiusX = rectangle_radius , 
                                                     .radiusY = rectangle_radius };
            
        private: // functions
            
            void reset           ();
            void reset_format    ();
            void reset_layout    ();
            void reset_rectangle ();
            void reset_brush     ();
            
            dimensions get_layout_size() const;
            float  get_layout_width       () const;
            float  get_layout_width_half  () const;
            float  get_layout_height      () const;
            float  get_layout_height_half () const;
            planes get_middle_planes() const;

            void draw_text();
            void draw_rectangle();
            
        public:

             text( void );
            ~text( void );

            text(const text & copy);
            text( const text && move );

            text & operator = ( const text & assignment );
            text & operator = ( const text & assignment_move );
            
            void    set_content( const string in_content      );
            string  get_content() const;
            void    add_content( const string in_string       ); // add to end

            void    set_font_locale ( const string in_locale );
            string  get_font_locale () const;

            void    set_font_face( const string in_font_face );
            string  get_font_face() const;

            void    set_font_size( const float in_font_size );
            float   get_font_size() const;

            void    set_font_colour( const colours in_font_colour ); // bool true set worked false set failed
            colours get_font_colour() const;

            void    set_font_opacity( const float in_font_opacity );
            float   get_font_opacity() const;

            void         set_font_style( const font_style in_font_style );
            font_style   get_font_style() const;

            void         set_font_weight( const font_weight in_font_weight );
            font_weight  get_font_weight() const;

            void         set_font_stretch( const font_stretch in_font_stretch );
            font_stretch get_font_stretch() const;

            void         set_font_options( const font_options in_font_options );
            font_options get_font_options() const;

            void         set_position_top_left( const vertex in_position );
            vertex       get_position_top_left() const;

            void         set_layout_size( const dimensions in_layout_size );
            dimensions   get_layout_size() const;

            void         set_rectangle_size( const rectangle in_rectangle_size );
            rectangle    get_rectangle_size() const;

            void         set_rectangle_colour( const colours in_colour );
            colours      get_rectangle_colour() const;

            void         set_rectangle_edge_width  ( const float in_width );
            float        get_reactangle_edge_width() const;

            void         set_position_top_left( const vertex in_top_left );
            vertex       get_position_top_left() const;

            text_metrics get_text_metrics() const;

            rectangle_edge_middles get_middle_vertices() const;
            rectangle              get_formated_rectangle() const;

            void draw();

    }; // class text

} // namespace hid