//https://learn.microsoft.com/en-us/cpp/cpp/cpp-built-in-operators-precedence-and-associativity?view=msvc-170
#include "..\headers\graphics_d2d.h"

#include "..\headers\locate.h"
#include "..\headers\write_d2d.h"
#include "..\headers\gui_microsoft.h"

namespace hid
{
    graphics_d2d::graphics_d2d()
    {
        //OutputDebugString( L"graphics_d2d::constructor\n" );
    }

    void graphics_d2d::initialise( HWND in_window )
    {
        locate::set_graphics( this );

        window = in_window;

        D2D1_FACTORY_OPTIONS factory_options {};
        factory_options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

        D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , factory_options , & factory );

        //WaitForSingleObject( locate::get_windows().get_instance(), 1000 );
        
        reset();
    }

    void graphics_d2d::reset()
    {
        reset_page();
        reset_brush_line();
        reset_brush_rectangle();
    }

    graphics_d2d::~graphics_d2d() 
    { 
        //OutputDebugString( L"graphics_d2d::de-constructor\n" );

        if( page )            page->Release();
        if( factory )         factory->Release();
        if( brush_line )      brush_line->Release();
        if( brush_rectangle ) brush_rectangle->Release();
    }

    ID2D1HwndRenderTarget & graphics_d2d::get_page() 
    {
        return *page;
    }

    // help: your first direct2d program
    void graphics_d2d::reset_page()
    {
        /*
        // if existing page
        if( page )
        {
            page->Release();
            page = nullptr;
        }*/

        //HWND window = locate::get_windows().get_window();
        
        // full screen size
        RECT client_size {};
        GetClientRect( window , &client_size );
        D2D1_SIZE_U client_area = D2D1::SizeU( client_size.right , client_size.bottom );

        // enable render target transparency
        D2D1_RENDER_TARGET_PROPERTIES render_properties = D2D1::RenderTargetProperties();
        render_properties.pixelFormat = D2D1::PixelFormat( DXGI_FORMAT_UNKNOWN , D2D1_ALPHA_MODE_PREMULTIPLIED );
        D2D1_HWND_RENDER_TARGET_PROPERTIES window_properties = D2D1::HwndRenderTargetProperties( window , client_area );

        factory->CreateHwndRenderTarget( render_properties ,
                                         window_properties , 
                                         &page );
    }
   
    void graphics_d2d::reset_brush_line()
    {
        /*
        if( brush_line )
        {
            brush_line->Release();
            brush_line = nullptr;
        }*/

        page->CreateSolidColorBrush( line_colour , &brush_line );
    }

    void graphics_d2d::reset_brush_rectangle()
    {
        /*if( brush_rectangle )
        {
            brush_rectangle->Release();
            brush_rectangle = nullptr;
        }*/

        page->CreateSolidColorBrush( line_colour , &brush_rectangle );
    }

    /*
    void graphics_d2d::draw_rectangle( rectangle in_rectangle )
    {
        brush_solid_pointer brush = brush_solid();
        stroke_style_pointer style = stroke_style();
        float                stroke_width = 1.0f;

        //page->DrawRectangle( in_rectangle , brush.Get() , stroke_width , style.Get());

    }
    */

    /*
    void graphics_d2d::draw_rounded_rectangle( D2D1_ROUNDED_RECT in_rectangle,
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
    */

    void graphics_d2d::draw_rounded_rectangle( D2D_SIZE_F in_size              ,
                                               vertex     in_position_top_left ,
                                               float      in_corner_radius ,
                                               ID2D1Brush * in_brush ,
                                               float        in_line_width )
                                               //colours in_colour )
    {
        //if( page and in_brush )
        //{
            vertex            position  { in_position_top_left };
            D2D1_ROUNDED_RECT rectangle {};

            rectangle.radiusX = rectangle.radiusY = in_corner_radius;

            rectangle.rect.top    = position.y;
            rectangle.rect.right  = position.x + in_size.width;
            rectangle.rect.bottom = position.y + in_size.height;
            rectangle.rect.left   = position.x;


            page->DrawRoundedRectangle( rectangle ,
                                        in_brush ,
                                        in_line_width ,
                                        0 );
        //}
    }

    void graphics_d2d::draw_begin()
    {
        if( page )
        {
            page->BeginDraw();

            page->SetTransform( D2D1::Matrix3x2F::Identity() );

            page->Clear( colour_clear );

            /*
            if( hr == D2DERR_RECREATE_TARGET )
            {
                hr = S_OK;
                DiscardDeviceResources();
            }*/
        }
    }

    void graphics_d2d::draw_end()
    {
        page->EndDraw();
    }

    D2D_SIZE_U graphics_d2d::get_screen_size()
    {
        return { page->GetPixelSize().width , page->GetPixelSize().height };
    }

    D2D1_SIZE_F graphics_d2d::get_size_dips()
    {
        //D2D1_SIZE_F size = 
        return { page->GetSize().width , page->GetSize().height };
    }

    D2D_SIZE_F graphics_d2d::get_dpi()
    {
        D2D_SIZE_F page_dpi{ 0.0f , 0.0f };

        page->GetDpi( &page_dpi.width , &page_dpi.height );

        return page_dpi;
    }

    // void draw_page( page in_page );

    void graphics_d2d::draw_line_solid( vertex in_a , 
                                        vertex in_b )
    {
        //page_dimensions dimensions = get_size_pixels();
        //D2D1_SIZE_F size = get_size_dips();
        //page_dpi dpi = get_dpi();

        //stroke_style_pointer style {}; // = stroke_style;
        //brush_solid_pointer brush = brush_solid( in_colours );

        page->DrawLine( in_a , in_b , brush_line , line_width );
    }

    void graphics_d2d::resize()
    {
        RECT rectangle;
        HWND window = locate::get_windows().get_window();

        GetClientRect( window , & rectangle);

        D2D1_SIZE_U size = D2D1::SizeU( rectangle.right , rectangle.bottom );

        //if( page ) 
        page->Resize( size );

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


    /*
    brush_solid_pointer graphics_d2d::get_brush_solid( colours in_colour)
    {
        brush_solid_pointer brush_solid{};
        get_page()->CreateSolidColorBrush( in_colour , brush_solid.ReleaseAndGetAddressOf());
        return brush_solid.Get();
    }
    */

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

    /*
    stroke_style_pointer graphics_d2d::get_stroke_style( stroke_cap_style  in_cap_start   ,
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


        //properties.cap_start   = in_cap_start;
        //properties.dash_start  = in_dash_start;
        //properties.end_start   = in_end_start;
        //properties.line_join   = in_line_join;
        //properties.miter_limit = in_miter_limit;
        //properties.dash_style  = in_dash_style;
        //properties.dash_offset = in_dash_offset;


        factory->CreateStrokeStyle( properties ,
                                    dashes.data() ,
                                    static_cast< uint >( dashes.size() ),
                                    style.ReleaseAndGetAddressOf() );
        return style;
    }
    */