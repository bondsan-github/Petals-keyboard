#include "..\headers\graphics_d2d.h"

#include "..\headers\locate.h"
#include "..\headers\write_d2d.h"
#include "..\headers\gui_windows_ms.h"

namespace hid
{
    void graphics_d2d::initialise( HWND in_window )
    {
        window = in_window;

        locate::add_service( service_identifier::graphics , * this );

        D2D1_FACTORY_OPTIONS factory_options {};
        factory_options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

        D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , factory_options , factory.ReleaseAndGetAddressOf() ); //static_cast< D2D1_FACTORY_TYPE >( factory_type::single_thread );
        
        reset();
    }

    //enum class request_type { page }
    //template< typename type >
    //type request( ... )

    page_window_pointer graphics_d2d::get_page()
    {
        return page.Get();
    }

    void graphics_d2d::reset()
    {
        RECT page_size {};

        //gui_windows_ms * window_pointer = any_cast< gui_windows_ms * >( locate::get_service( service_identifier::window ) );

        GetClientRect( window , & page_size );

        size.width  = page_size.right;
        size.height = page_size.bottom;

        D2D1_SIZE_U client_area = SizeU( size.width , size.height );

        D2D1_RENDER_TARGET_PROPERTIES render_properties = D2D1::RenderTargetProperties();
        //enum class alpha_mode { force_dword = -1 , unknown , pre_multiplied , straight , ignore };
        render_properties.pixelFormat = D2D1::PixelFormat( DXGI_FORMAT_UNKNOWN , D2D1_ALPHA_MODE_PREMULTIPLIED );

        D2D1_HWND_RENDER_TARGET_PROPERTIES window_properties = HwndRenderTargetProperties( window , client_area );

        factory->CreateHwndRenderTarget( render_properties ,
                                         window_properties , 
                                         page.ReleaseAndGetAddressOf() );
    }

    brush_solid_pointer graphics_d2d::brush_solid( colours in_colour)
    {
        brush_solid_pointer brush_solid{};
    
        get_page()->CreateSolidColorBrush( in_colour , brush_solid.ReleaseAndGetAddressOf());

        return brush_solid.Get();
    }

    
    //pass page
    /*
    ID2D1SolidColorBrush & graphics_d2d::brush_solid( colours in_colour )
    {
        brush_solid_pointer brush_solid {};
        HRESULT result;
        result = page->CreateSolidColorBrush( in_colour , brush_solid.ReleaseAndGetAddressOf() );

        return ** brush_solid.ReleaseAndGetAddressOf();
    }
    */

    /*
    ComPtr< stroke_style > graphics_d2d::style( colours in_colour )
    {
        ComPtr< stroke_style > style {};
        //factory->CreateStrokeStyle( style_properties , )
    }
    */
    stroke_style_pointer graphics_d2d::stroke_style( stroke_cap_style  in_cap_start   ,
                                                     stroke_cap_style  in_cap_dash    ,
                                                     stroke_cap_style  in_cap_end     ,
                                                     stroke_line_join  in_line_join   ,
                                                     float             in_miter_limit ,
                                                     stroke_dash_style in_dash_style  ,
                                                     float             in_dash_offset )
    {
        stroke_style_pointer    style{};
        stroke_style_properties properties{};
        vector< float >         dashes{ 2.0f, 2.0f };// length of each dash and space in the pattern.
        // [0] dash length
        // [1] space length ...

        properties.startCap    = static_cast< D2D1_CAP_STYLE >( in_cap_start );
        properties.endCap      = static_cast< D2D1_CAP_STYLE >( in_cap_dash );
        properties.dashCap     = static_cast< D2D1_CAP_STYLE >( in_cap_end );
        properties.lineJoin    = static_cast< D2D1_LINE_JOIN >( in_line_join );
        properties.miterLimit  = in_miter_limit;
        properties.dashStyle   = static_cast< D2D1_DASH_STYLE >( in_dash_style );
        properties.dashOffset  = in_dash_offset;

        /*
        properties.cap_start   = in_cap_start;
        properties.dash_start  = in_dash_start;
        properties.end_start   = in_end_start;
        properties.line_join   = in_line_join;
        properties.miter_limit = in_miter_limit;
        properties.dash_style  = in_dash_style;
        properties.dash_offset = in_dash_offset;
        */

        factory->CreateStrokeStyle( properties ,
                                    dashes.data() ,
                                    static_cast< uint >( dashes.size() ),
                                    style.ReleaseAndGetAddressOf() ); 
        return style;
    }

    void graphics_d2d::draw_rectangle( rectangle in_rectangle )
    {
        brush_solid_pointer brush = brush_solid();
        stroke_style_pointer style = stroke_style();
        float                stroke_width = 1.0f;

        page->DrawRectangle( in_rectangle , brush.Get() , stroke_width , style.Get());

    }

    void graphics_d2d::draw_rounded_rectangle( rounded_rectangle in_rectangle,
                                               float radius ,
                                               float boundry_width ,
                                               colours colour )
    {
        brush_solid_pointer brush = brush_solid( colour );
        stroke_style_pointer style = stroke_style();

        page->DrawRoundedRectangle( in_rectangle ,
                                    brush.Get() ,
                                    boundry_width ,
                                    style.Get() );
    }

    void graphics_d2d::draw_rounded_rectangle( dimensions in_size              ,
                                               vertex     in_position_top_left ,
                                               float      in_radius            ,
                                               float      in_width             ,
                                               colours    in_colour            )
    {
        vertex            position  { in_position_top_left };
        rounded_rectangle rectangle {};

        rectangle.radiusX = rectangle.radiusY = in_radius;

        rectangle.rect.top    = position.y;
        rectangle.rect.right  = position.x + in_size.width;
        rectangle.rect.bottom = position.y + in_size.height;
        rectangle.rect.left   = position.x;

        brush_solid_pointer brush = brush_solid( in_colour );
        stroke_style_pointer style = stroke_style();

        page->DrawRoundedRectangle( rectangle ,
                                    brush.Get() ,
                                    in_width ,
                                    style.Get() );
    }

    void graphics_d2d::draw()
    {
        if( page.Get() )
        {
            page->BeginDraw();

            page->SetTransform( Matrix3x2F::Identity() );

            page->Clear( colour_clear );

            page->EndDraw();
        }
    }

    page_dimensions graphics_d2d::get_size_pixels()
    {
        return { page->GetPixelSize().width , page->GetPixelSize().height };
    }

    D2D_SIZE_F graphics_d2d::get_size_dips()
    {
        return { page->GetSize().width , page->GetSize().height };
    }

    page_dpi graphics_d2d::get_dpi()
    {
        page->GetDpi( & dpi.width , & dpi.height );

        return dpi;
    }

    // void draw_page( page in_page );

    void graphics_d2d::draw_line( vertex in_a        , // 0..1
                                  vertex in_b        ,
                                  float in_width     ,
                                  colours in_colours )
    {
        //page_dimensions dimensions = get_size_pixels();
        //D2D1_SIZE_F size = get_size_dips();
        //page_dpi dpi = get_dpi();

        stroke_style_pointer style {}; // = stroke_style;
        brush_solid_pointer brush = brush_solid( in_colours );

        page->DrawLine( in_a , in_b , brush.Get() , in_width , style.Get());
    }

    void graphics_d2d::resize()
    {
        RECT rectangle;

        GetClientRect( window , & rectangle);

        D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

        if( page.Get() ) page->Resize( size );

        //calculate_layout();   

        InvalidateRect( window , 0 , false);
    }

}

        //page_dpi          dpi         = get_dpi();
        //dimensions        size_dips   = get_size_dips();
        //page_dimensions   size_pixels = get_size_pixels();
        // width  = 3840 , dpi.x = 240, dips.width = 1536 // (desktop 3840 x 2160 )
        // dips = pixels / ( dpi / 96.0 );
        //float center_x = in_position_center.x;// * size_dips.width; 
        //float center_y = in_position_center.y;// * size_dips.height; 
        //const float width       = in_size.width;// / dpi.width; 
        //const float height      = in_size.height;// / dpi.height;
        //const float width_half  = width  / 2.0f;
        //const float height_half = height / 2.0f;
        //const float margin      = 5.0f;
        //float top    = center_y - height_half - margin;
        //float right  = center_x + width_half  + margin;
        //float bottom = center_y + height_half + margin;
        //float left   = center_x - width_half  - margin;