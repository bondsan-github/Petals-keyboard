#include "..\headers\contact.h"

namespace hid
{
    contact::contact() 
    {
        identifier++;
    }

    void contact::set_position( ulong in_x , ulong in_y )
    {
        // if within screen bounds
        x = in_x;
        y = in_y;

        circle.set_centre( x , y );
    }

    void contact::draw()
    {
        circle.draw();
    }
}