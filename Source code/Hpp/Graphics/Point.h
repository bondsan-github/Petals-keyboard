#pragma once

//#include <d2d1.h>

class Point
{
    private:

        int x_ {};
        int y_ {};

    public:

        Point() {};
        Point( int x , int y ) { x_ = x; y_ = y; }
        //Point( float x , float y );

        void x( int x ) { x_ = x; }
        void y( int y ) { y_ = y; }

        int  x() { return x_; }
        int  y() { return y_; }

        /*
        // <=> starship operator
        D2D1_RECT_F operator + ( D2D1_RECT_F rectangle );
        Point       operator - ( float in_value );
        Point &     operator -= ( float in_value );
        
                    operator D2D1_POINT_2F ();
                    operator D2D1_SIZE_F ();
        */
};
