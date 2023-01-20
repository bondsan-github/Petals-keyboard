#include "..\headers\circle_d2d.h"
#include "..\headers\locate.h"

namespace hid
{
    circle::circle()
    {
        locate::get_graphics().get_page().CreateSolidColorBrush( colour_fill , &brush );
    }

    void circle::draw()
    {
        ellipse.point = centre;
        ellipse.radiusX = radius;
        ellipse.radiusY = radius;

        locate::get_graphics().get_page().FillEllipse( &ellipse , brush.Get() );
    }
}