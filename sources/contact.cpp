#include "..\headers\contact.h"

namespace hid
{
    D2D_POINT_2F const operator + ( const D2D_POINT_2F & in_point_left , const D2D_POINT_2F & in_point_right )
    {
        return { in_point_left.x + in_point_right.x , in_point_left.y + in_point_right.y };
    }

    contact::contact()
    {
        identifier++;
    }

    void contact::set_inputs( std::array< std::wstring , 4 > in_inputs )
    {
        uint index { 0 };

        for( auto & input : in_inputs )
        {
            petals[ index ].set_input( input );
            ++index;
        }
    }

    void contact::update( float in_x , float in_y )
    {
        switch( state )
        {
            case states::contact:
            {
                first_contact = { in_x , in_y };

                uint index { 0 };

                for( auto & petal : petals )
                {
                    petal.set_position( in_x + offsets.at( index ).x ,
                                        in_y + offsets.at( index ).y );
                    ++index;
                }

                state = states::chosing_petal;
            } break;

            case states::chosing_petal:
            {
                for( auto & petal : petals )
                {
                    petal.update( in_x , in_y );
                }
            } break;
        }

        // if within screen bounds
        
    }

    void contact::draw()
    {
        for( auto & petal : petals ) petal.draw();
    }
}