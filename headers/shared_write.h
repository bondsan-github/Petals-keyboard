#pragma once

//#include "..\headers\write.h"
#include < memory >

class write;

namespace hid
{
    struct shared_write
    {
        inline static shared_ptr< write > write_ptr {};
    };
}
