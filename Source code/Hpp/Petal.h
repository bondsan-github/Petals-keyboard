#pragma once

#include "Aliases.h"

#include "Graphics\Direct2D\Circle.h"
//#include "Graphics\DWrite\Text.h"
 
#include <string>

namespace HID
{
    class Petal
    {
        private:

            Point    center  { -100 , -100 };
            Circle2D circle  {};
            //Text     text    {};
            uint     os_code {};

        public:

            Petal();

            void input( std::wstring input );
            void position( int x, int y );
            void send();
            void update( int x, int y );
            void draw();
            
    };
}
