#include "Graphics\Direct2D\Direct2D.h"

#include "Application.h"
#include "Output\Logging.h"

//#include <winuser.h>

void Direct2D::initialise( HWND in_window )
{
    window = in_window;

    D2D1_FACTORY_OPTIONS factory_options {};

    factory_options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

    D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED ,
                       factory_options ,
                       factory_2d.ReleaseAndGetAddressOf() ) >> hr_check;

    D3D11CreateDevice( nullptr , // Adapter
                       D3D_DRIVER_TYPE_HARDWARE ,
                       nullptr , // Module
                       D3D11_CREATE_DEVICE_BGRA_SUPPORT ,
                       nullptr ,
                       0 ,       // Highest available feature level
                       D3D11_SDK_VERSION ,
                       & device_3d ,
                       nullptr , // Actual feature level
                       nullptr ) >> hr_check; // Device context

    
    device_3d.As( & device_gi ) >> hr_check;
    
    CreateDXGIFactory2( DXGI_CREATE_FACTORY_DEBUG ,
                        __uuidof( factory_gi ) ,
                        & factory_gi ) >> hr_check;

    create_swap_chain();

    factory_2d->CreateDevice( device_gi.Get() , & device_2d ) >> hr_check;

    // Create the Direct2D device context that is the actual render target
    // and exposes drawing commands.
    device_2d->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_NONE , & context_2d ) >> hr_check;

    // Retrieve the swap chain's back buffer
    swap_chain->GetBuffer( 0, __uuidof( surface ) , & surface ) >> hr_check;

    //float dpi_x {} , dpi_y {};

    factory_2d->ReloadSystemMetrics();
    uint dpi = GetDpiForWindow( window );
    
    // Create a Direct2D bitmap that points to the swap chain surface
    D2D1_BITMAP_PROPERTIES1 properties {};

    properties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    properties.pixelFormat.format    = DXGI_FORMAT_B8G8R8A8_UNORM;
    properties.bitmapOptions         = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
    properties.dpiX = dpi;
    properties.dpiY = dpi;

    context_2d->CreateBitmapFromDxgiSurface( surface.Get() , properties , & bitmap ) >> hr_check;

    // Point the device context to the bitmap for rendering    
    context_2d->SetTarget( bitmap.Get() );

    // Draw something
    //dc->BeginDraw();
    //dc->Clear();
    //dc->EndDraw();
    
    // Make the swap chain available to the composition engine
    //swapChain->Present( 1, // sync
    //                    0); // flags
       
    DCompositionCreateDevice( device_gi.Get() ,
                              __uuidof( device_composition ) ,
                              & device_composition ) >> hr_check;

    device_composition->CreateTargetForHwnd( window ,
                                             true , // Top most
                                             & target_composition ) >> hr_check;

    device_composition->CreateVisual( & visual_composition ) >> hr_check;
    
    visual_composition->SetContent( swap_chain.Get() ) >> hr_check;

    target_composition->SetRoot( visual_composition.Get() ) >> hr_check;

    device_composition->Commit() >> hr_check;

    reset();
}

void Direct2D::reset()
{
    //create_target();
    //create_swap_chain();
}

void Direct2D::create_swap_chain()
{
    DXGI_SWAP_CHAIN_DESC1 description {};

    description.Format      = DXGI_FORMAT_B8G8R8A8_UNORM;
    description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    description.SwapEffect  = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    description.BufferCount = 2;
    description.SampleDesc.Count = 1;
    description.AlphaMode   = DXGI_ALPHA_MODE_PREMULTIPLIED;

    RECT client_size{};

    GetClientRect( window , & client_size );

    description.Width  = client_size.right - client_size.left;
    description.Height = client_size.bottom - client_size.top;
    
    factory_gi->CreateSwapChainForComposition( device_gi.Get() ,
                                               & description ,
                                               nullptr , // Don’t restrict
                                               swap_chain.GetAddressOf() ) >> hr_check;
}

void Direct2D::draw_begin()
{
    if( context_2d )
    {
        //D2D1_SIZE_F renderTargetSize = target->GetSize();

        context_2d->BeginDraw();

        context_2d->SetTransform( D2D1::Matrix3x2F::Identity() );

        //context_2d->Clear( colour_clear );
        //context_2d->Clear( { 0.5, 0.5, 0.5, 1.0 } );
        //context_2d->Clear( D2D1::ColorF( 0 , 0.0f ) );
        context_2d->Clear( D2D1::ColorF( 0 , 0.0f ) );

        /*
        if( result == D2DERR_RECREATE_TARGET )
        {
            hr = S_OK;
            DiscardDeviceResources();
        }*/
    }
}

void Direct2D::draw_end()
{
    if( context_2d ) context_2d->EndDraw() >> hr_check;

    if( swap_chain ) swap_chain->Present( 1, 0 ) >> hr_check; 
}

D2D_SIZE_U Direct2D::screen_size()
{
    return { context_2d->GetPixelSize().width , context_2d->GetPixelSize().height };
}

D2D1_SIZE_F Direct2D::size_dips()
{
    //D2D1_SIZE_F size = 
    return { context_2d->GetSize().width , context_2d->GetSize().height };
}

D2D_SIZE_F Direct2D::dpi()
{
    D2D_SIZE_F page_dpi{ 0.0f , 0.0f };

    context_2d->GetDpi( &page_dpi.width , &page_dpi.height );

    return page_dpi;
}

void Direct2D::window_size_change( uint width , uint height )
{

    //if( context_2d ) context_2d->Resize( { width, height } );
    reset();

    //calculate_layout();   

    InvalidateRect( window , 0 , false );
}

//https://learn.microsoft.com/en-us/windows/win32/direct2d/supported-pixel-formats-and-alpha-modes
