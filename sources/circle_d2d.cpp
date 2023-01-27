#include "..\headers\circle_d2d.h"
#include "..\headers\locate.h"

namespace hid
{
    circle_d2d::circle_d2d()
    {
        locate::get_graphics().get_page().CreateSolidColorBrush( colour_fill , &brush );
    }

    void circle_d2d::draw()
    {
        ellipse.point = centre;
        ellipse.radiusX = radius;
        ellipse.radiusY = radius;

        locate::get_graphics().get_page().FillEllipse( &ellipse , brush.Get() );
    }
}