#include "..\headers\circle_d2d.h"
#include "..\headers\locate.h"

namespace hid
{
    circle_d2d::circle_d2d()
    {
        locate::get_graphics().get_page().CreateSolidColorBrush( colour_fill , &brush );
    }

    void circle_d2d::set_centre( D2D_POINT_2F in_centre ) 
    {
        centre = in_centre;
    }

    void circle_d2d::draw()
    {
        //To convert a physical pixel to a DIP , use this formula:
        //dip = ( physical pixel × 96 ) / DPI

        ellipse.point = centre;
        ellipse.radiusX = radius;
        ellipse.radiusY = radius;

        locate::get_graphics().get_page().FillEllipse( &ellipse , brush.Get() );
    }
}