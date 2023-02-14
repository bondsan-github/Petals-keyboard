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
        circle.set_centre( { in_x , in_y } );
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