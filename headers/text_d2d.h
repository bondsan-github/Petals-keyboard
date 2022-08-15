#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
    class text
    {
        private: // variables

            text_format_pointer     format     {};
            brush_solid_pointer     brush      {}; 
            text_layout_pointer     layout     {};
            font_collection_pointer collection {};

            string                content           { L"empty"             };
            string                font_locale       { L"en-us"             };
          //vertex                position_center   { 10.0f , 10.0f        }; // dips
            vertex                position_top_left {                      }; // in dips
            string                font_face         { L"Times New Roman"   }; // font family
            float                 font_size         { 15.0f                }; // * dpi? // MS "size * 96.0f/72.0f"
            colours               font_colour       { colours::Yellow      };
            float                 font_opacity      { 1.0f                 };
            text_style            font_style        { text_style::normal   };
            text_weight           font_weight       { text_weight::regular };
            text_stretch          font_stretch      { text_stretch::normal };
            text_options          font_options      { text_options::none   };
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
            rectangle             layout_rectangle {                    };
            text_metrics          layout_metrics   {                    };

            bool                  rectangle_show   { true               };
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
            
            
            float  const layout_width       ();
            float  const layout_width_half  ();
            float  const layout_height      ();
            float  const layout_height_half ();
          //void   const position           ( vertex in_top_left );

            void draw_text       ();
            void draw_rectangle  ();
            planes const middle_planes ();
            
        public:

            text( string       const in_content           = { L"empty"             } ,
                  vertex       const in_position_top_left = { 10.0f , 10.0f        } ,
                  float        const in_font_size         = { 10.0f                } ,
                  dimensions   const in_layout_size       = { 200.0f , 150.0f      } ,
                  float        const in_rectangle_margin  = { 0.0f                 } ,
                  colours      const in_font_colour       = { colours::Yellow      } ,
                  text_weight  const in_font_weight       = { text_weight::regular } ,
                  text_style   const in_font_style        = { text_style::normal   } ,
                  text_stretch const in_font_stretch      = { text_stretch::normal } ,
                  string       const in_font              = { L"Times New Roman"   } );
            
            void  set_content          ( string const in_content );
            void  add_content          ( string const in_string  );
            void  set_position         ( vertex in_position      );
            void  set_font_colour      ( colours const in_colour );
          //void  set_layout_size      ( dimensions in_layout_size );
            void  set_rectangle_colour ( colours const in_colour );
            void  set_rectangle_width  ( float const in_width    );
            void  draw                 ();

            vertex get_position();

            rectangle_edge_middles middle_vertices();
            rectangle              formated_rectangle();
    };
}