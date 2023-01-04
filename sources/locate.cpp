#include "..\headers\locate.h"

namespace hid
{
    locate::~locate( void )
    {
        input_devices = nullptr;
        usages   = nullptr;
        write    = nullptr;
        windows  = nullptr;
        graphics = nullptr;
        application = nullptr;
    }
}