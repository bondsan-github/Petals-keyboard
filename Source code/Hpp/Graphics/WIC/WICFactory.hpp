#pragma once

#include <wincodec.h>

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

class WICFactory
{
    public:

       WICFactory();
       ~WICFactory();

    protected:

        static inline ComPtr< IWICImagingFactory > wic_factory {};
};
