#pragma once

#include "..\headers\custom_types.h"
//#include "..\headers\vertex.h"

#include <d2d1.h>
#include <wrl/client.h>

namespace hid
{
    class circle
    {
        private:

        D2D1_POINT_2F centre {};
        float radius{ 20.0f };
        float line_width { 2.0f };
        D2D1::ColorF colour_outline { D2D1::ColorF::DarkCyan };
        D2D1::ColorF colour_fill { D2D1::ColorF::Cyan };
        D2D1_ELLIPSE ellipse {};
        Microsoft::WRL::ComPtr <ID2D1SolidColorBrush> brush{ nullptr };

        public:
        
        circle();
        void set_centre( float in_x, float in_y ) { centre.x = in_x , centre.y = in_y; }
        void set_radius( float in_radius ) {}
        void draw();
    };
}