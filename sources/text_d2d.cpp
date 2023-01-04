#include "..\headers\text_d2d.h"
#include "..\headers\locate.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

#include <string>

namespace hid
{
    text::text()
    {
        identifier += 1;

        OutputDebugStringW( L"text::default constructor" );
        std::wstring message = L" id: " + std::to_wstring(identifier) + L"\n";
        OutputDebugStringW( message.c_str() );
        
        reset();
    }

    text::text( const text &copy )
    {
        //OutputDebugStringW( L"text::copy constructor" );
        //std::wstring message = L" id: " + std::to_wstring( identifier ) + L"\n";
        //OutputDebugStringW( message.c_str() );

        if( this != &copy ) *this = copy;
    }

    text::text( text &&in_move ) noexcept
    { 
        //OutputDebugStringW( L"text::move constructor" );
        //std::wstring message = L" id: " + std::to_wstring( identifier ) + L"\n";
        //OutputDebugStringW( message.c_str() );

        if( this != &in_move ) *this = std::move( in_move );
    }

    text & text::operator = ( const text &assign_copy )
    {
        OutputDebugStringW( L"text::assign copy to" );
        std::wstring message = L" id: " + std::to_wstring( identifier )
        + L" from id: " + std::to_wstring(assign_copy.get_id()) + L"\n";
        OutputDebugStringW( message.c_str() );

        if( this not_eq &assign_copy )
        { 
            if( assign_copy.format )
            {
                format = assign_copy.format;
                format->AddRef();
            }

            if( assign_copy.layout )
            {
                layout = assign_copy.layout;
                layout->AddRef();
            }

            if( assign_copy.brush_font )
            {
                brush_font = assign_copy.brush_font;
                brush_font->AddRef();
            }

            content           = assign_copy.content;
            position_top_left = assign_copy.position_top_left;
            font_locale       = assign_copy.font_locale;
            font_face         = assign_copy.font_face;
            font_size         = assign_copy.font_size;
            //font_colour       = assign_copy.font_colour;
            font_opacity      = assign_copy.font_opacity;
            //font_style        = assign_copy.font_style;
            //font_weight       = assign_copy.font_weight;
            //font_stretch      = assign_copy.font_stretch;
            layout_size       = assign_copy.layout_size;
            bounding_rectangle_show          = assign_copy.bounding_rectangle_show;
            bounding_rectangle_line_width    = assign_copy.bounding_rectangle_line_width;
            //bounding_rectangle_line_colour   = assign_copy.bounding_rectangle_line_colour;
            bounding_rectangle_corner_radius = assign_copy.bounding_rectangle_corner_radius;
            bounding_rectangle_inner_margin  = assign_copy.bounding_rectangle_inner_margin;
        }
        
        return *this;
    }

    text & text::operator = ( text &&assign_move ) noexcept
    {
        OutputDebugStringW( L"text::assignment move" );
        std::wstring message = L" id: " + std::to_wstring( identifier )
        + L" from id: " + std::to_wstring( assign_move.get_id() ) + L"\n";
        OutputDebugStringW( message.c_str() );

        if( this != &assign_move )
        {
            if( assign_move.format )
            {
                format = std::move( assign_move.format );
                //assign_move.format->Release();
                assign_move.format = nullptr;
            }

            if( assign_move.layout )
            {
                layout = std::move( assign_move.layout );
                //assign_move.layout->Release();
                assign_move.layout = nullptr;
            }

            if( assign_move.brush_font )
            {
                brush_font = std::move( assign_move.brush_font );
                //assign_move.brush_font->Release();
                assign_move.brush_font = nullptr;
            }

            content           = std::move( assign_move.content);
            position_top_left = std::move( assign_move.position_top_left );
            font_locale       = std::move( assign_move.font_locale );
            font_face         = std::move( assign_move.font_face );
            font_size         = std::move( assign_move.font_size );
            //font_colour       = std::move( assign_move.font_colour );
            font_opacity      = std::move( assign_move.font_opacity );
            //font_style        = std::move( assign_move.font_style );
            //font_weight       = std::move( assign_move.font_weight );
            //font_stretch      = std::move( assign_move.font_stretch );
            layout_size       = std::move( assign_move.layout_size );
            bounding_rectangle_show          = std::move( assign_move.bounding_rectangle_show );
            bounding_rectangle_line_width    = std::move( assign_move.bounding_rectangle_line_width );
            //bounding_rectangle_line_colour   = std::move( assign_move.bounding_rectangle_line_colour );
            bounding_rectangle_corner_radius = std::move( assign_move.bounding_rectangle_corner_radius );
            bounding_rectangle_inner_margin  = std::move( assign_move.bounding_rectangle_inner_margin );

            //assign_move.re_initialise();
        }

        return *this;
    }

