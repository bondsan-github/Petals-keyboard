#include "..\headers\circle_d2d.h"
#include "..\headers\locate.h"

namespace hid
{
    circle_d2d::circle_d2d()
    {
        locate::get_graphics().get_page().CreateSolidColorBrush( colour_fill_on , &brush_on );
        locate::get_graphics().get_page().CreateSolidColorBrush( colour_fill_selected , &brush_selected );

        locate::get_graphics().get_factory().CreateEllipseGeometry( ellipse , &ellipse_geometry );
    }

    void circle_d2d::set_position( D2D_POINT_2F in_centre ) 
    {
        ellipse.point = in_centre;

        locate::get_graphics().get_factory().CreateEllipseGeometry( ellipse , &ellipse_geometry );
    }

    void circle_d2d::draw()
    {
        switch( state )
        {
            case states::on:
            {
                locate::get_graphics().get_page().FillGeometry( ellipse_geometry.Get() , brush_on.Get() );
            } break;

            case states::selected:
            {
                locate::get_graphics().get_page().FillGeometry( ellipse_geometry.Get() , brush_selected.Get() );
            } break;
        }
        
    }

    bool circle_d2d::selected( float in_x , float in_y )
    {
        BOOL contains = false;
        ellipse_geometry->FillContainsPoint( {in_x , in_y}, 0 , &contains );

        return static_cast<bool>( contains );
    }
}