#pragma once

#include <windows.h>

#include <wrl\client.h>
using Microsoft::WRL::ComPtr;

#include <dxgi1_6.h>
#include <d3d11_4.h>
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <dcomp.h>

#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dcomp")

//struct monitor {};
//struct page {};

#include "Aliases.h"
#include "Graphics\Direct2D\Drawable.h"
#include "Graphics\Direct2D\Factory.h"

class Direct2D : public Drawable2D , public Factory2D
{
    private:

        HRESULT                 result { E_FAIL };

        HWND                    window {};

        // -- 3D Device / adapter --
        ComPtr< ID3D11Device >    device_3d  {};
        ComPtr< IDXGIDevice >     device_gi  {};
        ComPtr< IDXGIFactory2 >   factory_gi {};
        ComPtr< IDXGISwapChain1 > swap_chain {};

        // -- 2D Device / adapter --
        ComPtr< ID2D1Device1 >  device_2d  {};
        ComPtr< IDXGISurface2 > surface    {};
        ComPtr< ID2D1Bitmap1 >  bitmap     {};
        ComPtr< IDCompositionDevice > device_composition {};
        ComPtr< IDCompositionTarget > target_composition {};
        ComPtr< IDCompositionVisual > visual_composition {};
        
        D2D1_ALPHA_MODE         alpha_mode { D2D1_ALPHA_MODE_IGNORE };

        D2D1_PIXEL_FORMAT       target_format { DXGI_FORMAT_B8G8R8A8_UNORM ,  
                                                D2D1_ALPHA_MODE_PREMULTIPLIED };
        
        PAINTSTRUCT  paint {};
        D2D1_COLOR_F colour_clear { 0.5f , 0.5f , 0.5f , 1.0f };
        
        //float       page_dips    { 0.0f };
        //D2D1_SIZE_F page_dpi     { 0.0f , 0.0f };
       
        void reset();
        void create_swap_chain();
       
    public:

        void initialise( HWND in_window );
        void draw_begin();
        void draw_end();
            
        D2D_SIZE_F size_dips();
        D2D_SIZE_U screen_size();
        D2D_SIZE_F dpi();

        void window_size_change( uint width , uint height );
};

//https://learn.microsoft.com/en-us/windows/win32/direct2d/devices-and-device-contexts

 //ID2D1SolidColorBrush  & get_brush_solid( D2D1::ColorF in_colour = D2D1::ColorF::Yellow );
            /*
            ID2D1StrokeStyle      & get_stroke_style( stroke_cap_style  in_cap_start   = stroke_cap_style::flat  ,
                                                 stroke_cap_style  in_cap_dash    = stroke_cap_style::flat  ,
                                                 stroke_cap_style  in_cap_end     = stroke_cap_style::flat  ,
                                                 stroke_line_join  in_line_join   = stroke_line_join::round ,
                                                 float             in_miter_limit = 1.0f                    ,
                                                 stroke_dash_style in_dash_style  = stroke_dash_style::dash ,
                                                 float             in_dash_offset = 1.0f                    );
 /*
         class sheet
         {
            enum class request_type { window_ptr , size };

            using window_ptr = ID2D1HwndRenderTarget *;
            using size    = D2D1_SIZE_F;

            window_ptr _sheet {};
            size    _size  {};

            public:

            sheet( window_ptr const in_sheet = {} , const size in_size = {} )
            : _sheet( in_sheet ) , _size( in_size )
            {}

            size    size()    const { return _size; }
            window_ptr window_ptr() const { return _sheet; }
         };
         */

         //vector< sheet > sheets {};