#pragma once

#include <string>
#include <array>
#include <vector>

#include <d3d11_4.h>
#pragma comment( lib , "d3d11.lib" )

#pragma comment( lib , "DXGI.lib" )

//#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
//#else
//#include <dxgi1_5.h>
//#endif
#include <dxgidebug.h>

#include <d3dcompiler.h>
#pragma comment( lib , "d3dcompiler.lib" )

#include <d2d1_3.h>
#pragma comment( lib , "d2d1.lib" )

#include <DirectXMath.h> // XMFLOAT4
using DirectX::XMFLOAT4;

#include <wrl/client.h> // ComPtr
using Microsoft::WRL::ComPtr;

#include <wincodec.h>

#include "Custom types.hpp"
#include "Input layouts.hpp"

#include "Drawable.hpp"

class Application;

class Graphics : public Drawable
{
    private:

        Application & application;
        HWND window {};

        HRESULT                         result { E_FAIL };
        
        // -- 2D Device / adapter --
        ComPtr< ID2D1Factory7 >          d2d_factory7 {};
        ComPtr< ID2D1Device6 >           d2d_device6  {};
        ComPtr< ID2D1DeviceContext >     d2d_context  {};
        ComPtr< ID2D1RenderTarget >      d2d_target   {};
        D2D1_ALPHA_MODE                  d2d_alpha_mode { D2D1_ALPHA_MODE_IGNORE };

        // -- Windows imaging component --
        ComPtr< IWICImagingFactory >     wic_factory      {};
        

        // -- 3D Device / adapter --
        ComPtr< ID3D11Device >           d3d_device {};
        //ComPtr< ID3D11Device5 >         d3d_device5;
        uint                             device_flags { D3D11_CREATE_DEVICE_BGRA_SUPPORT };
        D3D_FEATURE_LEVEL                feature_level {};
        static const inline D3D_FEATURE_LEVEL feature_levels[]
        {
            D3D_FEATURE_LEVEL_11_1,
        }; // first compatible level; set from CreateDevice

        ComPtr< ID3D11DeviceContext >    device_context  {};
        ComPtr< ID3D11DeviceContext1 >   device_context1 {};
        //std::vector< IDXGIAdapter * >   adapters;
        
        // -- Debugging --
        ComPtr< ID3D11Debug >               d3d_debug  {}; 
        ComPtr< IDXGIDebug1 >               dxgi_debug {}; 
        ComPtr< ID3DUserDefinedAnnotation > annotation {};
        ComPtr< ID3D11InfoQueue >           info_queue {};
        bool                                debug_output { false };
        
        // -- Swap chain --
        ComPtr< IDXGISwapChain1 >       swap_chain{};
        //ComPtr< IDXGISwapChain3 >       swap_chain3;
        DXGI_SWAP_CHAIN_DESC1		    swap_chain_description {};
        DXGI_SWAP_CHAIN_FULLSCREEN_DESC swap_chain_fullscreen_description {};
        bool                            is_windowed       { true };
        Size                            swap_chain_size   {};
        uint				            swap_chain_amount { 2 }; 
        //DXGI_FORMAT                     swap_chain_format { DXGI_FORMAT_R16G16B16A16_FLOAT };
        DXGI_FORMAT                     swap_chain_format { DXGI_FORMAT_B8G8R8A8_UNORM };
        DXGI_SCALING                    scaling           { DXGI_SCALING_NONE };
        DXGI_SWAP_EFFECT                swap_effect       { DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL }; // all apps must use this SwapEffect };
        DXGI_SAMPLE_DESC                sampling          { 1,0 };
        uint                            swap_chain_flags  { DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING };
        
        // -- Graphics interface --
        ComPtr< IDXGIDevice1 >          dxgi_device   {};
        ComPtr< IDXGIAdapter1 >         dxgi_adapter  {};
        ComPtr< IDXGIFactory2 >         dxgi_factory2 {};
        ComPtr< IDXGIFactory7 >         dxgi_factory7 {};
        uint                            dxgi_flags    {};

        DXGI_ADAPTER_DESC3              adpater_description {};// GetDesc3()
        // DXGI_OUTPUT_DESC1
        // DXGI_GPU_PREFERENCE = DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE;

        // -- Render targets --
        
        ComPtr< ID3D11Texture2D >		 render_target{};
        ComPtr< ID3D11RenderTargetView > render_target_view{};
        float                            clear_colour[ 4 ] { 0.2f, 0.2f, 0.2f, 1.0f };
        //D3D11_RENDER_TARGET_VIEW_DESC view_description {};

        // -- Depth and stenciling --
        D3D11_TEXTURE2D_DESC             depth_texture_description {};
        DXGI_FORMAT                      depth_texture_format { DXGI_FORMAT_D32_FLOAT };//{ DXGI_FORMAT_D24_UNORM_S8_UINT };
        
        D3D11_DEPTH_STENCIL_DESC         depth_stencil_description {};
        D3D11_DEPTH_STENCIL_VIEW_DESC    depth_stencil_view_description {};

        ComPtr< ID3D11Texture2D >         depth_stencil{};
        ComPtr< ID3D11DepthStencilState > depth_stencil_state{};
        ComPtr< ID3D11DepthStencilView >  depth_stencil_view{};

