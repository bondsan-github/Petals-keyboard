#include "..\headers\petal.h"

namespace hid
{

    petal::petal()
    {
       // text.set_font_size(10);
        text.set_show_border( false );
    }

    void petal::set_input( std::wstring in_input )
    {
        os_code = inputs_english.at( in_input );

        text.set_content( in_input );
    }

    void petal::set_position( float in_x , float in_y )
    {
        text.set_position_top_left( { in_x - 5.0f , in_y -8.0f } );
        circle.set_position( { in_x , in_y } );
        circle.set_state( circle_d2d::states::on );
    }

    void petal::update( float in_x , float in_y )
    {
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
    }

    void petal::draw()
    {
        circle.draw();
        text.draw();
    }

    void petal::send_input()
    {
        //SendInput();
    }
}