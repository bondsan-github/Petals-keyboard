#include "Graphics\Graphics.hpp"

#include "Application2d.hpp"
#include "Operating system\MSWindows.hpp"
#include "Graphics\DXGI formats.hpp"
#include "Logging.hpp"

#include <iostream>
#include <fstream>
#include <map>

using std::wstring;
using std::vector;
using std::map;
using std::to_wstring;

Graphics::Graphics( Application & in_application )
: application { in_application }
{}

Graphics::~Graphics()
{
/*
    blend_state.Reset();
    sampler_state.Reset();
    input_layout_.Reset();
    pixel_shader_.Reset();
    vertex_shader_.Reset();
    rasteriser_state.Reset();
    depth_stencil_view.Reset();
    depth_stencil.Reset();
    render_target_view.Reset();
    render_target.Reset();
    dxgi_factory2.Reset();
    dxgi_factory7.Reset();
    dxgi_adapter.Reset();
    dxgi_device.Reset();
    swap_chain.Reset();
  */  
    //device_context->ClearState();
    //device_context->Flush();

    //device_context.Reset();
    //long count = device.Reset();

//Objects with Refcount=0 and IntRef=0 will be eventually destroyed through typical Immediate Context usage.
//However, if the application requires these objects to be destroyed sooner,
//ClearState followed by Flush on the Immediate Context will realize their destruction.
    
    //wic_factory.Reset();

    if( debug_output )
        d3d_debug->ReportLiveDeviceObjects( D3D11_RLDO_DETAIL | D3D11_RLDO_IGNORE_INTERNAL );//D3D11_RLDO_SUMMARY
}

bool Graphics::initialise( HWND in_window )
{
    window = in_window;
    
    //swap_chain_size = MSWindows::client_size;
    
    RECT area{};

    GetClientRect( window , &area );

    swap_chain_size = { area.right - area.left , area.bottom - area.top };

    create_dxgi_factory();    
    
    //enumerate_hardware_devices();

    create_hardware_device();

    create_device_resources();
     
    if( debug_output ) configure_debuging();

    create_window_size_dependent_resources( swap_chain_size.width() ,
                                            swap_chain_size.height() );

    // Setup viewport to translate pixel coordinates to normalised coordinates.
    set_viewport( viewport );

    return true;
}

void Graphics::configure_debuging()
{
    //result = DXGIGetDebugInterface1( 0 ,  __uuidof( dxgi_debug ) , & dxgi_debug );
    
    result = d3d_device.As( & d3d_debug );

    if FAILED( result ) print_debug( L"\n Unable to get debug interface." , result );

    result = d3d_debug.As( & info_queue );

    if FAILED( result ) print_debug( L"\n Unable to get debug information queue." , result );

    result = info_queue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_CORRUPTION , true );
    result = info_queue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_ERROR , true );

    D3D11_MESSAGE_CATEGORY hide_catagories[] =
    {
        D3D11_MESSAGE_CATEGORY_STATE_CREATION,
        //D3D11_MESSAGE_CATEGORY_INITIALIZATION,
    };

    D3D11_MESSAGE_ID hide_messages[] =
    {
        D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
        // TODO: Add more message IDs here as needed.
    };

    D3D11_INFO_QUEUE_FILTER filter{};

    filter.DenyList.pCategoryList = hide_catagories;
    filter.DenyList.NumCategories = _countof( hide_catagories );
    filter.DenyList.NumIDs = _countof( hide_messages );
    filter.DenyList.pIDList = hide_messages;

    result = info_queue->AddStorageFilterEntries( & filter );

    if( FAILED( result ) ) print_debug( L"\n Unable to add filter entries." , result );

    result = device_context.As( & annotation );

    if( FAILED( result ) ) print_debug( L"\n Unable to get Annotation interface." , result );
}

void Graphics::create_dxgi_factory()
{

#if defined( _DEBUG )// and ( _WIN32_WINNT >= 0x0603 )
    dxgi_flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

    result = CreateDXGIFactory2( dxgi_flags , __uuidof( dxgi_factory2.Get() ) , & dxgi_factory2 );

    if( FAILED( result ) ) error_exit( L"Unable to create DXGI 2 factory." , result );
    
    //print_debug( L"\n DXGI factory 2 created." );

    result = dxgi_factory2.As( & dxgi_factory7 );

    if( FAILED( result ) ) error_exit( L"Unable to get DXGI 7 interface." , result );

    //dxgi_factory2->SetPrivateData( __uuidof( dxgi_factory2.Get() ), wcslen( L"dxgi factory 2" ) *2 , L"dxgi factory 2");
    //set_name( dxgi_factory2.Get() , L"dxgi factory 2" );
    //print_debug(L"\n DXGI factory 7 created.");
}

