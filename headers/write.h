#pragma once

#include < string >
#include < vector >

#include < wrl.h >

#include < d2d1.h >
#include < dwrite.h >

#include "globals.h"

namespace hid
{
   using namespace D2D1;
   using namespace Microsoft::WRL;

   //using com_ptr = ComPtr<>;
   
   //struct write_factory { inline static ComPtr< IDWriteFactory > factory {}; };

   class text //: public write_factory
   {
      ComPtr< write_factory >      factory {};
      ComPtr< render_target >      sheet   {};
      ComPtr< text_format >        format  {}; // simple version of text_layout
      ComPtr< brush_solid_colour > brush   {};
      ComPtr< text_layout >        layout  {};

      wstring                      content    {};
      point                        origin     {}; // top left
      wstring                      font       { L"Times New Roman" }; // font family
      float                        size       { 15.0f }; // MS "size * 96.0f/72.0f"
      colours                      colour     { colours::DarkSlateGray };
      area                         dimensions {};
      rounded_rectangle            rrectangle {};
      float                        radius     { 5.0f };

      public:

      text( ComPtr< write_factory > in_factory                                ,
            ComPtr< render_target > in_sheet                                  ,
            wstring                 in_content    = {}                        ,
            point                   in_origin     = { 10.0f , 10.0f }         ,
            float                   in_size       = { 15u }                   ,
            colours                 in_colour     = { ColorF::DarkSlateGray } ,
            area                    in_dimensions = { 150.0f , 100.0f }       ,
            wstring                 in_font       = { L"Times New Roman" }    )
      : factory( in_factory.Get() ) , sheet( in_sheet.Get() ) , content( in_content ) , 
        origin( in_origin) , size( in_size ) , colour( in_colour ) , dimensions( in_dimensions )
      {
         reset_format();
         reset_layout();
         reset_brush();
      }

      rectangle mid_points() const
      {
         rectangle         temp {};
         rectangle_middles mid  {};

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
      }

      void reset_brush()
      {
         sheet->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );
      }

      void reset_format()
      {
          //result_win
         HRESULT result = factory->CreateTextFormat( font.c_str() ,
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
         factory->CreateTextLayout( content.c_str()   ,
                                    content.size()    ,
                                    format.Get()      ,
                                    dimensions.width  ,
                                    dimensions.height ,
                                    layout.ReleaseAndGetAddressOf() );
      }

      void add( const wstring in_string )
      {
         content += in_string;

         reset_layout();         
      }

      void draw()
      {
         if( sheet.Get() ) 
         {
           sheet->DrawTextLayout( origin, layout.Get() , brush.Get() );

           rrectangle.radiusX = rrectangle.radiusY = radius;

           rrectangle.rect.left   = origin.x - 5;
           rrectangle.rect.top    = origin.y - 5;
           rrectangle.rect.right  = origin.x + dimensions.width  + 5;
           rrectangle.rect.bottom = origin.y + dimensions.height + 5;

           sheet->DrawRoundedRectangle( rrectangle , brush.Get() );
         }
      }
   };

   class write //: public write_factory
   {
         ComPtr< write_factory > factory {};
         ComPtr< render_target > sheet   {};
         vector< text >          texts   {};
      
      public:

         void initialise( ComPtr< render_target > in_sheet )
         {
            sheet = in_sheet.Get();

            HRESULT result = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED ,
                                 __uuidof( IDWriteFactory ) ,
                                 & factory );
         }

         void add(  wstring in_text                                   , 
                   point   in_origin     = { 100.0f ,100.0f }         ,
                   float   in_size       = { 15u }                    ,
                   colours in_colour     = { colours::DarkSlateGray } ,
                   area    in_dimensions = { 150.0f , 100.0f }        ,
                   wstring in_font       = { L"Times New Roman" }     )
         {            
            texts.emplace_back( factory , sheet , 
                                in_text , in_origin , in_size , in_colour , in_dimensions , in_font );
         }

         void draw()
         {
            if( sheet ) for( auto & _text : texts ) _text.draw();
         }

   }; // class direct_write

} // namespace hid

//GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );