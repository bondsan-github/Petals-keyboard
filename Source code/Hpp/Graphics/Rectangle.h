#pragma once

#include "Graphics\Point.h"
#include "Graphics\Size.h"

#include <d2d1.h>

class Rectangle
{
    private:

        int top_    {};
        int right_  {};
        int bottom_ {};
        int left_   {};
        
        // Point1 , Point 2;

    public:
        
        Rectangle();
        Rectangle( int x1 , int y1 , int x2 , int y2 );

        void position( int x1 , int y1 , int x2 , int y2 );
        void position( Point in_point1 , Point in_point2 );

        void size( int width , int height );
        void size( float in_size );

        void operator = ( D2D1_SIZE_F in_size );
        void operator + ( float in_size );
        operator D2D1_RECT_F ();

};
