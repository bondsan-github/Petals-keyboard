#pragma once

#include "d2d1_3.h"

#include <wrl\client.h> // ComPtr
using Microsoft::WRL::ComPtr;

class Factory2D
{
    protected:

        static inline ComPtr< ID2D1Factory7 > factory_2d {};
};