    void text::re_initialise()
    {
        OutputDebugStringW( L"text::re_initialise" );
        std::wstring message = L" id: " + std::to_wstring( identifier ) + L"\n";
        OutputDebugStringW( message.c_str() );

        //if( format )     { format->Release();     format     = nullptr; } 
        //if( brush_font ) { brush_font->Release(); brush_font = nullptr; }
        //if( layout )     { layout->Release();     layout     = nullptr; }
        //if( collection ) { collection->Release(); collection = nullptr; }

        content           = L"empty";
        position_top_left = vertex{ 0.0f , 0.0f };
        font_locale       = L"en-us";
        font_face         = L"Times New Roman"; 
        font_size         = 15.0f; 
        font_colour       = D2D1::ColorF::Black;
        font_opacity      = 1.0f;
        font_style        = DWRITE_FONT_STYLE_NORMAL;
        font_weight       = DWRITE_FONT_WEIGHT_NORMAL;
        font_stretch      = DWRITE_FONT_STRETCH_NORMAL;

        layout_size = D2D1_SIZE_F{ 150.0f , 150.0f };
        
        bounding_rectangle_show         = true;
        bounding_rectangle_line_width   = 1.0f;
        bounding_rectangle_line_colour  = D2D1::ColorF::Yellow;
        bounding_rectangle_corner_radius       = 0.0f;
        bounding_rectangle_inner_margin = 0.0f;
        //rounded_rectangle      = D2D1_ROUNDED_RECT{ .radiusX = rectangle_radius ,
         //                                           .radiusY = rectangle_radius };
        reset();
    }

    text::~text()
    {
        OutputDebugString( L"text::de-constructor" );
        std::wstring message = L" id: " + std::to_wstring( identifier ) + L"\n";
        OutputDebugStringW( message.c_str() );

        if( format )// not_eq nullptr ) 
        {
            format->Release(); 
            format = nullptr;
        }

        if( brush_font )
        {
            brush_font->Release();
            brush_font = nullptr;
        }

        if( layout ) 
        {
            layout->Release(); 
            layout = nullptr;
        }

        if( collection ) 
        {
            collection->Release();
            collection = nullptr;
        }
    }

    void text::set_font_locale( std::wstring in_font_locale )
    {
        if( in_font_locale.empty() )
            font_locale = L"en-us"; // en-GB
            // else not a vaild locale
        else
            font_locale = in_font_locale;

        reset();
    }

    void text::set_font_face( std::wstring in_font_face )
    {
        if( in_font_face.empty() ) // is_not_valid_font_face()
            font_face = L"Times New Roman";
        else
            font_face = in_font_face;

        reset();
    }

    void text::set_font_size( float in_font_size )
    {
        if( in_font_size <= 0.0f )//|| in_font_size > )
            font_size = 0.1f;
        else
            font_size = in_font_size;

        reset();
    }

    void text::set_font_style( DWRITE_FONT_STYLE in_font_style )
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

    void text::set_font_opacity( float in_font_opacity ) 
    {
        if( in_font_opacity < 0.0f ) // || > 1.0f clamp(0.0,1.0);
            font_opacity = 0.0f;
        else
            font_opacity = in_font_opacity;

        reset();
    }

    void text::set_font_weight( DWRITE_FONT_WEIGHT in_font_weight )
    {
        // between 1 and 999
        font_weight = in_font_weight;
        reset();
    }

    void text::set_font_stretch( DWRITE_FONT_STRETCH in_font_stretch )
    {
        font_stretch = in_font_stretch;
        reset();
    }

    void text::set_layout_size( D2D1_SIZE_F in_layout_size )
    {
        // check sizes are within all screen bounds
        layout_size = in_layout_size;
        reset();
    }

