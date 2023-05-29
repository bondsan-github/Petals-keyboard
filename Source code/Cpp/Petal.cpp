#include "Petal.hpp"

namespace HID
{
    Petal::Petal()
    {
       // text.set_font_size(10);
        text.show_border( false );
    }

    void Petal::set_input( std::wstring input )
    {
        os_code = inputs_english.at( input );

        text.set( input );
    }

    void Petal::set_position( int in_x , int in_y )
    {
        text.set_position( { in_x - 5.0f , in_y -8.0f } );

        circle.set_position( { in_x , in_y } );
        //circle.set_state( circle_d2d::states::on );
    }

    void Petal::update( int in_x , int in_y )
    {
    /*
        if( circle.selected( in_x , in_y ) )
        {
            circle.set_state( circle_d2d::states::selected );
        }
        else
        {
            circle.set_state( circle_d2d::states::on );
        }
        // long time_now = locate::get_timer().now()
        //
        */
    }

    void Petal::draw()
    {
        //circle.draw();
        text.draw();
    }

    void Petal::send()
    {
        //SendInput();
    }
}