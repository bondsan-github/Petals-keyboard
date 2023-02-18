#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\vertex.h"

#include <windows.h>
#include <d2d1.h>

namespace hid
{
    //struct monitor {};
    //struct page {};

    class graphics_d2d
    {
        private:

            ID2D1Factory          * factory      { nullptr };
            HWND window { nullptr };
            ID2D1HwndRenderTarget * page         { nullptr };
            
            PAINTSTRUCT           paint {};
            D2D1::ColorF          colour_clear { 0.2f , 0.2f , 0.2f , 0.5f };
            //D2D1_SIZE_F           page_size    { 0.0f , 0.0f };
            //float                 page_dips    { 0.0f };
            //D2D1_SIZE_F           page_dpi     { 0.0f , 0.0f };
            //result_win          result       { E_FAIL };
            ID2D1SolidColorBrush * brush_line {};
            ID2D1SolidColorBrush * brush_rectangle {};

            float line_width { 1.0f };
            D2D1::ColorF line_colour { D2D1::ColorF::Yellow };

            D2D1_SIZE_F       rectangle_size         { 0.0f , 0.0f };
            static inline float rectangle_line_width   { 1.0f };
            float             rectangle_inner_margin { 5.0f };
            static inline D2D1::ColorF rectangle_line_colour  { D2D1::ColorF::Yellow };

            float             rounded_rectangle_radius { 5.0f };
            D2D1_ROUNDED_RECT rounded_rectangle        { .radiusX = rounded_rectangle_radius ,
                                                         .radiusY = rounded_rectangle_radius };
            void reset();
            void reset_page();
            void reset_brush_line();
            void reset_brush_rectangle();
            void resize();

        public:

            graphics_d2d();
            ~graphics_d2d( void );
            
            //void set_window( HWND in_window ) { }
            void initialise( HWND in_window );
            void draw_begin();
            void draw_end();
            //void draw();
            
            ID2D1Factory & get_factory() { return *factory; }
            ID2D1HwndRenderTarget & get_page();
            D2D_SIZE_F              get_size_dips();
            //D2D_SIZE_U              get_size_pixels();
            D2D_SIZE_U              get_screen_size();
            D2D_SIZE_F              get_dpi();
           
            void set_line_width( float in_width ) { line_width = in_width; }
            void set_line_colour( D2D1::ColorF in_colour ) { line_colour = in_colour; }

            void set_rectangle_line_width( float in_line_width ) { rectangle_line_width = in_line_width; }

            void draw_line_solid( vertex  in_a , vertex  in_b );
            //void draw_line_style()

            //void draw_rectangle( rectangle in_rectangle );

            void draw_rounded_rectangle( D2D_SIZE_F   in_size ,
                                         vertex       in_position_top_left ,
                                         float        in_corner_radius , 
                                         ID2D1Brush * in_brush ,
                                         float        in_line_width = rectangle_line_width );
                                         //D2D1::ColorF in_colour = rectangle_line_colour );
            
    }; // class graphics_d2d

} // namespace hid

 //ID2D1SolidColorBrush  & get_brush_solid( D2D1::ColorF in_colour = D2D1::ColorF::Yellow );
            /*
            ID2D1StrokeStyle      & get_stroke_style( stroke_cap_style  in_cap_start   = stroke_cap_style::flat  ,
                                                 stroke_cap_style  in_cap_dash    = stroke_cap_style::flat  ,
                                                 stroke_cap_style  in_cap_end     = stroke_cap_style::flat  ,
                                                 stroke_line_join  in_line_join   = stroke_line_join::round ,
                                                 float             in_miter_limit = 1.0f                    ,
                                                 stroke_dash_style in_dash_style  = stroke_dash_style::dash ,
                                                 float             in_dash_offset = 1.0f                    );
 /*
         class sheet
         {
            enum class request_type { window_ptr , size };

            using window_ptr = ID2D1HwndRenderTarget *;
            using size    = D2D1_SIZE_F;

            window_ptr _sheet {};
            size    _size  {};

            public:

            sheet( window_ptr const in_sheet = {} , const size in_size = {} )
            : _sheet( in_sheet ) , _size( in_size )
            {}

            size    size()    const { return _size; }
            window_ptr window_ptr() const { return _sheet; }
         };
         */

         //vector< sheet > sheets {};