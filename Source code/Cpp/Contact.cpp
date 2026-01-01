#include "Contact.h"

namespace HID
{
    Contact::Contact()
    {
        identifier++;
    }

    D2D_POINT_2F const operator + ( const D2D_POINT_2F & in_point_left , const D2D_POINT_2F & in_point_right )
    {
        return { in_point_left.x + in_point_right.x , in_point_left.y + in_point_right.y };
    }

    void Contact::set_inputs( std::array< std::wstring , 4 > in_inputs )
    {
        uint index { 0 };

        for( auto & input : in_inputs )
        {
            petals[ index ].set_input( input );
            ++index;
        }
    }

    void Contact::update( float in_x , float in_y )
    {
    /*
        switch( state )
        {
            case states::Contact:
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
        */
        
    }

    void Contact::draw()
    {
        for( auto & petal : petals ) petal.draw();
    }
}