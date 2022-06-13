#pragma once

#include < string >
#include < vector >

#include < wrl.h >
#include < d2d1.h >
#include < dwrite.h >

#include "..\headers\globals.h"
#include "..\headers\shared_write.h"
#include "..\headers\shared_graphics.h"
#include "..\headers\graphics.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    class text : public shared_write , public shared_graphics
    {
        ComPtr< ms_text_format >        format{}; // simple version of text_layout
        ComPtr< ms_brush_solid_colour > brush{};
        ComPtr< ms_text_layout >        layout{};

        wstring           content    {};
        point             origin     {}; // top left
        wstring           font       { L"Times New Roman" }; // font family
        float             size       { 15.0f }; // MS "size * 96.0f/72.0f"
        colours           colour     { colours::Yellow };
        area              dimensions {};
        rounded_rectangle rrectangle {};
        float             radius     { 5.0f };

        public:

        text( wstring                 in_content    ={} ,
              point                   in_origin     ={ 10.0f , 10.0f } ,
              float                   in_size       ={ 15u } ,
              colours                 in_colour     ={ colours::Yellow } ,
              area                    in_dimensions ={ 150.0f , 100.0f } ,
              wstring                 in_font       ={ L"Times New Roman" } )
            : content( in_content ) , origin( in_origin ) , size( in_size ) , colour( in_colour ) , dimensions( in_dimensions )
        {
            //reset();
        }

        rectangle_midpoints mid_points() const
        {
            rectangle           temp{};
            rectangle_midpoints mid{};

            temp.left   = origin.x - 5;
            temp.top    = origin.y - 5;
            temp.right  = origin.x + dimensions.width + 5;
            temp.bottom = origin.y + dimensions.height + 5;

            float mid_horizontal = ( temp.right - temp.left ) / 2.0f; // fabs()
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
        }

        void reset()
        {
            reset_format();
            reset_layout();
            reset_brush();
        }

        void reset_brush()
        {
            graphics_ptr->sheet_pointer()->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );
        }

        void reset_format()
        {
            
            enum class text_style { normal , oblique , italic };
            enum class text_weight { light = 300 , regular = 400 , bold = 700 };

            //write::factory()->CreateText
            HRESULT result = write_ptr->factory()->CreateTextFormat(font.c_str() ,
                                                              0 ,
                                                              DWRITE_FONT_WEIGHT_REGULAR ,
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

        void reset_layout()
        {
            write_ptr->factory()->CreateTextLayout(content.c_str() ,
                                             content.size() ,
                                             format.Get() ,
                                             dimensions.width ,
                                             dimensions.height ,
                                             layout.ReleaseAndGetAddressOf() );
        }

        void add( const wstring in_string )
        {
            content += in_string;

            reset();
        }

        void draw()
        {
            // render_target_window / sheet
            window_render_target * sheet_ptr = graphics_ptr->sheet_pointer();

            if( sheet_ptr )
            {
                sheet_ptr->DrawTextLayout( origin , layout.Get() , brush.Get() );

                rrectangle.radiusX = rrectangle.radiusY = radius;

                rrectangle.rect.left   = origin.x - 5;
                rrectangle.rect.top    = origin.y - 5;
                rrectangle.rect.right  = origin.x + dimensions.width + 5;
                rrectangle.rect.bottom = origin.y + dimensions.height + 5;

                sheet_ptr->DrawRoundedRectangle( rrectangle , brush.Get() );
            }
        }
    };
}