#include "Graphics\Direct2D\Image.h"

Image::Image( std::wstring filename )
{
    load( filename );
}

void Image::load( std::wstring filename )
{
    WIC::load( filename );

    D2D1_BITMAP_PROPERTIES properties {};

    properties.pixelFormat = { DXGI_FORMAT_B8G8R8A8_UNORM , 
                               D2D1_ALPHA_MODE_PREMULTIPLIED };
                               //D2D1_ALPHA_MODE_STRAIGHT };
                               
    //properties.dpiX = 96;
    //properties.dpiY = 96;

    //source_rectangle += size;
    source_rectangle.right  = width;
    source_rectangle.bottom = height;

    //destination_rectangle += size;
    destination_rectangle.right  = width;
    destination_rectangle.bottom = height;
}

void Image::draw( Point position )
{
    if( context_2d )
    {
        context_2d->SetTransform( matrix_scale * matrix_rotation * matrix_translation );

        if( frames.at( frame_index ) )
        {
            context_2d->DrawBitmap( frames.at( frame_index ).Get() ,
                                    position + destination_rectangle ,
                                    opacity ,
                                    interpolation ,
                                    source_rectangle );
        }
    }
}

void Image::scale( float in_scale )
{
    matrix_scale = D2D1::Matrix3x2F::Scale( in_scale , in_scale );
}
