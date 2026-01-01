#pragma once

#include <vector>
#include <string>

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#include <wincodec.h>

#include "Source code/Hpp/Custom types.hpp"
#include "Source code/Hpp/Graphics/WIC/WICFactory.hpp"

#include "Source code/Hpp/Graphics/Direct2D/Drawable2D.hpp"

class WIC : public WICFactory , public Drawable2D
{
    private:

        HRESULT	result { E_FAIL };

        ComPtr< IWICBitmapDecoder >       decoder          {};
        ComPtr< IWICBitmapFrameDecode >   frame_decode     {};
        ComPtr< IWICFormatConverter >     format_converter {};
        ComPtr< IWICComponentInfo >       component_info   {};
        ComPtr< IWICPixelFormatInfo >     format_info      {};
        ComPtr< IWICMetadataQueryReader > meta_data_reader {};
        PROPVARIANT                       properties {};

        GUID               image_format {};
        WICPixelFormatGUID source_format {};
        //DXGI_FORMAT      GI_destination_format { DXGI_FORMAT_R16G16B16A16_FLOAT };
        DXGI_FORMAT        GI_destination_format { DXGI_FORMAT_B8G8R8A8_UNORM };
        BOOL               can_convert { false };
        uint               supported   { false };

        //GUID source_format_guid {};
        //WICPixelFormatGUID WIC_destination_format = GUID_WICPixelFormat64bppRGBA;
        //WICPixelFormatGUID WIC_destination_format = GUID_WICPixelFormat32bppBGRA;
        WICPixelFormatGUID WIC_destination_format = GUID_WICPixelFormat32bppPBGRA;

        wchar_t	format_name[ 128 ]{};
        uint	chars_read{};

        uint bytes_per_pixel = 4;//bits_per_pixel_ / 8;
        uint bits_per_pixel {};
        uint row_byte_pitch {};
        uint size_bytes     {};
        uint channel_amount {};
        
        uchar gif_background_index {};
        ComPtr< IWICPalette > pallete {};
        WICColor pallete_colours[ 256 ];
        uint colours_copied {};
        ulong background_colour_temp {};
        D2D1_COLOR_F background_colour {};
        enum disposal_methods
        {
            dm_undefined  = 0 ,
            dm_none       = 1 ,
            dm_background = 2 ,
            dm_previous   = 3
        };
        uint disposal_method {};
        
        void load_image();

        void load_tiff_frames();
        
        void load_gif_frames();
        void get_background_colour();

    protected:

        using frame = ComPtr< ID2D1Bitmap >;

        uint width{};
        uint height{};
        
        uint frame_amount{};
        
        std::vector< frame >  frames       {};
        std::vector< double > frame_delays {};

	public:

		void load( std::wstring const & in_filename );
};

/*
struct WIC_to_DXGI
{
    GUID		wic;
    DXGI_FORMAT	format;
};

static WIC_to_DXGI WICFormats[]
{
    { GUID_WICPixelFormat32bppRGBA,	DXGI_FORMAT_R8G8B8A8_UNORM }
};
*/