void Graphics::create_hardware_device()// IDXGIAdapter1 ** adapter )
{
#ifdef _DEBUG

    device_flags |= D3D11_CREATE_DEVICE_DEBUG;// & D3D11_CREATE_DEVICE_DEBUGGABLE;

#endif

	result = D3D11CreateDevice( nullptr , // specify nullptr to use the default adapter
                                D3D_DRIVER_TYPE_HARDWARE , // The D3D_DRIVER_TYPE, which represents the driver type to create
                                nullptr , // A handle to a DLL that implements a software rasterizer
                                device_flags , // The runtime layers to enable
                                feature_levels , // A pointer to an array of D3D_FEATURE_LEVELs
                                _countof( feature_levels ) , // The number of elements in D3D_FEATURE_LEVEL []
                                D3D11_SDK_VERSION , // The SDK version; use D3D11_SDK_VERSION
                                & d3d_device , // returns the Direct3D device created
                                & feature_level , // returns feature level of device created
                                device_context.GetAddressOf() ); // returns the device immediate context

	if( FAILED( result ) ) error_exit( L"Unable create DX11 device." , result );

    // Get a DX11 5 interface from the device
    //result = d3d_device.As( & d3d_device5 );
    //if( FAILED( result ) ) error_exit( L"Unable to get DX11 5 interface." , result );

    set_device3d( d3d_device.Get() );

    // Get a Device Context version 1 from context
    result = device_context.As( & device_context1 );

    if( FAILED( result ) ) error_exit( L"Unable to get Device Context 1 interface." , result );
    

    // -- D2D initialisation --
    result = d3d_device.As( & dxgi_device );
    
    if( FAILED( result ) ) error_exit( L"Unable to get DXGI interface." , result );

    result = D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED ,
                                d2d_factory7.ReleaseAndGetAddressOf() );

    if( FAILED( result ) ) error_exit( L"Unable to create D2D factory." , result );
    
    result = d2d_factory7->CreateDevice( dxgi_device.Get() , & d2d_device6 );

    if( FAILED( result ) ) error_exit( L"Unable to create D2D device 6." , result );

    result = d2d_device6->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
                                               & d2d_context );

    if( FAILED( result ) ) error_exit( L"Unable to create D2D device context." , result );

    set_context_2d( d2d_context.Get() );

    // -- WIC --
    result = CoCreateInstance( CLSID_WICImagingFactory2 , nullptr , CLSCTX_INPROC_SERVER , IID_PPV_ARGS( & wic_factory ) );
    
    if( FAILED( result ) ) error_exit( L"Unable to create WIC imaging factory 2." , result );

    //set_factory( wic_factory.Get() );
    //set_name( d3d_device5.Get() , L"Device 5");
    //set_name( d3d_device.Get() , L"Device");
    
    if( debug_output ) print_debug( L"\n Device created." );
}
	
bool Graphics::create_device_resources()
{
    // ** layout signature comes from a vertex shader!! ** ( not P.S. )
    if( create_input_layout( L".\\data\\shaders\\vertex_shader.cso" ,
                             input_layouts ,
                             &input_layout_ ) )
    {
        if( create_vertex_shader( L".\\data\\shaders\\vertex_shader.cso" , &vertex_shader_ ) )
        {
            create_pixel_shader( L".\\data\\shaders\\pixel_shader.cso" , &pixel_shader_ );

            // Configure the rules of applying textures to polygons
            create_samplers( sampler_description , &sampler_state );

            // Setup the raster description which will determine 
            //  how and what polygons will be drawn.
            create_rasteriser( rasteriser_description , &rasteriser_state );

            // Configure how colours are blended
            //create_blend( blend_descripton , &blend_state );

            // Set results for depth collision tests
            //create_depth_state();
        }
    }

    return true;
}

