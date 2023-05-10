#pragma once


#include "Source code/Hpp/Custom types.hpp"

#include "Source code/Hpp/Petal.hpp"
#include "..\headers\text_d2d.h"

#include <array>

namespace hid
{
    // class petal 
    class Contact
    {
        private:

            static inline int        identifier { -1 };
            Point             first_contact { 0.0f , 0.0f };
            std::array< Petal , 4 >  petals;
            
            const float offset = 20.0f;

            std::array< Point , 4 > offsets =
            {//    x    ,     y
                0.0f    , -offset , // top 
                +offset , 0.0f    , // right
                0.0f    , +offset , // bottom
                -offset , 0.0f    , // left
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

            void inputs( std::array< std::wstring , 4 > in_inputs );
            void update( float in_x , float in_y );
            void draw();
            //bool hit_text_petal( float in_x , float in_y);
    };
}
