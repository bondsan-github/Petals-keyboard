#include "..\headers\text_d2d.h"

//#include "..\headers\graphics_d2d.h"
//#include "..\headers\write_d2d.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    text::text( wstring in_content    ,
                point   in_center     , // position 0..1
                float   in_size       ,
                colours in_colour     ,
                area    in_dimensions ,
                wstring in_font       )
    : content( in_content ) , center( in_center ) , size( in_size ) , colour( in_colour ) , dimensions( in_dimensions )
    {
    }

    float text::width()       { return dimensions.width; }
    float text::width_half()  { return dimensions.width / 2.0f; }
    float text::height()      { return dimensions.height; }
    float text::height_half() { return dimensions.height / 2.0f; }
    /*
    void text::position( point in_center )
    {
        center = in_center; // x,y = 0..1

        float dpi_x{};
        float dpi_y{};

        // screen_width / position.x
        window_render_target * sheet_ptr = locate::graphics_ptr()->sheet_ptr();

        sheet_ptr->GetDpi( &dpi_x , &dpi_y );

        area size = sheet_ptr->GetSize();
    }
    */
    point text::top_left()
    {
        point top_left{}; // in pixels

        top_left.x = center.x - width_half();
        top_left.y = center.y - height_half();

        return top_left;
    }

    void text::reset()
    {
        reset_format();
        reset_layout();
        reset_brush();
    }

    void text::reset_brush()
    {
        locate::graphics()->sheet_ptr()->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );
    }

    void text::reset_format()
    {
        //enum class text_style { normal , oblique , italic };
        //enum class text_weight : int { light = 300 , regular = 400 , bold = 700 };

        //write::factory()->CreateText
        HRESULT result = locate::write()->factory()->CreateTextFormat( font.c_str() ,
                                                                          0 ,
                                                                          DWRITE_FONT_WEIGHT_NORMAL , //static_cast< DWRITE_FONT_WEIGHT >( to_underlying( text_weight::regular ) ),
                                                                          DWRITE_FONT_STYLE_NORMAL ,
                                                                          DWRITE_FONT_STRETCH_NORMAL ,
                                                                          size ,
                                                                          L"en-us" , // locale       
                                                                          format.ReleaseAndGetAddressOf() );

                        //format->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ); // _LEADING
        format->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );

        //trimming trim{};
        //trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;
        //format->SetTrimming( & trim , 0 );
    }

    void text::reset_layout()
    {
        locate::write()->factory()->CreateTextLayout( content.c_str() ,
                                                         content.size() ,
                                                         format.Get() ,
                                                         dimensions.width ,
                                                         dimensions.height ,
                                                         layout.ReleaseAndGetAddressOf() );
    }

    void text::set_content( wstring in_content )
    {
        content = in_content;

        reset();
    }

    void text::add( const wstring in_string )
    {
        content += in_string;

        reset();
    }

    void text::draw()
    {
        draw_text();
    }

    void text::draw_text()
    {
        window_render_target * sheet_ptr = locate::graphics()->sheet_ptr();

        //if( sheet_ptr )
        sheet_ptr->DrawTextLayout( top_left() , layout.Get() , brush.Get() );
    }
    /*
    void reset_bounds()
    {

        rect.left   = top_left.x - 5;
        rect.top    = origin.y - 5;
        rect.right  = origin.x + dimensions.width + 5;
        rectangle.bottom = origin.y + dimensions.height + 5;

        temp.left   = center.x - -5;
        temp.top    = origin.y - 5;
        temp.right  = origin.x + dimensions.width + 5;
        temp.bottom = origin.y + dimensions.height + 5;
    }

    void draw_bounds()
    {
        window_render_target * sheet_ptr = locate::graphics_ptr()->sheet_pointer();
        //if( sheet_ptr )
        sheet_ptr->DrawRoundedRectangle( rrectangle , brush.Get() );
    }

    struct planes
    {
        float horizontal {};
        float vertical   {};
    };

    planes middle_planes( float in_width , float in_height )
    {
        planes middle {};

        middle.horizontal = center.x + ( in_width / 2.0f );
        middle.vertical   = center.y;

        return middle;
    }

    rect_points_mid middle_points()
    {
        rect_points_mid middles {};



        float mid_horizontal = ( temp.right - temp.left ) / 2.0f;
        float mid_vertical   = ( temp.bottom - temp.top ) / 2.0f;

        mid.top.x    = temp.left + mid_horizontal;
        mid.top.y    = temp.top;

        mid.right.x  = temp.right;
        mid.right.y  = temp.top + mid_vertical;

        mid.bottom.x = mid.top.x;
        mid.bottom.y = temp.bottom;

        mid.left.x   = temp.left;
        mid.left.y   = mid.right.y;

        return mid;

        rectangle     bounding_box{};
        //middle_planes planes{ dimensions.width , dimensions.height };

        reset_bounds()
        {


        }
        //int []
    }
    */
    rect_points_mid text::middle_points()
    {
        rect_points_mid points{};
        return points;
    }

} // namespace hid