    D2D1_SIZE_F text::get_layout_size() const
    { 
        //if( layout ) // call to draw before text initialised
        //{
            DWRITE_TEXT_METRICS metrics;
            layout->GetMetrics( &metrics );
        
            return { metrics.layoutWidth , metrics.layoutHeight };
        //}
        //else return { 0.0f , 0.0f };
    }

    /*

    void text::set_bounding_rectangle_corner_radius( float in_radius )
    {
        rectangle_radius = in_radius;

        bounding_rectangle_corner_radius.radiusX = rectangle_radius;
        bounding_rectangle_corner_radius.radiusY = rectangle_radius;
    }
    */
    
    void text::reset()
    {
        OutputDebugString( L"text::reset" );
        std::wstring message = L" id: " + std::to_wstring( identifier ) + L"\n";
        OutputDebugStringW( message.c_str() );

        reset_format();
        reset_layout();
        reset_brush();
    }

    void text::reset_format()
    {
        if( format )
        {
            format->Release();
            format = nullptr;
        }

        locate::get_write().get_write_factory().CreateTextFormat( font_face.c_str(),
                                                                  nullptr , // in_font_collection // (NULL sets it to use the system font collection).
                                                                  font_weight ,
                                                                  font_style ,
                                                                  font_stretch ,
                                                                  font_size ,
                                                                  font_locale.c_str() ,
                                                                  &format );// address of pointer to COM object  
    }

    void text::reset_layout()
    {
        //layout = locate::get_write().get_layout( layout , content , format , layout_size );
        
        if( layout )
        {
            layout->Release();
            layout = nullptr;
        }

        locate::get_write().get_write_factory().CreateTextLayout( content.c_str() ,
                                                                  static_cast< uint >( content.size() ),
                                                                  format ,
                                                                  layout_size.width ,
                                                                  layout_size.height ,
                                                                  &layout );
        //reset_rectangle();
    }

    void text::reset_brush()
    {
        if( brush_font )
        {
            brush_font->Release();
            brush_font = nullptr;
        }

        locate::get_graphics().get_page().CreateSolidColorBrush( font_colour , &brush_font );
    }

    float text::get_layout_width()
    { 
        layout->GetMetrics( & layout_metrics );
        return layout_metrics.width;
    }
    
    float text::get_layout_width_half() 
    {
        return get_layout_width() / 2.0f;
    }

    float text::get_layout_height()
    { 
        //if( layout )
        //{
            layout->GetMetrics( &layout_metrics );
            return layout_metrics.height;
        //}
        //else return 0.0f;
    }

    float text::get_layout_height_half() 
    {
        return get_layout_height() / 2.0f;
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

    void text::set_position_top_left( vertex in_position_top_left )
    {
        position_top_left = in_position_top_left;

        //reset_rectangle();
    }

    vertex text::get_position_top_left()
    {
        return { position_top_left.x , position_top_left.y };
    }

    void text::set_font_colour( D2D1::ColorF in_font_colour )
    {
        font_colour = in_font_colour;

        reset_brush();
        //reset();
    }

    void text::set_content( std::wstring in_content )
    {
        content = in_content;
        reset();
    }

    void text::add_content( std::wstring in_string )
    {
        content += in_string;
        reset();
    }

    void text::draw() const
    {
        draw_text();
        if( bounding_rectangle_show ) draw_bounding_rectangle();
    }

    void text::draw_text() const
    {
        //if( layout and brush_font )
        locate::get_graphics().get_page().DrawTextLayout( position_top_left, //get_position() ,
                                                          layout ,
                                                          brush_font );
                                                        //static_cast< D2D1_DRAW_TEXT_OPTIONS >( font_options ) );
    }

    void text::draw_bounding_rectangle() const
    {
        vertex position = position_top_left;

        position.x -= bounding_rectangle_inner_margin;
        position.y -= bounding_rectangle_inner_margin;
        
        D2D_SIZE_F size = get_layout_size();
        size.width  += bounding_rectangle_inner_margin * 2.0f;
        size.height += bounding_rectangle_inner_margin * 2.0f;

        locate::get_graphics().draw_rounded_rectangle( size ,
                                                       position ,
                                                       bounding_rectangle_corner_radius , 
                                                       brush_font ,
                                                       bounding_rectangle_line_width );
    }

    float text::get_bottom()
    {
        return { get_layout_height() + bounding_rectangle_inner_margin };
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
        
    }
    */

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

} // namespace hid