#include "..\headers\text_d2d.h"

#include "..\headers\locate.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    text::text( string       in_content           ,
                vertex       in_position_top_left ,
                float        in_font_size         ,
                dimensions   in_layout_size       ,
                float        in_rectangle_margin  , 
                colours      in_font_colour       ,
                text_weight  in_font_weight       ,
                text_style   in_font_style        ,
                text_stretch in_font_stretch      ,
                string       in_font_face         )
              : content( in_content )                     ,
                position_top_left( in_position_top_left ) ,
                font_size( in_font_size )                 ,  
                layout_size( in_layout_size )             ,
                rectangle_margin( in_rectangle_margin )   ,
                font_colour( in_font_colour )             ,
                font_weight( in_font_weight )             ,
                font_style( in_font_style )               ,
                font_stretch( in_font_stretch )           ,
                font_face( in_font_face )
    {
        reset();
    }

    void text::reset()
    {
        reset_format();
        reset_layout();
        reset_brush();
    }

    void text::reset_format()
    {
        format = locate::write()->format( content      ,
                                          collection   ,
                                          font_weight  ,
                                          font_style   ,
                                          font_stretch ,
                                          font_size    ,
                                          font_locale  );
    }

    void text::reset_layout()
    {
        layout = locate::write()->layout( content , format , layout_size );

        reset_rectangle();
    }

    void text::reset_rectangle()
    {
        float  radius   = rectangle_radius;
        vertex position = this->position();
        float  margin   = rectangle_margin;

        layout->GetMetrics( & layout_metrics );

        layout_rectangle.left   = layout_metrics.left;
        layout_rectangle.top    = layout_metrics.top;

        layout_rectangle.right  = layout_metrics.width;
        layout_rectangle.bottom = layout_metrics.height;

        rrectangle.radiusX = rrectangle.radiusY = radius;

        rrectangle.rect.left   = position.x - margin;
        rrectangle.rect.top    = position.y - margin;

        rrectangle.rect.right  = position.x + layout_rectangle.right + margin;
        rrectangle.rect.bottom = position.y + layout_rectangle.bottom + margin;
    }

    rectangle text::formated_rectangle()
    {
        vertex position = this->position();

        layout_rectangle.top    = position.y + layout_metrics.top;
        layout_rectangle.right  = position.x + layout_metrics.width;
        layout_rectangle.bottom = position.y + layout_metrics.height;
        layout_rectangle.left   = position.x + layout_metrics.left;

        return layout_rectangle;
    }

    void text::reset_brush()
    {
        brush = locate::graphics()->brush_solid( font_colour );
    }

    float const text::layout_width()
    { 
        layout->GetMetrics( & layout_metrics );

        return layout_metrics.width;
    }
    
    float const text::layout_width_half()
    { 
        return layout_width() / 2.0f; 
    }

    float const text::layout_height()
    { 
        layout->GetMetrics( & layout_metrics );

        return layout_metrics.height;
    }

    float const text::layout_height_half()
    {
        return layout_height() / 2.0f;
    }
    
    /*
    void text::position( vertex in_position )
    {
        //page_dpi        dpi         = locate::graphics()->get_dpi();
        //dimensions      size_dips   = locate::graphics()->get_size_dips();
        //page_dimensions size_pixels = locate::graphics()->get_size_pixels();

        position_top_left = in_position;

        layout->GetMetrics( &layout_metrics );

        position_top_left = { layout_metrics.left , layout_metrics.top };

        reset_rectangle();
    }
    */

    vertex text::position()
    {
        return position_top_left;
    }

    void text::set_font_colour( colours in_font_colour )
    {
        font_colour = in_font_colour;

        reset_brush();
    }

    void text::set_rectangle_width( float const in_width )
    {
        rectangle_width = in_width;
    }
    
    void text::set_rectangle_colour( colours const in_colour )
    {
        rectangle_colour = in_colour;
    }

    void text::set_content( string const in_content )
    {
        content = in_content;

        reset_format();
        reset_layout();
        reset_rectangle();
    }

    void text::add_content( string const in_string )
    {
        content += in_string;

        reset();
    }

    void text::draw()
    {
        draw_text();

        if( rectangle_show ) draw_rectangle();
    }

    void text::draw_text()
    {
        locate::graphics()->get_page()->DrawTextLayout( position() ,
                                                        layout.Get() ,
                                                        brush.Get() ,
                                                        static_cast< D2D1_DRAW_TEXT_OPTIONS >( font_options ) );
    }

    void text::draw_rectangle()
    {
        locate::graphics()->draw_rounded_rectangle( rrectangle , rectangle_radius , rectangle_width , rectangle_colour );
    }

    planes const text::middle_planes()
    {
        planes middle {};

        middle.horizontal = position().x + layout_width_half();
        middle.vertical   = position().y + layout_height_half();

        return middle;
    }

    rectangle_edge_middles text::middle_vertices()
    {
        rectangle_edge_middles middle     {};

        vertex                 position   = this->position();
        float                  horizontal = middle_planes().horizontal;
        float                  vertical   = middle_planes().vertical;
        float                  margin     = rectangle_margin;
        float                  width      = layout_width();
        float                  height     = layout_height();

        middle.top.x    = vertical;
        middle.top.y    = position.y - margin;

        middle.right.x  = position.x + width + margin;
        middle.right.y  = horizontal;

        middle.bottom.x = vertical;
        middle.bottom.y = position.y + height + margin;

        middle.left.x   = position.x - margin;
        middle.left.y   = horizontal;

        return middle;
    }
}