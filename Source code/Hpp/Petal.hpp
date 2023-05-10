#pragma once

#include "Source code/Hpp/Custom types.hpp"

#include "..\headers\circle2D.hpp"
#include "..\headers\text_d2d.h"
 
#include <string>

namespace hid
{
    class petal
    {
        private:

            Point center { -100.0f , -100.0f };
            Circle2D   circle; // geometry
            Text     text;
            uint         os_code { 0 };

        public:

            petal();

            void set_input( std::wstring in_input );
            void update( float in_x , float in_y ); 
            void set_position( float in_x , float in_y );
            void draw();
            void send_input();
    };
}
