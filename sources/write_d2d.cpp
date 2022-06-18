#include "..\headers\write_d2d.h"

//#include < string >
//#include < vector >

//#include < wrl.h >
//#include < memory >

//#include < d2d1.h >
//#include < dwrite.h >

//#include "..\headers\globals.h"
//#include "..\headers\locate.h"
//#include "..\headers\text_d2d.h"

namespace hid
{
    using namespace D2D1;
    using namespace Microsoft::WRL;

    void write_d2d::initialise()
    {

        HRESULT result = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED ,
                                              __uuidof( IDWriteFactory ) ,
                                              & write_factory );

        locate::provide_write( this );
    }

    IDWriteFactory * write_d2d::factory()
    {
        return write_factory.Get();
    }

    void write_d2d::add( wstring in_text       ,
                     point   in_origin     ,
                     float   in_size       ,
                     colours in_colour     ,
                     area    in_dimensions ,
                     wstring in_font       )
    {
        texts.emplace_back( in_text , in_origin , in_size , in_colour , in_dimensions , in_font );
    }

    rect_points_mid write_d2d::middle_points( uint index )
    {
        return texts.at( index ).middle_points();
    }

    void write_d2d::draw()
    {
        for( auto & _text : texts ) _text.draw();
    }

} // namespace hid