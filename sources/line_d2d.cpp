#include "..\headers\line_d2d.h"

//#include "..\headers\locate.h"
//#include "..\headers\graphics_d2d.h"

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    line_d2d::line_d2d( point in_a        ,
                        point in_b        ,
                        float in_width    ,
                        colours in_colour )
    : a( in_a ) , b( in_b ) , width( in_width ) , colour( in_colour )
    {
    }

    void line_d2d::draw()
    {
        if( brush.Get() == nullptr )
            locate::graphics()->sheet_ptr()->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );

        if( locate::graphics()->sheet_ptr() )
            locate::graphics()->sheet_ptr()->DrawLine( a , b , brush.Get() , width , style.Get() );
    }

} // namespace hid