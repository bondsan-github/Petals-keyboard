#pragma once

#include "Source code/Hpp/Custom types.hpp"
#include "Source code/Hpp/Graphics/Direct2D/Circle2D.hpp"
#include "Source code/Hpp/Graphics/DWrite/Text.hpp"
#include <string>

namespace HID
{
    class Petal
    {
        private:

            Point    center  { -100 , -100 };
            Circle2D circle  {};
            Text     text    {};
            uint     os_code {};

        public:

            Petal();

            void input( std::wstring in_input );
            void position( int in_x , int in_y );
            void send();
            void update( int in_x , int in_y );
            void draw();
            
    };
}
