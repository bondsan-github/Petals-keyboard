#include "..\headers\line_d2d.h"

#include "..\headers\locate.h"
#include "..\headers\graphics_d2d.h"

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    line_d2d::line_d2d( vertex in_a       ,
                        vertex in_b       ,
                        float in_width    ,
                        colours in_colour )
    : a ( in_a ) , b ( in_b ) , width ( in_width ) , colour ( in_colour )
    {
        reset();
    }

    void line_d2d::reset()
    {
        brush = locate::graphics()->brush_solid( colour );
    }

    void line_d2d::draw()
    {
        locate::graphics()->draw_line( a , b , width , colour );
    }

} // namespace hid