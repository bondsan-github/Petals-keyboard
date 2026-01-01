#pragma once

#include <d2d1_3.h>

#include "Custom types.h"
#include "Graphics\Vertex.h"

class line_2d 
{
    private:

        Vertex                  a      {};
        Vertex                  b      {};
        float                   width  { 1.0f };
        D2D1::ColorF            colour { D2D1::ColorF::Yellow };
        //ID2D1SolidColorBrush & brush;
        brush_solid_pointer brush {};
        ComPtr< stroke_style >  style  {};

    public:

        line_d2d( vertex in_a = { 0.0f , 0.0f } ,
                    vertex in_b = { 1.0f , 1.0f } ,
                    float in_width = 1.0f ,
                    D2D1::ColorF in_colour = D2D1::ColorF( 0.4f , 0.4f , 0.2f , 0.2f ) );
        //~line_d2d( void );

        void reset();

        void draw();

};