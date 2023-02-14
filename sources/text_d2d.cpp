#include "..\headers\text_d2d.h"
#include "..\headers\locate.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

#include <string>

namespace hid
{
    text_d2d::text_d2d()
    {
        reset();
    }

    text_d2d::text_d2d( std::wstring & in_content )
    {
        //if( not in_content.empty )
        set_content( in_content );
    }
    text_d2d::~text_d2d()
    {
        //brush_font.Reset();
        //format.Reset();
        //layout.Reset();
        //collection.Reset();
        //content.clear();
    }

    void text_d2d::set_font_locale( const std::wstring &in_font_locale )
    {
        if( in_font_locale.empty() )
            font_locale = L"en-us"; // en-GB
            // else not a vaild locale
        else
            font_locale = in_font_locale;

        reset();
    }

    void text_d2d::set_font_face( const std::wstring &in_font_face )
    {
        if( in_font_face.empty() ) // is_not_valid_font_face()
            font_face = L"Times New Roman";
        else
            font_face = in_font_face;

        reset();
    }

    void text_d2d::set_font_size( const float &in_font_size )
    {
        if( in_font_size <= 0.0f )//|| in_font_size > )
            font_size = 0.1f;
        else
            font_size = in_font_size;

        reset();
    }

    void text_d2d::set_font_style( const DWRITE_FONT_STYLE &in_font_style )
    {
        /*
        if( in_font_style == DWRITE_FONT_STYLE_NORMAL  || 
            in_font_style -= DWRITE_FONT_STYLE_OBLIQUE ||
            in_font_style == DWRITE_FONT_STYLE_ITALIC ) font_style = in_font_style;
        else*/
            font_style = in_font_style;

            reset();
    }
    
    //void text::set_font_options( const font_options in_font_options ) { font_options = in_font_options; }
    //font_options text::get_font_options() const { return _font_options; }

    void text_d2d::set_font_opacity( const float &in_font_opacity )
    {
        if( in_font_opacity < 0.0f ) // || > 1.0f clamp(0.0,1.0);
            font_opacity = 0.0f;
        else
            font_opacity = in_font_opacity;

        reset();
    }

    void text_d2d::set_font_weight( const DWRITE_FONT_WEIGHT &in_font_weight )
    {
        // between 1 and 999
        font_weight = in_font_weight;
        reset();
    }

    void text_d2d::set_font_stretch( const DWRITE_FONT_STRETCH &in_font_stretch )
    {
        font_stretch = in_font_stretch;
        reset();
    }

    void text_d2d::set_layout_size( const D2D1_SIZE_F &in_layout_size )
    {
        // check sizes are within all screen bounds
        layout_size = in_layout_size;
        reset();
    }

    D2D1_SIZE_F text_d2d::get_formated_size() const
    { 
        DWRITE_TEXT_METRICS metrics;
        layout->GetMetrics( &metrics );
        
        return { metrics.width , metrics.height };
    }

    /*

    void text::set_bounding_rectangle_corner_radius( float in_radius )
    {
        rectangle_radius = in_radius;

        bounding_rectangle_corner_radius.radiusX = rectangle_radius;
        bounding_rectangle_corner_radius.radiusY = rectangle_radius;
    }
    */
    
    void text_d2d::reset()
    {
        reset_format();
        reset_layout();
        reset_brush();
    }

    void text_d2d::reset_format()
    {
        locate::get_write().get_write_factory().CreateTextFormat( font_face.c_str(),
                                                                  nullptr , // in_font_collection // (NULL sets it to use the system font collection).
                                                                  font_weight ,
                                                                  font_style ,
                                                                  font_stretch ,
                                                                  font_size ,
                                                                  font_locale.c_str() ,
                                                                  &format );// address of pointer to COM object  
    }

    void text_d2d::reset_layout()
    {
        locate::get_write().get_write_factory().CreateTextLayout( content.c_str() ,
                                                                  static_cast< uint >( content.size() ),
                                                                  format.Get() ,
                                                                  layout_size.width ,
                                                                  layout_size.height ,
                                                                  &layout );
        //reset_rectangle();
    }

    void text_d2d::reset_brush()
    {
        locate::get_graphics().get_page().CreateSolidColorBrush( font_colour , &brush_font );
    }

