#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\circle_d2d.h"
#include "..\headers\text_d2d.h"
 
#include <string>

namespace hid
{
    class petal
    {
        private:

            D2D_POINT_2F center { -100.0f , -100.0f };
            circle_d2d   circle; // geometry
            text_d2d     text;
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
