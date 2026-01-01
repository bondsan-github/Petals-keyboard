#include "Source code/Hpp/Graphics/Point.hpp"

Point::Point() 
{
};

Point::Point( int x , int y ) 
    : x_( x ) , y_( y ) 
{
}

void Point::x( int x ) 
{
    x_ = x;
}

void Point::y( int y ) 
{
    y_ = y;
}

int Point::x() const 
{
    return x_;
}

int Point::y() const
{
    return y_;
}

D2D1_RECT_F Point::operator + ( D2D1_RECT_F & in_rect )
{
    return { static_cast< float >( x_ )  ,
             static_cast< float >( y_ ) ,
             static_cast< float >( x_ ) + in_rect.right ,
             static_cast< float >( y_ ) + in_rect.bottom };
}

Point::operator D2D1_POINT_2F ()
{
    return { static_cast< float >( x_ ) ,
             static_cast< float >( y_ ) };
}

Point::operator D2D1_SIZE_F ()
{
    return { static_cast< float >( x_ ) ,
             static_cast< float >( y_ ) };
}

Point & Point::operator -= ( float in_value )
{
    x_ -= static_cast< int >( in_value );
    y_ -= static_cast< int >( in_value );

    return *this;
}

Point Point::operator - ( float in_value )
{
    x_ -= static_cast< int >( in_value );
    y_ -= static_cast< int >( in_value );

    return *this;
}