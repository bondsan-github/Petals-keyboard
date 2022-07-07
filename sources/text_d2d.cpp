#include "..\headers\text_d2d.h"

#include "..\headers\locate.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    text::text( string  in_content ,
                vertex  in_position_center ,
                float   in_size ,
                colours in_colour )
                : content( in_content ) , position_center( in_position_center ) , size( in_size ) , colour( in_colour )
    {
        reset();
    }

    float text::width()       { return boundry.width;         }
    float text::width_half()  { return boundry.width  / 2.0f; }
    float text::height()      { return boundry.height;        }
    float text::height_half() { return boundry.height / 2.0f; }
    
    void text::position( vertex in_center )
    {
        page_dpi        dpi         = locate::graphics().get_dpi();
        dimensions      size_dips   = locate::graphics().get_size_dips();
        page_dimensions size_pixels = locate::graphics().get_size_pixels();

        position_center.x = in_center.x;// * size_dips.width;
        position_center.y = in_center.y;// * size_dips.height;

        reset_boundry();
    }

    void text::set_colour( colours in_colour )
    {
        colour = in_colour;

        reset_brush();
    }

    void text::set_boundry( dimensions in_dimensions )
    {
        boundry = in_dimensions;

        reset_boundry();
    }

    void text::set_boundry_width( float in_width )
    {
        boundry_width = in_width;
    }
    
    void text::set_boundry_colour( colours in_colour )
    {
        boundry_colour = in_colour;
    }

    vertex text::top_left()
    {
        vertex top_left {}; // in pixels

        top_left.x = position_center.x - width_half();
        top_left.y = position_center.y - height_half();

        return top_left;
    }

    void text::reset()
    {
        reset_format();
        reset_layout();
        reset_brush();
        reset_boundry();
    }

    void text::reset_brush()
    {
        brush = locate::graphics().brush_solid( colour );
    }

    void text::reset_format()
    {
        format = locate::write().format( content ,
                                         collection ,
                                         weight , 
                                         style ,
                                         stretch , 
                                         size ,
                                         locale );
    }

    void text::reset_layout()
    {
        layout = locate::write().layout( content , format , boundry );
    }

    void text::set_content( wstring in_content )
    {
        content = in_content;

        reset_format();
        reset_layout();
        reset_boundry();
    }

    void text::add( const wstring in_string )
    {
        content += in_string;

        reset();
    }

    void text::draw()
    {
        draw_text();

        if( show_boundry ) draw_boundry();
    }

    void text::draw_text()
    {
        locate::graphics().get_page()->DrawTextLayout( top_left() ,
                                                       layout.Get() ,
                                                       brush.Get() ,
                                                       static_cast< D2D1_DRAW_TEXT_OPTIONS >( options ) );
    /*
        locate::write().draw_text( content ,
                                   position_center , 
                                   size ,
                                   weight ,
                                   style ,
                                   stretch ,
                                   colour ,
                                   boundry ,
                                   font );
    */
    }

    rectangle_edge_middles text::middle_vertices()
    {
        rectangle_edge_middles vertices {};
        return vertices;
    }
    
    void text::reset_boundry()
    {
        const float width       = boundry.width;
        const float height      = boundry.height;
        const float width_half  = width  / 2.0f;
        const float height_half = height / 2.0f;
        const float margin      = 5.0f;

        rrectangle.radiusX = rrectangle.radiusY = radius;
        
        rrectangle.rect.left   = position_center.x - width_half  - margin;
        rrectangle.rect.top    = position_center.y - height_half - margin;
        rrectangle.rect.right  = position_center.x + width_half  + margin;
        rrectangle.rect.bottom = position_center.y + height_half + margin;

        reset_layout();
    }

    void text::draw_boundry()
    {
        //const float width  = layout->GetMaxWidth();
        //const float height = layout->GetMaxHeight();

        locate::graphics().draw_rectangle( boundry , position_center , radius , boundry_width , boundry_colour );
    }

    /*
    struct planes
    {
        float horizontal {};
        float vertical   {};
    };

    planes middle_planes( float in_width , float in_height )
    {
        planes middle {};

        middle.horizontal = center.x + ( in_width / 2.0f );
        middle.vertical   = center.y;

        return middle;
    }

    rect_points_mid middle_points()
    {
        rect_points_mid middles {};



        float mid_horizontal = ( temp.right - temp.left ) / 2.0f;
        float mid_vertical   = ( temp.bottom - temp.top ) / 2.0f;

        mid.top.x    = temp.left + mid_horizontal;
        mid.top.y    = temp.top;

        mid.right.x  = temp.right;
        mid.right.y  = temp.top + mid_vertical;

        mid.bottom.x = mid.top.x;
        mid.bottom.y = temp.bottom;

        mid.left.x   = temp.left;
        mid.left.y   = mid.right.y;

        return mid;

        rectangle     bounding_box{};
        //middle_planes planes{ dimensions.width , dimensions.height };

        reset_bounds()
        {


        }
        //int []
    }
    */

} // namespace hid