void Graphics::enumerate_hardware_devices()
{
    ComPtr< IDXGIAdapter1 >                adapter1 {};
    std::vector< ComPtr< IDXGIAdapter4 > > adapters {};
    uint                                   index    {};

    // Request all available display adapters.
    while( dxgi_factory7->EnumAdapters1( index , & adapter1 ) != DXGI_ERROR_NOT_FOUND )
    {
        ComPtr< IDXGIAdapter4 > adapter4 {};

        adapter1.As( & adapter4 );

        adapters.push_back( adapter4 );
        index++;
    }

    DXGI_ADAPTER_DESC3 gpu_description {};

    // For all adapters output hardware description and available display modes.
    for( auto & gpu : adapters )
    {
        gpu->GetDesc3( &gpu_description );

        if( debug_output ) 
        {
            wstring text { L"\nAdapter description: " };

            text += gpu_description.Description;
            text += L"\n Video RAM amount: ";
            text += to_wstring( gpu_description.DedicatedVideoMemory > 0 ? gpu_description.DedicatedVideoMemory / 1048576 : 0 );
            text += L" mebibytes\n System RAM amount: ";
            text += to_wstring( gpu_description.DedicatedSystemMemory > 0 ? gpu_description.DedicatedSystemMemory / 1048576 : 0 );
            text += L" mebibytes\n Shared RAM amount: ";
            text += to_wstring( gpu_description.SharedSystemMemory > 0 ? gpu_description.SharedSystemMemory / 1048576 : 0 );
            text += L" mebibytes";
        
            print_debug( text.c_str() );
        }

        uint                                  index       {};
        ComPtr< IDXGIOutput >                 gpu_output  {};
        ComPtr< IDXGIOutput6 >                gpu_output6 {};
        vector< ComPtr< IDXGIOutput6 > >      gpu_outputs {};

        // Retreive list of available display adapters.
        while( gpu->EnumOutputs( index , & gpu_output ) != DXGI_ERROR_NOT_FOUND )
        {
            gpu_output.As( & gpu_output6 );

            gpu_outputs.push_back( gpu_output6 );
            index++;
        }

        // For each adpater print information;
        //  Adapter name and RAM 
        //  Display output devices
        //   Colour formats
        //    Resolutions 
        for( auto & output : gpu_outputs )
        {        
            DXGI_OUTPUT_DESC1 output_description {};

            output->GetDesc1( & output_description );

            if( debug_output ) 
            {
                wstring text { L"\n\nOutput device name: " };

                text += output_description.DeviceName;
                text += output_description.AttachedToDesktop ? L"\n is " : L"\n is not ";
                text += L"attached to destop";
                text += L"\n bits per colour: ";
                text += to_wstring( output_description.BitsPerColor );
                //text += to_wstring( output_description.ColorSpace );
                //RECT DesktopCoordinates;
                //DXGI_MODE_ROTATION Rotation;
                //HMONITOR Monitor;
                //FLOAT RedPrimary[ 2 ];
                //FLOAT GreenPrimary[ 2 ];
                //FLOAT BluePrimary[ 2 ];
                //FLOAT WhitePoint[ 2 ];
                text += L"\n minimum luminance: ";
                text += to_wstring( output_description.MinLuminance );
                text += L" nits ,\n maximum luminance: ";
                text += to_wstring( output_description.MaxLuminance );
                text += text += L" nits ,\n maximum full frame luminance: ";
                text += to_wstring( output_description.MaxFullFrameLuminance );

                print_debug( text.c_str() );
            }

            uint amount {};
            // Include modes that require scaling.
            uint flags = DXGI_ENUM_MODES_SCALING | DXGI_ENUM_MODES_INTERLACED;
            map< uint , uint > supported;

            // Retreive the amount of resolutions for each format.
            // DXGI_FORMATs enum range of 0 to 115
            for( uint index {}; index <= 115 ; index++ )
            {
                output->GetDisplayModeList1( static_cast< DXGI_FORMAT >( index ) , flags , & amount , 0 );

                if( amount > 0 ) supported[ index ] = amount;
            }

            if( debug_output ) print_debug( L" \nSupported colour formats and thier resolutions: " );

            map< uint , vector< DXGI_MODE_DESC1 > > format_descriptions;

            // For each format retreive the resolution description.
            for( const auto & [ key , amount ] : supported )
            {
                vector< DXGI_MODE_DESC1 > mode_descriptions;

                mode_descriptions.resize( amount );

                uint resolutions_amount = amount;

                output->GetDisplayModeList1( static_cast< DXGI_FORMAT >( key ) , flags , &resolutions_amount , mode_descriptions.data() );

                format_descriptions[key] = mode_descriptions;

                if( debug_output )
                {
                    wstring text{ L" \nFormat: " };
                    text += DXGI_formats::format( mode_descriptions.front().Format );
                    print_debug( text.c_str() );
                }

                /*
                for( auto & mode : mode_descriptions )
                {
                    text = L" \nResolution width: ";
                    text += to_wstring( mode.Width );
                    text += L" height: ";
                    text += to_wstring( mode.Height );
                    print_debug( text.c_str() );
                }
                */
            }
            
        }
    }
}

// These resources need to be recreated every time the window size is changed.
void Graphics::create_window_size_dependent_resources( uint width , uint height )
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView * nullViews[] = { nullptr };

    device_context->OMSetRenderTargets( _countof( nullViews ) , nullViews , nullptr );

    render_target_view.Reset();
    depth_stencil_view.Reset();

    render_target.Reset();
    depth_stencil.Reset();

    device_context->Flush();
    device_context->ClearState();

    d2d_target.Reset();
    d2d_context->Flush();

    // If the swap chain already exists, resize it, otherwise create one.
    if( swap_chain )
    {
        result = swap_chain->ResizeBuffers( swap_chain_amount ,
                                            width ,
                                            height ,
                                            swap_chain_format ,
                                            0 ); // swap chain flags

        if( FAILED( result ) ) error_exit( L"Unable to resize swap chain." , result );
        
        if( debug_output ) print_debug( L"\n Swap chain resized." );

        if( result == DXGI_ERROR_DEVICE_REMOVED || result == DXGI_ERROR_DEVICE_RESET )
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            device_lost();

            // Everything is set up now. Do not continue execution of this method. 
            // gpu_device_lost() will re-enter this function and correctly set up the new device.
            return;
        }
    }
    else// if( create_swap_chain( width , height ) ) <- could attempt with other formats
    {
        create_swap_chain( width , height );

        create_target_view();

        // A depth buffer / z-buffer, stores depth information 
        // ensuring polygons properly occlude other polygons.
        create_depth_texture();

        // Create the texture that will serve as the depth surface.
        create_depth_view();
    }
    
}

