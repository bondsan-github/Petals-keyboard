
#include "Graphics\Direct2D\Sprite.h"

void Sprite::update( )
{
    if( frame_amount > 1 )
    {
        if( ( current_frame_time += Timer::delta() ) > frame_delays.at( frame_index ) )
        {
            if( frame_index < frame_amount - 1 ) frame_index++;
            else frame_index = 0;

            current_frame_time = 0;
        }
    }
}
