#pragma once

#include <memory>
//#include "..\headers\graphics.h"
class graphics;

namespace hid
{
    struct shared_graphics
    {
        //protected:
            inline static shared_ptr< graphics > graphics_ptr {};
            //extern graphics * graphics_ptr;
    };
}