void Graphics::create_swap_chain( uint width , uint height )
{
    // Set the back buffer amount.
	swap_chain_description.BufferCount = swap_chain_amount;

    // Set the width and height of the back buffer.
    swap_chain_description.Width  = width;
    swap_chain_description.Height = height;
    
    // Set regular 32-bit surface for the back buffer.
	swap_chain_description.Format = swap_chain_format;

    // Set the refresh rate of the back buffer.
	//enumerate display modes -> if( v_sync ) Numerator = monitor refresh rate;
	//swap_chain_description.BufferDesc.RefreshRate.Numerator	  = 60; // 60hz refresh rate
	//swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;

    // Set the scan line ordering and scaling 
	swap_chain_description.Scaling = scaling;

    // Set the usage of the back buffer.
	swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    // Texture multi-sampling amount.
	swap_chain_description.SampleDesc = sampling;

     // Discard the back buffer contents after presenting.
    swap_chain_description.SwapEffect = swap_effect;

    // Set to full screen or windowed mode.
    swap_chain_fullscreen_description.Windowed = true;// false for store apps will fail;

    // Don't set the advanced flags.
    swap_chain_description.Flags = 0;

    //HWND window = application.get_gui().get_window();
    //HWND window = MSWindows::get_window();

    // Create the swap chain using the description
    result = dxgi_factory7->CreateSwapChainForHwnd( d3d_device.Get() ,
                                                    window ,
                                                    & swap_chain_description ,
                                                    & swap_chain_fullscreen_description ,
                                                    nullptr , //A pointer to the IDXGIOutput interface for the output to restrict content to. 
                                                    & swap_chain );

    if( FAILED( result ) ) error_exit( L"Unable to create swap chain." , result );

    /*
    dxgi_factory->CreateSwapChainForCoreWindow( d3d_device.Get() ,
                                                reinterpret_cast< IUnknown * >( window ) ,
                                                & swap_chain_description ,
                                                nullptr ,    // allow on all displays
                                                & swap_chain );

    if( FAILED( result ) ) error_exit( L"Unable to create swap chain." , result );
    */

    // -- Create D2D target --
    
    // Get the backbuffer for this window which is be the final 3D render target.
    //ComPtr< ID3D11Texture2D > back_buffer;
    ComPtr< IDXGISurface > back_buffer;

    result = swap_chain->GetBuffer( 0 , IID_PPV_ARGS( & back_buffer ) );

    if( FAILED( result ) ) error_exit( L"Unable to get swap chain buffer." , result );

    float dpi = static_cast< float >( GetDpiForWindow( window ) );
    
    //float dpi_x {};
    //float dpi_y {};
    //d2d_factory7->GetDesktopDpi( & dpi_x , & dpi_y ); // Depreciated

    if( dpi <= 0 ) error_exit( L"Unable to get window dpi." , result );
    
    // Configure Direct2D render target surface linked to the swapchain. 
    // Surface is directly rendered to the swap chain associated with the window.
    D2D1_RENDER_TARGET_PROPERTIES target_properties {};

    target_properties.type        = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    target_properties.pixelFormat = { swap_chain_format , d2d_alpha_mode };
    target_properties.usage       = D2D1_RENDER_TARGET_USAGE_NONE;
    target_properties.minLevel    = D2D1_FEATURE_LEVEL_DEFAULT;
    target_properties.dpiX        = dpi;
    target_properties.dpiY        = dpi;

    result = d2d_factory7->CreateDxgiSurfaceRenderTarget( back_buffer.Get() ,
                                                          target_properties ,
                                                          d2d_target.ReleaseAndGetAddressOf() );

    if( FAILED( result ) ) error_exit( L"Unable to create d2d render target." , result );

	// This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
	//result = dxgi_factory1->MakeWindowAssociation( application.get_gui().get_window() , DXGI_MWA_NO_ALT_ENTER );
	// DXGI_MWA_NO_ALT_ENTER - Prevent DXGI from responding to an alt-enter sequence. 
	// ensures that DXGI will not interfere with application's handling of window mode changes or Alt+Enter.

    if( debug_output )
    {
        set_name( swap_chain , L"swap_chain" );
        print_debug( L"\n Swap chain target created." );
    }
}

bool Graphics::create_target_view()
// set_render_target_texture( <Texture2D> texture )
{
	// Obtain the backbuffer for this window which will be the final 3D render target.
	result = swap_chain->GetBuffer( 0 , // index
                                    __uuidof( render_target ),
                                    reinterpret_cast< void ** >( render_target.GetAddressOf() ) );

    if( FAILED( result ) ) 
    {
        error_exit( L"Unable to get the swap chain buffer." , result );
        return false;
    }

    // Create the render target view with the back buffer pointer.
	result = d3d_device->CreateRenderTargetView( render_target.Get(), // ID3D11Resource * that represents a render target
                                                 nullptr , // D3D11_RENDER_TARGET_VIEW_DESC *
                                                 & render_target_view );

    // Release texture.
    //render_target.Reset();
    
	if( FAILED( result ) ) 
    {
        error_exit( L"Unable to create render target view." , result );
        return false;
    }

    if( debug_output )
    {
        set_name( render_target_view.Get() , L"Render target view" );
        print_debug( L"\n Render target created." );
    }

    return true;
}

bool Graphics::create_depth_texture()
{
    // TODO: get initial size from window creation and
    // WM_SIZE

    // Set up the description of the depth buffer.
    depth_texture_description.Width              = swap_chain_size.width();
    depth_texture_description.Height             = swap_chain_size.height();

	depth_texture_description.MipLevels          = 1;
	depth_texture_description.ArraySize          = 1;
	depth_texture_description.Format             = depth_texture_format;
	depth_texture_description.SampleDesc.Count   = 1;
	depth_texture_description.SampleDesc.Quality = 0;
	depth_texture_description.Usage              = D3D11_USAGE_DEFAULT;
	depth_texture_description.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	depth_texture_description.CPUAccessFlags     = 0;
	depth_texture_description.MiscFlags          = 0;

    // Create the texture for the depth buffer using the filled out description.
	result = d3d_device->CreateTexture2D( & depth_texture_description ,
                                          nullptr , // initial data
                                          &depth_stencil );

	if( FAILED( result ) ) 
    {
        error_exit( L"Unable to create depth texture." , result );
        return false;
    }

    if( debug_output )
    {
        set_name( depth_stencil.Get() , L"depth_stencil");
        print_debug( L"\n Depth texture created." );
    }

    return true;
}

