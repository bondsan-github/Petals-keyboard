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

            D2D_POINT_2F center;
            circle_d2d   circle;
            text_d2d     text;
            uint         os_code;

        public:

            petal();

            void set_input( std::wstring in_input );
            //void update( uint in_x , uint in_y );
            void set_position( float in_x , float in_y );
            void draw();
            void send_input();
    };
}
