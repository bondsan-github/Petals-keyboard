#include "Graphics\Size.h"

Size::Size()
{
};

Size::Size( int width , int height ) 
    : width_( width ) , height_( height )
{
}

Size::operator bool() const
{
    return ( width_ and height_ );
}

bool Size::operator == ( Size const & size )
{
    return size.width_ == width_ and size.height_ == height_;
}

bool Size::operator != ( Size const & size )
{
    return size.width_ != width_ or size.height_ != height_;
}

Size & Size::operator += ( float in_size )
{
    width_  += static_cast< int >( in_size );
    height_ += static_cast< int >( in_size );

    return *this;
}

// conversion
Size::operator D2D1_SIZE_U ()
{
    return { static_cast< unsigned int >( width_ ) ,
             static_cast< unsigned int >( height_ ) };
}

Size::operator D2D1_SIZE_F ()
{
    return { static_cast< float >( width_ ) ,
             static_cast< float >( height_ ) };
}

Size::operator RECT ()
{
    return 
    {
        .left   {} ,
        .top    {} ,
        .right  = static_cast< long >( width_ ) , // origin top left = right - left
        .bottom = static_cast< long >( height_ )  // origin top left = bottom - top
    };
}

bool Size::operator < ( Size const & in_rectangle )
{
    return { ( width_ * height_ ) < ( in_rectangle.width() * in_rectangle.height() ) };

}

void Size::width( int width ) 
{
    width_ = width;
}

void Size::height( int height ) 
{ 
    height_ = height;
}

void Size::width( float width ) 
{
    width_ = static_cast< int >( width );
}

void Size::height( float height ) 
{
    height_ = static_cast< int >( height );
}

void Size::width( long width ) 
{
    width_ = static_cast< int >( width );
}

void Size::height( long height ) 
{
    height_ = static_cast< int >( height );
}

int  Size::width() const 
{
    return width_;
}

int  Size::height() const 
{
    return height_;
}