bool Graphics::create_depth_state()
{
    //CD3D11_DEPTH_STENCIL_DESC;
    // Set up the description of the stencil state.
    depth_stencil_description.DepthEnable = true;
    depth_stencil_description.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_description.DepthFunc = D3D11_COMPARISON_LESS;

    depth_stencil_description.StencilEnable = false;
    depth_stencil_description.StencilReadMask = 0xFF;
    depth_stencil_description.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing.
    depth_stencil_description.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing.
    depth_stencil_description.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depth_stencil_description.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Create the depth stencil state.
    result = d3d_device->CreateDepthStencilState( & depth_stencil_description , 
                                                  & depth_stencil_state );

    if( FAILED( result ) ) 
    {
        error_exit( L"Unable to create depth stencil state." , result );
        return false;
    }

    if( debug_output )
    {
        set_name( depth_stencil_state , L"depth_stencil_state" );
        print_debug( L"\n Depth state created." );
    }

    return true;
}

void Graphics::set_depth_state( D3D11_DEPTH_STENCIL_DESC const & description,
                                ID3D11DepthStencilState * stencil_state )
{
    // Set the depth stencil state.
    device_context->OMSetDepthStencilState( stencil_state ,
                                            1 ); // stencil reference

    //if( debug_output ) print_debug( L"\n Depth state bound to Output merger." );
}

bool Graphics::create_depth_view() 
// ( ID3D11Texture2D * texture , format )
{
    // Set up the description of the stencil view.
	depth_stencil_view_description.Format = depth_texture_description.Format;
	
    depth_stencil_view_description.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; 
    // D3D11_DSV_DIMENSION_TEXTURE2DMS The resource will be accessed as a 2D texture with multisampling.	
	
    depth_stencil_view_description.Texture2D.MipSlice	= 0;

    // Create the resource that will serve as the depth surface.
	result = d3d_device->CreateDepthStencilView( depth_stencil.Get() ,
                                                 & depth_stencil_view_description ,
                                                 & depth_stencil_view );

	if( FAILED( result ) )
    {
        error_exit( L"Unable to create depth stencil view." , result );
        return false;
    }

    if( debug_output )
    {
        set_name( depth_stencil_view , L"depth_stencil_view" );
        print_debug( L"\n Depth texture view created." );
    }

    return true;
}

void Graphics::set_targets( ID3D11RenderTargetView * const * render_target_view ,
                            ID3D11DepthStencilView * depth_stencil_view )
{
    // Bind the render target view and depth texture view to the Output Merger pipeline.
    device_context->OMSetRenderTargets( 1 , // number of render targets to bind 
                                        render_target_view , // array of ID3D11RenderTargetView pointer , RTV[8]
                                        depth_stencil_view ); // ID3D11DepthStencilView pointer

    //if( debug_output ) print_debug( L"\n Render target and depth texture bound to Output Merger." );
}

bool Graphics::create_rasteriser( D3D11_RASTERIZER_DESC & rasteriser_description ,
                                  ID3D11RasterizerState ** rasteriser_state )
{
    // Fill in description with some Microsoft pre-defined values
    rasteriser_description = CD3D11_RASTERIZER_DESC( D3D11_DEFAULT );

    // Setup the raster description which will determine 
    //  how and what polygons will be drawn.
    rasteriser_description.FillMode				 = fill_mode;
    rasteriser_description.CullMode				 = cull_mode;
    rasteriser_description.FrontCounterClockwise = false;
    rasteriser_description.MultisampleEnable	 = is_multisample_enabled;
    rasteriser_description.AntialiasedLineEnable = is_antialiased_line_enabled;
    rasteriser_description.DepthBias             = 0; 
    rasteriser_description.DepthBiasClamp        = 0.0f;
    rasteriser_description.SlopeScaledDepthBias  = 0.0f;
    rasteriser_description.DepthClipEnable       = true;
    rasteriser_description.ScissorEnable         = false;
    rasteriser_description.MultisampleEnable     = true;
    rasteriser_description.AntialiasedLineEnable = true;
    // Only applies if doing line drawing and MultisampleEnable is false. 

    result = d3d_device->CreateRasterizerState( & rasteriser_description ,
                                                rasteriser_state );

    if( FAILED( result ) )
    {
        error_exit( L"Unable to create rasteriser state." , result );
        return false;
    }

    if( debug_output )
    {
        set_name( *rasteriser_state , L"rasteriser_state" );
        print_debug( L"\n Rasteriser state created." );
    }

    return true;
}

void Graphics::set_rasteriser( ID3D11RasterizerState * rasteriser_state )
{
    device_context->RSSetState( rasteriser_state );

    //if( debug_output ) print_debug( L"\n Rasteriser state bound to Rasteriser stage." );
}

