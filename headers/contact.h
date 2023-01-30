#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\circle_d2d.h"

namespace hid
{
    class contact
    {
        private:

            static inline int identifier{ -1 };
            ulong x    { 0ul };
            ulong y    { 0ul };
            circle_d2d circle;
            const enum class states { off , on };//, fading , moving };
            states state{ states::off };

        public:

            contact();

            void set_position( ulong in_x , ulong in_y);
            void draw();
    };
}
