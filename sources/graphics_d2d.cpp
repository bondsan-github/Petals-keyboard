#include "..\headers\graphics_d2d.h"

#include "..\headers\locate.h"

namespace hid
{
    void graphics_d2d::initialise()
    {
        locate::provide_graphics( this );

        D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , factory.ReleaseAndGetAddressOf() );

        reset();
    }

    void graphics_d2d::reset()
    {
        GetClientRect( locate::window() , & dimensions );

        D2D1_SIZE_U client_area = SizeU( dimensions.right , dimensions.bottom );

        factory->CreateHwndRenderTarget( RenderTargetProperties() ,
                                         HwndRenderTargetProperties( locate::window() , client_area ) ,
                                         sheet.ReleaseAndGetAddressOf() );
    }

    window_render_target * graphics_d2d::sheet_ptr()
    {
        return sheet.Get();
    }

    //void set_sheet( const ID2D1HwndRenderTarget * in_sheet )
      //sheets.emplace_back( window_ptr , size );

    void graphics_d2d::draw()
    {
        HWND window_pointer = nullptr;
             window_pointer = locate::window();

        if( window_pointer )
        {
            BeginPaint( window_pointer , & client_area );

            if( sheet.Get() )
            {
                sheet->BeginDraw();

                sheet->SetTransform( Matrix3x2F::Identity() );

                sheet->Clear( colour_clear );

                sheet->EndDraw();
            }

            EndPaint( window_pointer , & client_area );
        }
    }

    void graphics_d2d::resize()
    {
        HWND window = nullptr;
        window = locate::window();

        if( window )
        {
            RECT rectangle;

            GetClientRect( window , &rectangle );

            D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

            if( sheet.Get() ) sheet->Resize( size );

            //calculate_layout();

            InvalidateRect( window , 0 , false );
        }
    }

} // namespace hid