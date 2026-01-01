#pragma once

#include <dxgicommon.h>

class Colour_space
{
    public:

        enum class Channel_type    { rgb  , ycbcr };
        enum class Range           { full , studio };
        enum class Gamma           { g10  , g22  , g2084 , ghlg };
        enum class Siting          { none , left , top_left };
        enum class Primaries       { p601 , p709 , p2020 };
        enum class Transfer_matrix { x601 , x709 , x2020 };

        Colour_space() {};
        Colour_space( DXGI_COLOR_SPACE_TYPE type )
        {
            switch( type )
            {
                case 0:
                {
                    channel_type = Channel_type::rgb;
                    range        = Range::full;
                    gamma        = Gamma::g22;
                    siting       = Siting::none;
                    primaries    = Primaries::p709;
                    matrix       = Transfer_matrix::x709;
                } break;
            }
        }

    private:

        Channel_type channel_type;
        Range range;
        Gamma gamma;
        Siting siting;
        Primaries primaries;
        Transfer_matrix matrix;
};





