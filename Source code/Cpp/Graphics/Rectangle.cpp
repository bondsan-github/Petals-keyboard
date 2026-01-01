#include "Graphics\Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle( int x1 , int y1 , int x2 , int y2 )
{   
    top_   = y1;
    left_  = x1;

    right_  = x2;
    bottom_ = y2;
}

void Rectangle::position( int x1 , int y1 , int x2 , int y2 )
{ 
    top_   = y1;
    left_  = x1;

    right_  = x2;
    bottom_ = y2;
}

void Rectangle::position( Point point1 , Point point2 ) 
{ 
    top_  = point1.y();
    left_ = point1.x();

    right_ = point2.x();
    bottom_ = point2.y();
}

void Rectangle::size( int width , int height ) 
{
    bottom_ = height;
    right_  = width;
}

void Rectangle::size( float size )
{
    bottom_ = size;
    right_  = size;
}

void Rectangle::operator = ( D2D1_SIZE_F size )
{
    bottom_ = size.height;
    right_  = size.width;
}

void Rectangle::operator + ( float size )
{
    top_   -= size;
    left_  -= size;

    right_  += size;
    bottom_ += size;
}

Rectangle::operator D2D1_RECT_F()
{
    return { static_cast< float >( left_ ),
             static_cast< float >( top_ ),
             static_cast< float >( right_ ),
             static_cast< float >( bottom_ ) };
}