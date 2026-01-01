#include "Graphics\DWrite\Text.hpp"

#include <string>

Text::Text()
{
    reset();
}

Text::Text( wstring const & in_content )
{
    set( in_content );
}
Text::~Text()
{
    //brush_font.Reset();
    //format.Reset();
    //layout.Reset();
    //collection.Reset();
    //content.clear();
}

void Text::set_locale( wstring const & in_font_locale )
{
    if( in_font_locale.empty() )
        font_locale = L"en-us"; // en-GB
        // else not a vaild locale
    else
        font_locale = in_font_locale;

    reset();
}

void Text::set_face( wstring const & in_font_face )
{
    if( in_font_face.empty() ) // is_valid_font_face()
        font_face = L"Times New Roman";
    else
        font_face = in_font_face;

    reset();
}

void Text::set_size( float const in_font_size )
{
    if( in_font_size <= 0.0f )//|| in_font_size > )
        font_size = 0.1f;
    else
        font_size = in_font_size;

    reset();
}

void Text::set_style( DWRITE_FONT_STYLE const in_font_style )
{
    /*
    if( in_font_style == DWRITE_FONT_STYLE_NORMAL  || 
        in_font_style -= DWRITE_FONT_STYLE_OBLIQUE ||
        in_font_style == DWRITE_FONT_STYLE_ITALIC ) font_style = in_font_style;
    else*/
        font_style = in_font_style;

        reset();
}
    
//void text::options( const font_options in_font_options ) { font_options = in_font_options; }
//font_options text::options() const { return _font_options; }

void Text::set_opacity( float const in_font_opacity )
{
    if( in_font_opacity < 0.0f ) // || > 1.0f clamp(0.0,1.0);
        font_opacity = 0.0f;
    else
        font_opacity = in_font_opacity;

    reset();
}

void Text::set_weight( DWRITE_FONT_WEIGHT const in_font_weight )
{
    // between 1 and 999
    font_weight = in_font_weight;

    reset();
}

void Text::set_stretch( DWRITE_FONT_STRETCH const in_font_stretch )
{
    font_stretch = in_font_stretch;

    reset();
}

void Text::set_layout_size( D2D1_SIZE_F const & in_layout_size )
{
    layout_size_ = in_layout_size;

    reset();
}

D2D1_SIZE_F Text::get_layout_size() const
{ 
    DWRITE_TEXT_METRICS metrics {};

    layout->GetMetrics( & metrics );
        
    return { metrics.width , metrics.height };
}

/* void text::corner_radius( float in_radius )
{
    rectangle_radius = in_radius;

    corner_radius.radiusX = rectangle_radius;
    corner_radius.radiusY = rectangle_radius;
} */
    
void Text::reset()
{
    reset_format();
    reset_layout();
    reset_brush();
    reset_border();
}

void Text::reset_format()
{
    factory_write->CreateTextFormat( font_face.c_str(),
                                        nullptr , // in_font_collection // (NULL sets it to use the system font collection).
                                        font_weight ,
                                        font_style ,
                                        font_stretch ,
                                        font_size ,
                                        font_locale.c_str() ,
                                        & format );// address of pointer to COM object  
}

void Text::reset_layout()
{
    factory_write->CreateTextLayout( content_.c_str() ,
                                        static_cast< uint >( content_.size() ) ,
                                        format.Get() ,
                                        layout_size_.width ,
                                        layout_size_.height ,
                                        & layout );
    //reset_rectangle();
}

void Text::reset_brush()
{
    context_2d->CreateSolidColorBrush( font_colour , & brush_font );
}

float Text::width() const
{ 
    DWRITE_TEXT_METRICS layout_metrics{};

    layout->GetMetrics( & layout_metrics );

    return layout_metrics.width;
}
    
float Text::get_width_half() const
{
    return width() / 2.0f;
}

float Text::height() const
{ 
    DWRITE_TEXT_METRICS layout_metrics{};

    layout->GetMetrics( &layout_metrics );
        
    return layout_metrics.height;
}

float Text::get_height_half() const
{
    return height() / 2.0f;
}
    
/*
void text::position( vertex in_position )
{
    //page_dpi        dpi         = locate::graphics()->get_dpi();
    //dimensions      size_dips   = locate::graphics()->get_size_dips();
    //page_dimensions size_pixels = locate::graphics()->get_size_pixels();

    position_ = in_position;
    layout->GetMetrics( &layout_metrics );
    position_ = { layout_metrics.left , layout_metrics.top };
}
*/

void Text::set_position( const Point & in_position_top_left )
{
    position_ = in_position_top_left;
}

Point Text::get_position() const
{
    return position_;
}

void Text::set_colour( const D2D1::ColorF &in_font_colour )
{
    font_colour = in_font_colour;

    reset_brush();
    //reset();
}

void Text::set( wstring const & in_content )
{
    content_ = in_content;
        
    reset_layout();
}

void Text::add( wstring const & in_string )
{
    content_ += in_string;

    reset();
}

void Text::draw()
{
    context_2d->DrawTextLayout( position_ ,
                                layout.Get() ,
                                brush_font.Get() );
                                //font_options );

    if( border_show ) border.draw();
}

void Text::show_border( bool in_show_border )
{
    border_show = in_show_border;
}

void Text::reset_border()
{
    int x2 = get_layout_size().width;
    int y2 = get_layout_size().height;

    border.position( position_ , { x2 , y2 } );

    border + border_inner_margin;

    border.line_width( border_line_width );
    border.line_colour( border_line_colour );
}

float Text::top() const
{
    return position_.y();
}

float Text::bottom() const
{
    return position_.y() + height();
}

float Text::left() const
{
    return position_.x();
}

float Text::right() const
{
    return position_.x() + width();
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