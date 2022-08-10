#pragma once

#include "..\headers\direct_2d.h"
//#include "..\headers\service.h"

namespace hid
{
    struct monitor
    {};

    struct page
    {};

    //class gui_windows_ms;

    class graphics_d2d// : public service
    {
        private:

            HWND                  window       {};
            ComPtr< factory_d2d > factory      {};
            ComPtr< page_window > page         {};
            
            paint_structure           paint        {};
            colours                   colour_clear { 0.2f , 0.2f , 0.2f , 0.5f };
            page_dimensions           size         { 1024 , 768 };
            page_dips                 dips         {};
            page_dpi                  dpi          { .width = 96.0f , .height = 96.0f };
            //result_win              result            { E_FAIL };

        public:

            void initialise ( HWND in_window );
            void reset      ();
            void draw       ();
            void resize     ();

            page_window_pointer get_page        ();
            page_dips           get_size_dips   ();
            page_dimensions     get_size_pixels ();
            page_dpi            get_dpi         ();
            brush_solid_pointer brush_solid( colours in_colour = colours::Yellow );
            stroke_style_pointer stroke_style( stroke_cap_style  in_cap_start   = stroke_cap_style::flat  ,
                                               stroke_cap_style  in_cap_dash    = stroke_cap_style::flat  ,
                                               stroke_cap_style  in_cap_end     = stroke_cap_style::flat  ,
                                               stroke_line_join  in_line_join   = stroke_line_join::round ,
                                               float             in_miter_limit = 1.0f                    ,
                                               stroke_dash_style in_dash_style  = stroke_dash_style::dash ,
                                               float             in_dash_offset = 1.0f                    );
            
            void draw_line( vertex  in_a        = { 0.0f , 0.0f } , // dips 0..1
                            vertex  in_b        = { 1.0f , 1.0f } ,
                            float   in_width     = 1.0f            ,
                            colours in_colours = colours::Yellow );

            void draw_rectangle( rectangle in_rectangle );

            void draw_rounded_rectangle( dimensions in_size            = { 100 , 100 } ,
                                         vertex     in_position_center ={ 0.5f , 0.5f } ,
                                         float      in_radius          = 5.0f ,
                                         float      in_width           = 5.0f ,
                                         colours    in_colour          = colours::Yellow );

            void draw_rounded_rectangle( rounded_rectangle in_rectangle = { 10.0f, 10.0f , 50.0f , 50.0f } ,
                                         float             radius = 0.0f ,
                                         float             boundry_width = 1.0f ,
                                         colours           colour = colours::Yellow );
    };
}

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