    float text_d2d::get_formated_width() const
    { 
        DWRITE_TEXT_METRICS layout_metrics{};

        layout->GetMetrics( & layout_metrics );

        return layout_metrics.width;
    }
    
    float text_d2d::get_formated_width_half() const
    {
        return get_formated_width() / 2.0f;
    }

    float text_d2d::get_formated_height() const
    { 
        DWRITE_TEXT_METRICS layout_metrics{};

        layout->GetMetrics( &layout_metrics );
        
        return layout_metrics.height;
    }

    float text_d2d::get_layout_height_half() const
    {
        return get_formated_height() / 2.0f;
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
    }
    */

    void text_d2d::set_position_top_left( const vertex &in_position_top_left )
    {
        position_top_left = in_position_top_left;
    }

    vertex text_d2d::get_position_top_left() const
    {
        return { position_top_left.x , position_top_left.y };
    }

    void text_d2d::set_font_colour( const D2D1::ColorF &in_font_colour )
    {
        font_colour = in_font_colour;

        reset_brush();
        //reset();
    }

    void text_d2d::set_content( std::wstring &in_content )
    {
        content = in_content;
        //reset();
        reset_layout();
    }

    void text_d2d::add_content( std::wstring &in_string )
    {
        content += in_string;
        reset();
    }

    void text_d2d::draw() const
    {
        draw_text();
        if( border_show ) draw_border();
    }

    void text_d2d::draw_text() const
    {
        //if(locate::get_graphics() != nullptr /)
        locate::get_graphics().get_page().DrawTextLayout( position_top_left ,
                                                          layout.Get() ,
                                                          brush_font.Get() );
                                                          //font_options );
    }

    void text_d2d::set_show_border( const bool in_show_border )
    {
        border_show = in_show_border;
    }

    void text_d2d::draw_border() const
    {
        vertex position = position_top_left;

        position.x -= border_inner_margin;
        position.y -= border_inner_margin;
        
        D2D_SIZE_F size = get_formated_size();
        size.width  += border_inner_margin * 2.0f;
        size.height += border_inner_margin * 2.0f;

        locate::get_graphics().draw_rounded_rectangle( size ,
                                                       position ,
                                                       border_corner_radius ,
                                                       brush_font.Get() , // brush_bounding_rectangle
                                                       border_line_width );
    }

    float text_d2d::get_top() const
    {
        return position_top_left.y;// - bounding_rectangle_inner_margin;
    }

    float text_d2d::get_bottom() const
    {
        return position_top_left.y + get_formated_height();// + bounding_rectangle_inner_margin;
    }

    float text_d2d::get_left() const
    {
        return position_top_left.x;// - bounding_rectangle_inner_margin;
    }

    float text_d2d::get_right() const
    {
        return position_top_left.x + get_formated_width();// + bounding_rectangle_inner_margin;
    }

    /*
    planes text::get_middle_planes()
    {
        planes middle {};

        middle.horizontal = get_position_top_left().x + get_layout_width_half();
        middle.vertical   = get_position_top_left().y + get_layout_height_half();

        return middle;
    }
    */
    //text_metrics text::get_text_metrics()    {}

    /*
    rectangle_edge_middles text::get_middle_vertices()
    {
        rectangle_edge_middles middle     {};

        vertex                 position   = get_position_top_left();
        float                  horizontal = get_middle_planes().horizontal;
        float                  vertical   = get_middle_planes().vertical;
        float                  margin     = rectangle_inner_margin;
        float                  width      = get_layout_width();
        float                  height     = get_layout_height();

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
    */

    /*
    void text::get_layout_rectangle()
    {
    
        float  radius   = rectangle_radius;
        vertex position = get_position_top_left();
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
        
    }*/
    
    /*rectangle text::get_layout_rectangle()
    {

        vertex position = get_position_top_left();

        layout_rectangle.top    = position.y + layout_metrics.top;
        layout_rectangle.right  = position.x + layout_metrics.width;
        layout_rectangle.bottom = position.y + layout_metrics.height;
        layout_rectangle.left   = position.x + layout_metrics.left;

        return layout_size;
    }*/

} // namespace hid