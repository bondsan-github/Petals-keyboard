#pragma once

//https://learn.microsoft.com/en-us/windows/win32/direct2d/improving-direct2d-performance#use-a-multithreaded-device-context
//https://learn.microsoft.com/en-us/windows/win32/directwrite/rendering-by-using-direct2d

#include "..\headers\custom_types.h"
#include "..\headers\vertex.h"

#include <d2d1.h>
#include <dwrite.h>
#include <string>

#include <wrl/client.h>

namespace hid
{
    class text_d2d
    {
        private:
       
            Microsoft::WRL::ComPtr <IDWriteTextFormat>    format{ nullptr };
            Microsoft::WRL::ComPtr <ID2D1SolidColorBrush> brush_font { nullptr };
            Microsoft::WRL::ComPtr <IDWriteTextLayout>    layout     { nullptr };
            //Microsoft::WRL::ComPtr <IDWriteFontCollection> collection { nullptr };

            std::wstring          content {L" "};
            
          //vertex                position_center   { 10.0f , 10.0f        }; // dips
            vertex                position_top_left { 0.0f , 0.0f          }; // in dips
            
            std::wstring          font_locale       { L"en-us" }; // en-GB
            std::wstring          font_face         { L"Times New Roman"   }; // font family
            float                 font_size         { 15.0f                }; // * dpi? // MS "size * 96.0f/72.0f"
            D2D1::ColorF          font_colour       { D2D1::ColorF::Black       };
            float                 font_opacity      { 1.0f                 };
            DWRITE_FONT_STYLE     font_style        { DWRITE_FONT_STYLE_NORMAL };
            DWRITE_FONT_WEIGHT    font_weight       { DWRITE_FONT_WEIGHT_NORMAL };
            DWRITE_FONT_STRETCH   font_stretch      { DWRITE_FONT_STRETCH_NORMAL };
            
            // collection
            // family
            // spacing
            // trimming
            // wrapping
            // alignment_vertical
            // alignment_horizontal
            // direction_reading
            // direction_flow

            D2D1_SIZE_F         layout_size { 150.0 , 150.0 };

            bool         border_show          { true };
            float        border_line_width    { 2.0f };
            D2D1::ColorF border_line_colour   { D2D1::ColorF::Yellow };
            float        border_corner_radius { 1.0f };
            float        border_inner_margin  { 5.0f };
            
        private:
            
            void reset();
            void reset_format();
            void reset_layout();
            void reset_brush();
            
            D2D1_SIZE_F get_formated_size() const;
            float       get_formated_width_half() const ;
            float       get_layout_height_half() const ;
            //planes      get_middle_planes();

            void draw_text() const;
            void draw_border() const;
            
        public:

             text_d2d();
             text_d2d( std::wstring & in_content );
             ~text_d2d();

            void set_content( std::wstring &in_content );
            void add_content( std::wstring &in_string ); // add to end // concatenate

            void set_font_locale( const std::wstring &in_locale );
            void set_font_face( const std::wstring &in_font_face );
            void set_font_size( const float &in_font_size );
            void set_font_colour( const D2D1::ColorF &in_font_colour );
            void set_font_opacity( const float &in_font_opacity );
            void set_font_style( const DWRITE_FONT_STYLE &in_font_style );
            void set_font_weight( const DWRITE_FONT_WEIGHT &in_font_weight );
            void set_font_stretch( const DWRITE_FONT_STRETCH &in_font_stretch );

            void set_position_top_left( const vertex &in_position );
            void set_layout_size( const D2D1_SIZE_F &in_layout_size );

            void set_show_border( const bool in_show_border );
            //void set_rectangle_radius( float in_radius );
            //void set_rectangle_line_colour( D2D1::ColorF in_colour );
            //void set_rectangle_line_width( float in_width );
            //void set_font_options( font_options in_font_options );

            std::wstring get_content() const { return content; }
            std::wstring get_font_locale() const { return font_locale; }
            //font_options get_font_options();
            vertex get_position_top_left() const;
            //dimensions get_layout_size();
            float get_top() const;
            float get_right() const;
            float get_left() const;
            float get_bottom() const;
            float get_formated_width() const ;
            float get_formated_height() const ;

            //rectangle_edge_middles get_middle_vertices();
            //rectangle            get_formated_rectangle();

            void draw() const;

    }; // class text

} // namespace hid

