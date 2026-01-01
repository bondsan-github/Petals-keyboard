#pragma once

#include <array>
#include <d3d11.h>
#include <DirectXMath.h>

struct Vertex_uv
{
    DirectX::XMFLOAT4 position {};
    DirectX::XMFLOAT2 uv {};
};

class Input_layouts
{
    private:

        std::array< D3D11_INPUT_ELEMENT_DESC , 2 > layout {};

    public:

        Input_layouts()
        {
            unsigned int index {};

            layout[ index ].SemanticName         = "SV_POSITION";
            layout[ index ].SemanticIndex        = 0u;
            layout[ index ].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
            // 32 / 8 = 4, 4 * 4 = 16 
            layout[ index ].InputSlot            = 0u;
            layout[ index ].AlignedByteOffset    = 0u;
            layout[ index ].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            layout[ index ].InstanceDataStepRate = 0;

            /*
            layout[ index ].SemanticName         = "COLOR";
            layout[ index ].SemanticIndex        = 0u;
            layout[ index ].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
            layout[ index ].InputSlot            = 0u;
            layout[ index ].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;//16;
            layout[ index ].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            layout[ index ].InstanceDataStepRate = 0;
            */

            index++;

            layout[ index ].SemanticName         = "TEXCOORD";
            layout[ index ].SemanticIndex        = 0u;
            layout[ index ].Format               = DXGI_FORMAT_R32G32_FLOAT;
            layout[ index ].InputSlot            = 0u;
            layout[ index ].AlignedByteOffset    = 16;//D3D11_APPEND_ALIGNED_ELEMENT;
            layout[ index ].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            layout[ index ].InstanceDataStepRate = 0;
        }

        std::array< D3D11_INPUT_ELEMENT_DESC , 2 > get_layout() const { return layout; }
}; 

/*
DXGI_FORMAT_R32G32B32A32_FLOAT = +16 = Since an XMFLOAT3 is 4 bytes x 4 = 16 bytes in size ,
DXGI_FORMAT_R8G8B8A8_UINT = +4 // 32 / 8 = 4
colour coordinates won’t appear in vertex until after 12th byte
DXGI_FORMAT_R32G32B32A32_FLOAT = +16 = XMFLOAT4 = 4 bytes (= 32bits) x 4 values = 16 bytes
*/