void Graphics::set_viewport( D3D11_VIEWPORT & viewport )
{
    viewport.TopLeftX = viewport_top_left_x;
    viewport.TopLeftY = viewport_top_left_y;
    viewport.Width    = static_cast< float >( swap_chain_size.width() );
    viewport.Height   = static_cast< float >( swap_chain_size.height() );
    viewport.MinDepth = viewport_minimum_depth;
    viewport.MaxDepth = viewport_maximum_depth;

    // Bind an array of view ports to the rasterizer stage of the pipeline.
    device_context->RSSetViewports( 1 , // number of viewports to bind
                                    & viewport ); // D3D11_VIEWPORT structures array to bind to device

    //if( debug_output ) print_debug( L"\n Rasteriser viewport bound to Rasteriser stage." );

    // A viewport is a way of translating pixel coordinates to normalized coordinates.
    // pixel coordinates start at 0, 0 in the upper-left corner, and increase one pixel at a time. 
    // Normalized coordinates start at -1, -1 and increase to 1, 1, no matter the size of the back buffer. 
    // The word normalized means that a value is adjusted until it equals 1.
}

bool Graphics::create_input_layout( std::wstring path_of_cso ,
                                    Input_layouts & layout ,
                                    //D3D11_INPUT_ELEMENT_DESC * input_layout_description ,
                                    ID3D11InputLayout ** input_layout )
{
    ID3DBlob * blob {};

    result = D3DReadFileToBlob( path_of_cso.c_str() , &blob );

    if( FAILED( result ) ) error_exit( L"Create input layout; read file to blob error." , result );

    result = d3d_device->CreateInputLayout( layout.get_layout().data() , // input-assembler stage input data types array
                                            static_cast< uint >( layout.get_layout().size() ) , // Total input-data types in array of input-elements
                                            blob->GetBufferPointer() , // compiled shader pointer
                                            blob->GetBufferSize() , // size of compiled shader
                                            input_layout ); // output pointer to created input-layout object

    if( FAILED( result ) ) error_exit( L"Unable to create input layout error." , result );
    // ****  MOVE TO MESH ***** -> need VS shader compiled cso blob

    if( blob ) blob->Release(); blob = nullptr;
    
    if( debug_output )
    {
        set_name( *input_layout , L"input_layout" );
        print_debug( L"\n Input layout created." );
    }

    return true;
}


void Graphics::set_input_layout( ID3D11InputLayout * input_layout )
{
    // Bind an input-layout object to the input-assembler stage
    device_context->IASetInputLayout( input_layout );
    // ** no return value !

    //if( debug_output ) print_debug( L"\n Input layout bound to Input Assembeler stage." );
}

bool Graphics::create_vertex_shader( wstring const & path_of_cso ,
                                     ID3D11VertexShader ** vertex_shader )
{
    ID3DBlob * blob{ nullptr };

    HRESULT result = D3DReadFileToBlob( path_of_cso.c_str() , & blob );

    if( FAILED( result ) )
    {
        error_exit( L"Unable to read vertex shader." , result );
        return false;
    }

    result = d3d_device->CreateVertexShader( blob->GetBufferPointer() ,
                                             blob->GetBufferSize() ,
                                             nullptr ,
                                             vertex_shader );

    if( FAILED( result ) )
    {
        error_exit( L"Unable to create vertex shader." , result );
        return false;
    }

    if( decompile_shaders ) print_decompiled_shader( blob , "Vertex shader" );

    if( blob ) blob->Release(); blob = nullptr;

    if( debug_output )
    {
        set_name( *vertex_shader , L"vertex_shader" );
        print_debug( L"\n Vertex shader created." );
    }

    return true;
}

void Graphics::set_vertex_shader( ID3D11VertexShader * vertex_shader )
{
    device_context->VSSetShader( vertex_shader , nullptr , 0 );
    // ** no return value !
    // how to check shader is bound to pipeline?

    //if( debug_output ) print_debug( L"\n Vertex shader bound to Vertex Shader stage." );
}

ID3D11VertexShader * Graphics::get_vertex_shader() const
{
    return vertex_shader_.Get();
}

bool Graphics::create_pixel_shader( const std::wstring & path_of_cso ,
                                    ID3D11PixelShader ** pixel_shader )
// compiled shader object  
{
    ID3DBlob * blob { nullptr };

    // Read shader compiled at build.
    result = D3DReadFileToBlob( path_of_cso.c_str() , & blob);
    
    if( FAILED( result ) )
    {
        error_exit( L"Unavble to read pixel shader." , result );
        return false;
    }

    // Read data from blob to pixel shader.
    result = d3d_device->CreatePixelShader( blob->GetBufferPointer() ,
                                            blob->GetBufferSize() ,
                                            nullptr ,
                                            pixel_shader );

    if( FAILED( result ) )
    {
        error_exit( L"Unable to create pixel shader." , result );
        return false;
    }

    if( decompile_shaders ) print_decompiled_shader( blob , "Pixel shader" );

    if( blob ) blob->Release(); blob = nullptr;

    if( debug_output )
    {
        set_name( *pixel_shader , L"pixel_shader" );
        print_debug( L"\n Pixel shader created." );
    }

    return true;
}

void Graphics::set_pixel_shader( ID3D11PixelShader * pixel_shader )
{
    device_context->PSSetShader( pixel_shader ,
                                 nullptr ,
                                 0 );
    // ** no return value !
    // how to check shader is bound to pipeline?

    //if( debug_output ) print_debug( L"\n Pixel shader bound to Pixel Shader stage." );
}

