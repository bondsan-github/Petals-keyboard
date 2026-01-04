#include "Graphics\DWrite\Text.h"

#include <string>

Text::Text()
{
    reset();
}

Text::Text( wstring content )
{
    set( content );
}
Text::~Text()
{
    //brush_font.Reset();
    //format.Reset();
    //layout.Reset();
    //collection.Reset();
    //content.clear();
}

void Text::locale( wstring locale )
{
    if( locale_.empty() )
        locale_ = L"en-us"; // en-GB
        // else not a vaild locale
    else
        locale_ = locale;

    reset();
}

void Text::face( wstring face )
{
    if( face_.empty() ) // is_valid_font_face()
        face_ = L"Times New Roman";
    else
        face_ = face;

    reset();
}

void Text::size( float size )
{
    if( size_ <= 0.0f )//|| size > )
        size_ = 0.1f;
    else
        size_ = size;

    reset();
}

void Text::style( DWRITE_FONT_STYLE style )
{
    /*
    if( style == DWRITE_FONT_STYLE_NORMAL  || 
        style -= DWRITE_FONT_STYLE_OBLIQUE ||
        style == DWRITE_FONT_STYLE_ITALIC ) font_style = in_font_style;
    else*/
        style_ = style;

        reset();
}
    
//void text::options( const font_options in_font_options ) { font_options = in_font_options; }
//font_options text::options() const { return _font_options; }

void Text::opacity( float opacity )
{
    if( opacity_ < 0.0f ) // || > 1.0f clamp(0.0,1.0);
        opacity_ = 0.0f;
    else
        opacity_ = opacity;

    reset();
}

void Text::weight( DWRITE_FONT_WEIGHT weight )
{
    // between 1 and 999
    weight_ = weight;

    reset();
}

void Text::stretch( DWRITE_FONT_STRETCH stretch )
{
    stretch_ = stretch;

    reset();
}

void Text::layout_size( D2D1_SIZE_F layout_size )
{
    layout_size_ = layout_size;

    reset();
}

D2D1_SIZE_F Text::layout_size()
{ 
    DWRITE_TEXT_METRICS metrics {};

    layout_->GetMetrics( & metrics );
        
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
    factory_write->CreateTextFormat( face_.c_str(),
                                     nullptr, // in_font_collection // (NULL sets it to use the system font collection).
                                     weight_,
                                     style_,
                                     stretch_,
                                     size_,
                                     locale_.c_str() ,
                                     & format_ );// address of pointer to COM object  
}

void Text::reset_layout()
{
    factory_write->CreateTextLayout( content_.c_str() ,
                                     static_cast< uint >( content_.size() ) ,
                                     format_.Get() ,
                                     layout_size_.width ,
                                     layout_size_.height ,
                                     & layout );
    //reset_rectangle();
}

void Text::reset_brush()
{
    context_2d->CreateSolidColorBrush( colour_ , & brush_ );
}

float Text::width()
{ 
    DWRITE_TEXT_METRICS layout_metrics{};

    layout_->GetMetrics( & layout_metrics );

    return layout_metrics.width;
}
    
float Text::width_half()
{
    return width() / 2.0f;
}

float Text::height()
{ 
    DWRITE_TEXT_METRICS layout_metrics{};

    layout_->GetMetrics( &layout_metrics );
        
    return layout_metrics.height;
}

float Text::height_half()
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

void Text::position( Point position_top_left )
{
    position_ = position_top_left;
}

Point Text::position()
{
    return position_;
}

void Text::colour( D2D1::ColorF colour )
{
    colour_ = colour;

    reset_brush();
    //reset();
}

void Text::set( wstring const & in_content )
{
    content_ = in_content;
        
    reset_layout();
}

void Text::add( wstring string )
{
    content_ += string;

    reset();
}

void Text::draw()
{
    context_2d->DrawTextLayout( position_ ,
                                layout_.Get() ,
                                brush_.Get() );
                                //font_options );

    if( border_show ) border.draw();
}

void Text::show_border( bool show )
{
    border_show = show;
}

void Text::reset_border()
{
    int x2 = layout_size().width;
    int y2 = layout_size().height;

    border.position( position_ , { x2 , y2 } );

    border + border_inner_margin;

    border.line_width( border_line_width );
    border.line_colour( border_line_colour );
}

float Text::top()
{
    return position_.y();
}

float Text::bottom()
{
    return position_.y() + height();
}

float Text::left()
{
    return position_.x();
}

float Text::right()
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