        // -- Rasteriser --
        ComPtr< ID3D11RasterizerState >   rasteriser_state{};
        D3D11_RASTERIZER_DESC             rasteriser_description {};
        D3D11_FILL_MODE                   fill_mode { D3D11_FILL_SOLID };
        //D3D11_FILL_MODE                  fill_mode { D3D11_FILL_WIREFRAME };
        D3D11_CULL_MODE                   cull_mode { D3D11_CULL_NONE };
        //D3D11_CULL_MODE                  cull_mode { D3D11_CULL_BACK };
        bool                              is_multisample_enabled { false };
        bool                              is_antialiased_line_enabled { false };
        // Only applies if doing line drawing and MultisampleEnable is FALSE. 

        // -- Viewport --
        D3D11_VIEWPORT viewport {};

        float viewport_top_left_x    = 0.0f;
        float viewport_top_left_y    = 0.0f;
        //float viewport_width         = static_cast< float >( swap_chain_size.width() );
        //float viewport_height        = static_cast< float >( swap_chain_size.height() );
        float viewport_minimum_depth = 0.0f; // Range between 0..1;
        float viewport_maximum_depth = 1.0f; // Range between 0..1;

        // -- Shaders --
        Input_layouts                      input_layouts;
        ComPtr< ID3D11InputLayout >        input_layout_{};

        ComPtr< ID3D11VertexShader >       vertex_shader_{};
        ComPtr< ID3D11PixelShader >        pixel_shader_{};
        bool                               decompile_shaders { false };

        // -- Sampling --
        ComPtr< ID3D11SamplerState >       sampler_state{};
        D3D11_SAMPLER_DESC                 sampler_description {};
        D3D11_FILTER                       filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; 
        //_ANISOTROPIC;//_MIN_MAG_MIP_POINT;
        uint                               maximum_anisotropy { 0 };
        //D3D11_TEXTURE_ADDRESS_MODE         address_mode { D3D11_TEXTURE_ADDRESS_CLAMP };
        D3D11_TEXTURE_ADDRESS_MODE         address_mode { D3D11_TEXTURE_ADDRESS_WRAP };
        float                              border_colour[ 4 ] { 1.0f, 1.0f, 0.0f, 1.0f };
        D3D11_COMPARISON_FUNC              comparison { D3D11_COMPARISON_NEVER };
        
        // -- Blending --       
        D3D11_BLEND_DESC                   blend_descripton {};
        ComPtr< ID3D11BlendState >         blend_state{};

        bool                               is_blend_enabled  { true };
        float                              blend_factor[ 4 ] { 1.0f , 1.0f , 1.0f , 1.0f };
        uint                               sample_mask       = 0xffffffff;

    protected:

        //Size swap_chain_size{};
        //friend class MSWindows;

    public:
    
        Graphics( Application & in_application );
        ~Graphics();

        bool initialise( HWND window );

        void window_size_change( uint width , uint height );

        //void client_size( Size const & size);
        //Size swap_chain_size() const;

        ID3D11Device * device();

        void clear();
        void clear( XMFLOAT4 const & in_colour );

        void frame_begin();
        void frame_end();

    private:

        void create_dxgi_factory();
        void create_hardware_device();// IDXGIAdapter1 ** adapter );

        void enumerate_hardware_devices();

        void configure_debuging();
        
        bool create_device_resources();
        void create_window_size_dependent_resources( uint width , uint height );
        
        void create_swap_chain( uint width , uint height );
        bool create_target_view();
        
        bool create_depth_texture();
        bool create_depth_state();
        void set_depth_state( D3D11_DEPTH_STENCIL_DESC const & description ,
                              ID3D11DepthStencilState * stencil_state );
        bool create_depth_view();

        void set_targets( ID3D11RenderTargetView * const * render_target_view ,
                          ID3D11DepthStencilView * depth_stencil_view );

        bool create_rasteriser( D3D11_RASTERIZER_DESC & rasteriser_description ,
                                ID3D11RasterizerState ** rasteriser_state );
        void set_rasteriser( ID3D11RasterizerState * rasteriser_state );

        void set_viewport( D3D11_VIEWPORT & viewport );

        bool create_pixel_shader( std::wstring const & path_of_cso , // compiled shader object
                                  ID3D11PixelShader ** pixel_shader );
        void set_pixel_shader( ID3D11PixelShader * pixel_shader );

        bool create_vertex_shader( std::wstring const & path_of_cso , // compiled shader object
                                   ID3D11VertexShader ** vertex_shader ); 
        void set_vertex_shader( ID3D11VertexShader * vertex_shader );

        void print_decompiled_shader( ID3DBlob * cso , std::string const & comments = {} );

        bool create_input_layout( std::wstring path_of_cso ,
                                  Input_layouts & layout, 
                                  ID3D11InputLayout ** input_layout );
        void set_input_layout( ID3D11InputLayout * input_layout );

        ID3D11PixelShader * get_pixel_shader() const;
        ID3D11VertexShader * get_vertex_shader() const;

        bool create_samplers( D3D11_SAMPLER_DESC & sampler_description ,
                             ID3D11SamplerState ** sampler_state );

        void set_samplers( ID3D11SamplerState ** sampler_state );

        bool create_blend( D3D11_BLEND_DESC & blend_description ,
                           ID3D11BlendState ** blend_state );

        void set_blend( ID3D11BlendState * blend_state ,
                        float * blend_factor ,
                        uint sample_mask );

        void device_lost();

        void clear_common();       
};

//enum class API { DirectX_11 , DirectX_12 , OpenGL , Vulkan };
// default to DirectX 11 API
//Graphics( API in_api = API::DirectX_11 );