ID3D11PixelShader * Graphics::get_pixel_shader() const
{
    return pixel_shader_.Get();
}

void Graphics::print_decompiled_shader( ID3DBlob * cso ,
                                        std::string const & comments )
{
    uint flags { };//D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS };

    //std::ifstream file( path_of_cso , std::ios::binary | std::ios::in );

    //file.rdstate();
    //file.ignore( std::numeric_limits<std::streamsize>::max );
    //std::streamsize length = file.gcount();
    //file.clear(); //  Since ignore will have set eof.
    //file.seekg( 0 , std::ios_base::beg );
    //file.read( )

    //IStream * file;
    //file.open(path_of_cso);

    ID3DBlob * output;

    result = D3DDisassemble( cso->GetBufferPointer() ,
                             cso->GetBufferSize() ,
                             flags,
                             comments.c_str() ,
                             & output);

    print_debug( reinterpret_cast< char * >( output->GetBufferPointer() ) );
}

bool Graphics::create_samplers( D3D11_SAMPLER_DESC & sampler_description ,
                                ID3D11SamplerState ** sampler_state )
{
    // Fill in description with some Microsoft pre-defined values
    //sampler_description = CD3D11_SAMPLER_DESC( D3D11_DEFAULT );
    
    // Configure how textures apply to polygons and 
    // what happens when the texture is smaller or
    // larger than the surface
    sampler_description.Filter         = filter;
    sampler_description.MaxAnisotropy  = maximum_anisotropy;
    sampler_description.AddressU       = address_mode;
    sampler_description.AddressV       = address_mode;
    sampler_description.AddressW       = address_mode;
    sampler_description.BorderColor[0] = border_colour[0];
    sampler_description.BorderColor[1] = border_colour[1];
    sampler_description.BorderColor[2] = border_colour[2];
    sampler_description.BorderColor[3] = border_colour[3];
    sampler_description.MipLODBias     = 0;
    sampler_description.ComparisonFunc = comparison;
    sampler_description.MinLOD         = 0;//FLT_MIN;
    sampler_description.MaxLOD         = D3D11_FLOAT32_MAX;

    result = d3d_device->CreateSamplerState( & sampler_description ,
                                             sampler_state );

    if( FAILED( result ) )
    {
        error_exit( L"Unable to create sampler state." , result );
        return false;
    }
    // move to Texture

    if( debug_output )
    {
        set_name( *sampler_state , L"Sampler state" );
        print_debug( L"\n Sampler state created." );
    }

    return true;
}

void Graphics::set_samplers( ID3D11SamplerState ** sampler_state )
{
    device_context->PSSetSamplers( 0u , // start sampler/s slot // enum class { SAMPLER_SLOT0 , ... }
                                   1u , // amount of samplers
                                   sampler_state ); // sampler state

    /* If building an array of Direct3D interface pointers ,
       you should build one as a local variable as there's no direct way to convert an array of ComPtr<T> to an array of T*.

       ID3D11SamplerState* samplers[] = { sampler1.Get(), sampler2.Get() };
       context->PSSetSamplers( 0 , _countof( samplers ) , samplers ); */

    //if( debug_output ) print_debug( L"\n Sampler state bound to Pixel Shader stage." );
}

bool Graphics::create_blend( D3D11_BLEND_DESC & blend_description ,
                             ID3D11BlendState ** blend_state )
{
    //blend_description = CD3D11_BLEND_DESC( D3D11_DEFAULT );

    // Conifgure what happens with alpha values
    blend_descripton.AlphaToCoverageEnable	= false;
    blend_descripton.IndependentBlendEnable	= false; //FALSE, only the RenderTarget[0] members are used; RenderTarget[1..7] are ignored. 

    blend_descripton.RenderTarget[ 0 ].BlendEnable           = is_blend_enabled;
    blend_descripton.RenderTarget[ 0 ].SrcBlend              = D3D11_BLEND_SRC_ALPHA; // the blend factor is (As, As, As, As) , that is alpha data (A) from a pixel shader
    blend_descripton.RenderTarget[ 0 ].DestBlend             = D3D11_BLEND_DEST_ALPHA; // the blend factor is (Ad, Ad, Ad, Ad), that is alpha data from a render target.
    blend_descripton.RenderTarget[ 0 ].BlendOp               = D3D11_BLEND_OP_ADD; //Add source 1 and source 2.
    blend_descripton.RenderTarget[ 0 ].SrcBlendAlpha         = D3D11_BLEND_ZERO; //The blend factor is (0, 0, 0, 0)
    blend_descripton.RenderTarget[ 0 ].DestBlendAlpha        = D3D11_BLEND_ZERO;
    blend_descripton.RenderTarget[ 0 ].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blend_descripton.RenderTarget[ 0 ].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    // Configure up to eight Render Targets

    result = d3d_device->CreateBlendState( & blend_descripton , 
                                           blend_state );

    if( FAILED( result ) )
    {
        error_exit( L"Unable to create blend state." , result );
        return false;
    }

    set_name( *blend_state , L"Blend state" );
    print_debug( L"\n Blend state created." );

    return true;
}

void Graphics::set_blend( ID3D11BlendState * blend_state ,
                          float * blend_factor ,
                          uint sample_mask )
{
    device_context->OMSetBlendState( blend_state ,
                                     blend_factor , 
                                     sample_mask );

    //if( debug_output ) print_debug( L"\n Blend state bound to Output Merger stage." );
}


