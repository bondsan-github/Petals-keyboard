#include "..\headers\grid_d2d.h"

namespace hid
{
    void grid_d2d::initialise( uint in_column_amount , uint in_row_amount )
    {
        locate::add_service( service_identifier::grid , this );

        cell_amount.width  = in_column_amount;
        cell_amount.height = in_row_amount;
        area               = locate::graphics().get_size_dips();

        float cell_width  = area.width / cell_amount.width;
        float cell_height = area.height / cell_amount.height;

        for( float x {} ; x <= area.width ; x += cell_width )
            for( float y {} ; y <= area.height ; y += cell_height )
            {
                lines.emplace_back( vertex{ 0 , y } , vertex{ area.width , y }  , 1.0f ); // horizontal
                lines.emplace_back( vertex{ x , 0 } , vertex{ x , area.height } , 1.0f ); // vertical
            }
    };

    vertex grid_d2d::cell_position( uint in_column , uint in_row )
    {
        return { in_column * cell_size().width , in_row * cell_size().height };
    }

    dimensions grid_d2d::cell_size()
    {
        return { static_cast< uint >( area.width ) / cell_amount.width ,
                 static_cast< uint >( area.height ) / cell_amount.height };
    }

    void grid_d2d::draw()
    {
        for( auto & line : lines ) line.draw();
    }
}