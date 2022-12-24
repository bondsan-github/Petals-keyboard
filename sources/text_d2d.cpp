#include "..\headers\text_d2d.h"

#include "..\headers\locate.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    //text::text( void ) { OutputDebugString( L"\n text::default constructor" ); }
    //text::text( const text & copy ) { OutputDebugString( L"\n text::copy constructor" ); }
    /*
    text::text( text && move ) 
    { 
        OutputDebugString( L"\n text::move constructor" );

        format.Swap( move.format );
        brush.Swap( move.brush );
        layout.Swap( move.layout );
        collection.Swap( move.collection );
    }
    */
    /*
    text & text::operator = ( const text & assignment ) 
    { 
        OutputDebugString( L"\n text::assignment" );
        return *this;
    }
    */
    /*
    text & text::operator = ( const text && assignment_move ) 
    { 
        OutputDebugString( L"\n text::assignment_move" );
        return *this;
    }
    */

    void text::set_font_locale( string in_font_locale )
    {
        if( in_font_locale.empty() )
            font_locale = L"en-us"; // en-uk
            // else not a vaild locale
        else
            font_locale = in_font_locale;
    }

    void text::set_font_face( string in_font_face )
    {
        if( in_font_face.empty() )
            font_face = L"Times New Roman";
        else
            font_face = in_font_face;
    }

    void text::set_font_size( float in_font_size )
    {
        if( in_font_size <= 0.0f )//|| in_font_size > )
            font_size = 0.1f;
        else
            font_size = in_font_size;
    }

    void text::set_font_style( DWRITE_FONT_STYLE in_font_style )
    {
        if( in_font_style != DWRITE_FONT_STYLE_NORMAL  || 
            in_font_style != DWRITE_FONT_STYLE_OBLIQUE ||
            in_font_style != DWRITE_FONT_STYLE_ITALIC ) font_style = DWRITE_FONT_STYLE_NORMAL;
        else
            font_style = in_font_style;
    }
    
    //void text::set_font_options( const font_options in_font_options ) { font_options = in_font_options; }
    //font_options text::get_font_options() const { return _font_options; }

    void text::set_font_opacity( float in_font_opacity ) 
    {
        if( in_font_opacity < 0.0f ) // || > 1.0f clamp(0.0,1.0);
            font_opacity = 0.0f;
        else
            font_opacity = in_font_opacity;
    }

    void text::set_font_weight( DWRITE_FONT_WEIGHT in_font_weight )
    {
        font_weight = in_font_weight;
    }

    void text::set_font_stretch( DWRITE_FONT_STRETCH in_font_stretch )
    {
        font_stretch = in_font_stretch;
    }

    void text::set_layout_size( D2D1_SIZE_F in_layout_size )
    {
        // check sizes are within all screen bounds
        layout_size = in_layout_size;
    }
    //dimensions text::get_layout_size() { return layout_size; }

    void text::set_rectangle_size( rectangle in_rectangle_size ) 
    {
        rectangle_size = in_rectangle_size;
    }

    void text::set_rounded_rectangle_radius( float in_radius )
    {
        rectangle_radius = in_radius;

        rounded_rectangle.radiusX = rectangle_radius;
        rounded_rectangle.radiusY = rectangle_radius;
    }

    /*
    text::~text( void )
    {
        OutputDebugString( L"\n text::de-constructor" );

        if( format ) format->Release();//Reset();
        if( brush  ) brush->Release();//.Reset();
        if( layout ) layout->Release();//Reset();
        if( collection ) collection->Release();//Reset();
    }
    */

    void text::reset()
    {
        reset_format();
        reset_layout();
        reset_brush();
    }

    void text::reset_format()
    {
        locate::get_write().get_format( format,
                                        font_face ,
                                        nullptr ,//collection ,
                                        font_weight ,
                                        font_style ,
                                        font_stretch ,
                                        font_size ,
                                        font_locale );
    }

    void text::reset_layout()
    {
        locate::get_write().get_layout( layout , content , format , layout_size );

        reset_rectangle();
    }

    void text::reset_brush()
    {
        locate::get_graphics().get_page()->CreateSolidColorBrush( font_colour , & brush );
    }

    float text::get_layout_width()
    { 
        layout->GetMetrics( & layout_metrics );
        return layout_metrics.width;
    }
    
    float text::get_layout_width_half() { return get_layout_width() / 2.0f; }

    float text::get_layout_height()
    { 
        layout->GetMetrics( & layout_metrics );
        return layout_metrics.height;
    }

    float text::get_layout_height_half() { return get_layout_height() / 2.0f; }
    
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

    void text::set_position_top_left( vertex in_position_top_left )
    {
        //set_position_top_left( in_position_top_left );

        reset_rectangle();
    }

    vertex text::get_position_top_left()
    {
        //return D2D1_POINT_2F(position_top_left.x , position_top_left.y);
        return { position_top_left.x , position_top_left.y };
    }

    void text::set_font_colour( colours in_font_colour )
    {
        font_colour = in_font_colour;

        reset_brush();
    }

    void text::set_rectangle_line_width( float const in_width )
    {
        rectangle_line_width = in_width;
    }
    
    void text::set_rectangle_line_colour( colours const in_colour )
    {
        rectangle_line_colour = in_colour;
    }

    void text::set_content( string in_content )
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
        locate::get_graphics().get_page()->DrawTextLayout( position_top_left, //get_position() ,
                                                       layout ,
                                                       brush );
                                                        //static_cast< D2D1_DRAW_TEXT_OPTIONS >( font_options ) );
    }

    void text::draw_rectangle()
    {
        locate::get_graphics().draw_rounded_rectangle( rounded_rectangle , rectangle_radius , rectangle_line_width , rectangle_line_colour );
    }

    planes text::get_middle_planes()
    {
        planes middle {};

        middle.horizontal = get_position_top_left().x + get_layout_width_half();
        middle.vertical   = get_position_top_left().y + get_layout_height_half();

        return middle;
    }

    //text_metrics text::get_text_metrics()    {}

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


    void text::reset_rectangle()
    {
    /*
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
        */
    }

    /*
    rectangle text::get_layout_rectangle()
    {

        vertex position = get_position_top_left();

        layout_rectangle.top    = position.y + layout_metrics.top;
        layout_rectangle.right  = position.x + layout_metrics.width;
        layout_rectangle.bottom = position.y + layout_metrics.height;
        layout_rectangle.left   = position.x + layout_metrics.left;

        return layout_size;
    }
    */

}