// Allocate all memory resources that change on a window SizeChanged event.
void Graphics::window_size_change( uint width , uint height )
{
    create_window_size_dependent_resources( width , height );
}

void Graphics::clear()
{
    if( annotation ) annotation->BeginEvent( L"Clear default" );

    if( render_target_view )
    {
	    // Clear the views.
	    device_context->ClearRenderTargetView( render_target_view.Get() , 
                                               clear_colour );  // 4-component colour array color to fill // dx9 D3DCOLOR_RGBA() );

        clear_common();
    }
}

void Graphics::clear( XMFLOAT4 const & in_colour )
{
    if( annotation ) annotation->BeginEvent( L"Clear custom" );

    if( render_target_view )
    {
	    // Clear the views.
	    float clear_colour[ 4 ] {};

	    clear_colour[ 0 ] = in_colour.x;
	    clear_colour[ 1 ] = in_colour.y;
	    clear_colour[ 2 ] = in_colour.z;
	    clear_colour[ 3 ] = in_colour.w;

	    device_context->ClearRenderTargetView( render_target_view.Get() ,
                                               clear_colour );  // 4-component colour array color to fill // dx9 D3DCOLOR_RGBA() );

        clear_common();
    }
}

void Graphics::clear_common()
{
    if( depth_stencil_view )
    {
        device_context->ClearDepthStencilView( depth_stencil_view.Get() ,
                                               D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL ,
                                               1.0f , // depth
                                               0 ); // stencil
    }
    
    if( annotation ) annotation->EndEvent();
}

void Graphics::frame_begin()
{
    if( annotation ) annotation->BeginEvent( L"Frame begin" );

    clear();
    
    set_input_layout( input_layout_.Get() );
    
    // Bind the render target view and depth texture view 
    // to the Output Merger pipeline.
    set_targets( render_target_view.GetAddressOf() , depth_stencil_view.Get() );
    
    set_vertex_shader( vertex_shader_.Get() );
    set_pixel_shader( pixel_shader_.Get() );
    
    // Bind the sampler to the Pixel Shader.
    set_samplers( sampler_state.GetAddressOf() );

    // Bind state/settings to Rasteriser stage of the pipeline.
    set_rasteriser( rasteriser_state.Get() );

    // Bind a state / rules to the ouput merger pipeline
    //set_depth_state( depth_stencil_description , depth_stencil_state.Get() );

    // Bind blend state to the Ouput Merger
    //set_blend( blend_state.Get() , blend_factor , sample_mask );

    // Setup viewport to translate pixel coordinates to normalised coordinates.
    set_viewport( viewport );

    //device_context->GSSetShader( nullptr , nullptr , 0 );

    //d2d_context->BeginDraw();

    if( annotation ) annotation->EndEvent();
}

void Graphics::frame_end()
{ 
    if( annotation ) annotation->BeginEvent( L"Frame end" );

    //result = d2d_context->EndDraw();

    if( FAILED( result ) ) error_exit( L"Error ending draw." , result );

    if( swap_chain )
    {
        //if(m_vsync_enabled)

        // Back buffer swap rate at monitor refresh rate.
	    result = swap_chain->Present( 1u, //block until V.Sync, application sleep until next V.Sync. 
                                      0u ); // flags
        //else present( 0,0) // swap back buffer as fast as possible.

        // If the device was reset we must completely re-initialise the renderer.
        if( result == DXGI_ERROR_DEVICE_REMOVED || result == DXGI_ERROR_DEVICE_RESET )
        {
            device_lost();
        }
        else
        {
            if( FAILED( result ) ) error_exit( L"Present() error; video device removed or reset" , result );

            if( not dxgi_factory2->IsCurrent() )
            {
                // Informs an application of the possible need to re-enumerate adapters.
                create_dxgi_factory();
            }
        }

        if( render_target_view )
        {
            device_context1->DiscardView( render_target_view.Get() );
        }

        if( depth_stencil_view )
        {
            // Discard the contents of the depth stencil.
            device_context1->DiscardView( depth_stencil_view.Get() );
        }

        
    }

    if( annotation ) annotation->EndEvent();
}

void Graphics::device_lost()
{
    // ComPtr::Reset = Release all pointer references to the associated interface

    sampler_state.Reset();

    //vertex_buffer.Reset();
    input_layout_.Reset();

    pixel_shader_.Reset();
    vertex_shader_.Reset();

    //constant_buffer_projection.Reset();
    //constant_buffer_view.Reset();	
    //constant_buffer_world.Reset();

    depth_stencil_view.Reset();
    depth_stencil.Reset();

    render_target_view.Reset();
    render_target.Reset();

    swap_chain.Reset();

#ifdef _DEBUG

    //debug.Reset();

#endif

    device_context.Reset();
    d3d_device.Reset();

    create_device_resources();
}

ID3D11Device * Graphics::device()
{
    return d3d_device.Get();
}

/*
Size Graphics::swap_chain_size() const
{
    D3D11_VIEWPORT viewport {};
    uint           viewport_amount {};

    device_context->RSGetViewports( &viewport_amount , &viewport );

    return { static_cast< int >( viewport.Width ), static_cast< int >( viewport.Height ) };
}
*/