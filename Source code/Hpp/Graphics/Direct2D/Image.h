#pragma once

#include <wrl/client.h> // ComPtr
using Microsoft::WRL::ComPtr;

#include <d2d1_3.h>
#include <d2d1helper.h>
#include <wincodec.h>

#include <string>
#include <vector>

#include "Graphics\WIC\WIC.h"
#include "Graphics\Point.h"

class Image : public WIC
{
    private:

        HRESULT result { E_FAIL };

        D2D1_RECT_F destination_rectangle{};
        D2D1_RECT_F source_rectangle{};
        float       opacity{ 1.0f };
        D2D1_BITMAP_INTERPOLATION_MODE interpolation { D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR };
        //D2D1_MATRIX_4X4_F

        D2D1_MATRIX_3X2_F matrix_scale       { D2D1::Matrix3x2F::Identity() };
        D2D1_MATRIX_3X2_F matrix_rotation    { D2D1::Matrix3x2F::Identity() };
        D2D1_MATRIX_3X2_F matrix_translation { D2D1::Matrix3x2F::Identity() };

    protected:

        uint frame_index {};

    public:

        Image() = default;
        Image( std::wstring in_image );

        void load( std::wstring filename );

        //void set_frame_index( uint in_frame_index ) { frame_index = in_frame_index; }
        //uint get_frame_index() { return frame_index; }

        void draw( Point position = {} );

        void scale( float in_scale );
};
