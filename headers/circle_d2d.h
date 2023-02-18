#pragma once

#include "..\headers\custom_types.h"

#include <d2d1.h>
#include <wrl/client.h>

namespace hid
{
    class circle_d2d
    {
        public:

            enum class states { off , on , selected , fading_in , fading_out };

        private:

            D2D1_POINT_2F centre         { -100.0f , -100.0f };
            float         radius         { 20.0f };
            float         line_width     { 2.0f };
            D2D1::ColorF  colour_outline { D2D1::ColorF::DarkCyan };
            D2D1::ColorF  colour_fill_on { D2D1::ColorF::DarkBlue };
            D2D1::ColorF  colour_fill_selected { D2D1::ColorF::Cyan };
            D2D1_ELLIPSE  ellipse        { .point   = centre ,
                                           .radiusX = radius ,
                                           .radiusY = radius };
            Microsoft::WRL::ComPtr <ID2D1EllipseGeometry> ellipse_geometry {};
            Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_on { nullptr };
            Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_selected { nullptr };
            
            states state { states::off };

        public:
            
            circle_d2d();

            void set_position( D2D_POINT_2F );
            //void set_radius( float in_radius ) {}
            void set_state( states in_state ) { state = in_state; }
            bool selected( float in_x , float in_y );
            void draw();
    };
}