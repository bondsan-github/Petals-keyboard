#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Usages.h"

//#include "Input\HID\Device.h"

namespace HID
{
    class Device;

    class Value : public HIDP_VALUE_CAPS, public Usages
    {
        private:
            
            ulong        value_unsigned { 0ul }; // = 0xffff'ffff
            long         value_signed { -1 };

            Device & device;

        public:

            Value( Device & device, HIDP_VALUE_CAPS & ) : device( device ) {};

            void update( RAWINPUT * raw_data );

            long  value() { return value_signed; }

            Value() = default;
    };
}