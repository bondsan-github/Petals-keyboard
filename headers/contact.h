#pragma once

#include <array>
#include "..\headers\custom_types.h"
#include "..\headers\petal.h"
#include "..\headers\text_d2d.h"

namespace hid
{
    // class petal 
    class contact
    {
        private:

            static inline int        identifier { -1 };
            D2D_POINT_2F             first_contact { 0.0f , 0.0f };
            std::array< petal , 4 >  petals;
            
            const float offset = 20.0f;

            std::array< D2D_POINT_2F , 4 > offsets =
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

            contact();

            void set_inputs( std::array< std::wstring , 4 > in_inputs );
            void update( float in_x , float in_y );
            void draw();
            //bool hit_text_petal( float in_x , float in_y);
    };
}
