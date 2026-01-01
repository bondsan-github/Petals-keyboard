#include "Graphics\Line.h"


Line::Line( Point a,
            Point b,
            float width,
            colours colour )
: a_( a ), b_( b ), width_( width ), colour( colour ) //, brush( brush_solid( colour ) )
{
    //OutputDebugString( L"\n line_d2d::constructor" );
    //reset();
}

//Line::~Line() { OutputDebugString( L"\n Line::de-constructor" ); }

void Line::reset()
{
    //brush = Direct2D.brush_solid( colour );
}

void Line::draw()
{
    locate::get_graphics().draw_line( a_ , b_, width_ , colour_ );
}