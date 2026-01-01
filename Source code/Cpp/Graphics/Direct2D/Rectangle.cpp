#include "Graphics\Direct2D\Rectangle.h"


Rectangle2D::Rectangle2D()
{
    context_2d->CreateSolidColorBrush( line_colour_ , & brush_ );
    //factory_2d->CreateStrokeStyle()
}

void Rectangle2D::line_colour( D2D1::ColorF colour )
{ 
    line_colour_ = colour;

    context_2d->CreateSolidColorBrush( line_colour_ , &brush_ );
}

void Rectangle2D::draw()
{
    context_2d->DrawRectangle( *this,
                               brush_.Get() ,
                               line_width_,
                               style_.Get() );
}