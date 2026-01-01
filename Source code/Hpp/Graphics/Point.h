#pragma once

#include <d2d1.h>

class Point
{
    private:

        int x_ {};
        int y_ {};

    public:

        Point();
        Point( int x , int y );
        //Point( float x , float y );

        void x( int x );
        void y( int y );

        int  x();
        int  y();

        // <=> starship operator
        D2D1_RECT_F operator + ( D2D1_RECT_F rectangle );
        Point       operator - ( float in_value );
        Point &     operator -= ( float in_value );
        
                    operator D2D1_POINT_2F ();
                    operator D2D1_SIZE_F ();
};
