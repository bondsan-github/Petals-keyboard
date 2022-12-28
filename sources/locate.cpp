#include "..\headers\locate.h"

namespace hid
{
    locate::~locate( void )
    {
        usages   = nullptr;
        graphics = nullptr;
        write    = nullptr;
        windows  = nullptr;
    }
}