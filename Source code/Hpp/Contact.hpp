#pragma once

#include "Source code/Hpp/Custom types.hpp"
#include "Source code/Hpp/Graphics/DWrite/Text.hpp"

#include "Petal.hpp"

#include <array>

namespace HID
{
    // class petal 
    class Contact
    {
        private:

            static inline int       identifier { -1 };
            Point                   first_contact {};
            std::array< Petal , 4 > petals;
            
            const int offset = 20;

            std::array< Point , 4 > offsets =
            {
                Point{ 0        , -offset } , // top 
                Point{ +offset  , 0       } , // right
                Point{ 0        , +offset } , // bottom
                Point{ -offset  , 0       } , // left
            };

            const enum class states 
            { 
                contact ,
                chosing_petal ,
                off ,
                on
                //, fading , moving
            };

            states state { states::off };

        public:

            Contact();

            void set_inputs( std::array< std::wstring , 4 > in_inputs );
            void update( float in_x , float in_y );
            void draw();
            //bool hit_text_petal( float in_x , float in_y);
    };
}
