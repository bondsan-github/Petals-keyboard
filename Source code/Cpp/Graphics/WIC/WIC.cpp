#include "Source code/Hpp/Graphics/WIC/WIC.hpp"

#include <d3d11_1.h>

//#include "Graphics\Graphics.hpp"

#include "Source code/Hpp/Output/Logging.hpp"

// image_formats
// struct { string name , channel count , DXGI format , WIC_Guid }

void WIC::load( std::wstring const & filename )
{
    wic_factory->CreateDecoderFromFilename( filename.data() , // Image to be decoded
                                            nullptr , // Do not prefer a particular vendor
                                            GENERIC_READ , // Desired read access to the file
                                            WICDecodeMetadataCacheOnDemand , // Cache metadata when needed // WICDecodeMetadataCacheOnLoad
                                            & decoder ) >> result_check; // Pointer to the decoder  

    decoder->GetContainerFormat( & image_format );
    decoder->GetFrameCount( & frame_amount );
    decoder->GetFrame( 0 , &frame_decode );

    if( image_format == GUID_ContainerFormatGif )
    {
        if( frame_amount > 1 ) load_gif_frames();
        else load_image();
        
        get_background_colour();

    }
    else if( image_format == GUID_ContainerFormatTiff )
    {
        if( frame_amount > 1 ) load_tiff_frames();
        else load_image();
    }
    else load_image();
    
    frame_decode->GetSize( & width , & height );

    //device3d->CheckFormatSupport( GI_destination_format ,
    //                                       &is_supported );
    //if( supported & D3D11_FORMAT_SUPPORT_TEXTURE2D );
	
	frame_decode->GetPixelFormat( & source_format );

    wic_factory->CreateComponentInfo( source_format , &component_info );

    component_info.As( & format_info );

    format_info->GetFormatGUID( & source_format );
    format_info->GetBitsPerPixel( & bits_per_pixel );
    format_info->GetChannelCount( & channel_amount );
    format_info->GetFriendlyName( 128 , format_name , & chars_read );

	/* format_converter->CanConvert( source_format ,
                                  WIC_destination_format ,
                                  & can_convert );

    //if( can_convert ) else ""    */

    //frame_amount -= 1;
}

void WIC::load_image()
{
    frames.resize( frame_amount );
    // Format convert to 32bppPBGRA which D2D expects
    wic_factory->CreateFormatConverter( &format_converter ) >> result_check;

    format_converter->Initialize( frame_decode.Get() ,
                                  WIC_destination_format ,
                                  WICBitmapDitherTypeNone , //WICBitmapDitherTypeErrorDiffusion ,
                                  nullptr , // palete
                                  0.0f , // alpha threshold percent
                                  WICBitmapPaletteTypeMedianCut ) >> result_check; //WICBitmapPaletteTypeCustom );

    context_2d->CreateBitmapFromWicBitmap( format_converter.Get() ,
                                           frames.at( 0 ).ReleaseAndGetAddressOf() ) >> result_check;
}

void WIC::load_gif_frames()
{
    frames.resize( frame_amount );

    frame_delays.resize( frame_amount );

    PropVariantInit( &properties );

    //decoder->GetFrame( 0 , &frame_decode );

    // get_meta_data()
    frame_decode->GetMetadataQueryReader( &meta_data_reader );

    for( uint index{} ; index < frame_amount ; index++ )
    {
        result = decoder->GetFrame( index , &frame_decode );

        // Format convert to 32bppPBGRA which D2D expects
        wic_factory->CreateFormatConverter( &format_converter ) >> result_check;

        format_converter->Initialize( frame_decode.Get() ,
                                      WIC_destination_format ,
                                      WICBitmapDitherTypeNone , //WICBitmapDitherTypeErrorDiffusion ,
                                      nullptr , // palete
                                      0.0f , // alpha threshold percent
                                      WICBitmapPaletteTypeMedianCut ) >> result_check; //WICBitmapPaletteTypeCustom );

        context_2d->CreateBitmapFromWicBitmap( format_converter.Get() ,
                                               & frames.at( index ) ) >> result_check;

        meta_data_reader->GetMetadataByName( L"/grctlext/Delay" ,
                                             &properties ) >> result_check;

        // Convert the delay retrieved in 10 ms units to a delay in 1 ms units
        frame_delays.at( index ) = properties.uiVal * 0.01;

        PropVariantClear( &properties );

        meta_data_reader->GetMetadataByName( L"/grctlext/Disposal" ,
                                             & properties );

        disposal_method = properties.bVal;

        PropVariantClear( &properties );
    }
}

void WIC::load_tiff_frames()
{
    frames.resize( frame_amount );

    //frame_delays.resize( frame_amount );

    for( uint index{} ; index < frame_amount ; index++ )
    {
        result = decoder->GetFrame( index , &frame_decode );

        // Format convert to 32bppPBGRA which D2D expects
        wic_factory->CreateFormatConverter( &format_converter ) >> result_check;

        format_converter->Initialize( frame_decode.Get() ,
                                      WIC_destination_format ,
                                      WICBitmapDitherTypeNone , //WICBitmapDitherTypeErrorDiffusion ,
                                      nullptr , // palete
                                      0.0f , // alpha threshold percent
                                      WICBitmapPaletteTypeMedianCut ) >> result_check; //WICBitmapPaletteTypeCustom );

        context_2d->CreateBitmapFromWicBitmap( format_converter.Get() ,
                                               & frames.at( index ) ) >> result_check;
    }
}

void WIC::get_background_colour()
{
    // If we have a global palette, get the palette and background color
    meta_data_reader->GetMetadataByName( L"/logscrdesc/GlobalColorTableFlag" ,
                                         &properties );

    if( properties.vt == VT_BOOL or properties.boolVal )
    {
        // Background color index
        meta_data_reader->GetMetadataByName( L"/logscrdesc/BackgroundColorIndex" ,
                                             &properties );

        if( properties.vt == VT_UI1 )
        {
            gif_background_index = properties.bVal;

            // Get the color from the palette
            wic_factory->CreatePalette( & pallete );

            // Get the global palette
            decoder->CopyPalette( pallete.Get() );

            pallete->GetColors( 256 ,
                                pallete_colours ,
                                & colours_copied );

            // Check whether background colour is inside range 
            //gif_background_index <= colours_copied;

            // Get the color in ARGB format
            background_colour_temp = pallete_colours[ gif_background_index ];

            // The background color is in ARGB format, and we want to 
            // extract the alpha value and convert to float
            float alpha = ( background_colour_temp >> 24 ) / 255.0f;

            background_colour = D2D1::ColorF( background_colour_temp , alpha );
        }
    }
}