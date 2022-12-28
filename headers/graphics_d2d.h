#pragma once

#include "..\headers\custom_types.h"
//#include "..\headers\service.h"

#include <windows.h>
#include <d2d1.h>

namespace hid
{
    //struct monitor {};
    //struct page {};

    class graphics_d2d// : public service
    {
        private:

            HWND                    window       { nullptr };
            ID2D1Factory          * factory      { nullptr };
            ID2D1HwndRenderTarget * page         { nullptr };
            
            PAINTSTRUCT           paint;
            D2D1::ColorF          colour_clear { 0.2f , 0.2f , 0.2f , 0.5f };
            //D2D1_SIZE_F           page_size    { 0.0f , 0.0f };
            //float                 page_dips    { 0.0f };
            //D2D1_SIZE_F           page_dpi     { 0.0f , 0.0f };
            //result_win          result       { E_FAIL };

        public:

            graphics_d2d( void );
            ~graphics_d2d( void );

            void reset      ();
            void draw       ();
            void resize     ();

            ID2D1HwndRenderTarget & get_page();
            D2D_SIZE_F              get_size_dips();
            D2D_SIZE_U              get_size_pixels();
            D2D_SIZE_F              get_dpi();
            //ID2D1SolidColorBrush  & get_brush_solid( D2D1::ColorF in_colour = D2D1::ColorF::Yellow );
            /*
            ID2D1StrokeStyle      & get_stroke_style( stroke_cap_style  in_cap_start   = stroke_cap_style::flat  ,
                                                 stroke_cap_style  in_cap_dash    = stroke_cap_style::flat  ,
                                                 stroke_cap_style  in_cap_end     = stroke_cap_style::flat  ,
                                                 stroke_line_join  in_line_join   = stroke_line_join::round ,
                                                 float             in_miter_limit = 1.0f                    ,
                                                 stroke_dash_style in_dash_style  = stroke_dash_style::dash ,
                                                 float             in_dash_offset = 1.0f                    );
            */
            /*
            void draw_line( vertex  in_a       = { 0.0f , 0.0f } , // dips 0..1
                            vertex  in_b       = { 1.0f , 1.0f } ,
                            float   in_width   = 1.0f            ,
                            colours in_colours = colours::Yellow );

            void draw_rectangle( rectangle in_rectangle );

            void draw_rounded_rectangle( dimensions in_size            = { 100 , 100 } ,
                                         vertex     in_position_center = { 0.5f , 0.5f } ,
                                         float      in_radius          = 5.0f ,
                                         float      in_width           = 5.0f ,
                                         colours    in_colour          = colours::Yellow );

            void draw_rounded_rectangle( D2D1_ROUNDED_RECT in_rectangle = {{ 10.0f, 10.0f , 50.0f , 50.0f }} ,
                                         float             radius = 0.0f ,
                                         float             boundry_width = 1.0f ,
                                         colours           colour = colours::Yellow );
            */
    }; // class graphics_d2d

} // namespace hid

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