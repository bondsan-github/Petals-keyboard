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
   using write_factory      = IDWriteFactory;
   using text_format        = IDWriteTextFormat;
   using text_layout        = IDWriteTextLayout;
   using brush_solid_colour = ID2D1SolidColorBrush;
   
   using colours            = ColorF;
   using point              = D2D1_POINT_2F;
   using trimming           = DWRITE_TRIMMING;

   //struct write_factory { inline static ComPtr< IDWriteFactory > factory {}; };

   class text //: public write_factory
   {
      ComPtr< write_factory >      factory {};
      ComPtr< render_target >      sheet   {};
      ComPtr< text_format >        format  {}; // simple version of text_layout
      ComPtr< brush_solid_colour > brush   {};
      ComPtr< text_layout >        layout  {};

      point                        origin  { 10.0f , 10.0f }; // top left
      wstring                      name    { L"Times New Roman" };
      float                        size    { 15.0f }; // MS "size * 96.0f/72.0f"
      colours                      colour  { ColorF::DarkSlateGray };
      wstring                      content {};

      // area.
      float width  { 300.0f };
      float height { 110.0f };
      float radius { 5.0f };

      D2D1_ROUNDED_RECT rrectangle {};

      public:

      text( ComPtr< write_factory >     in_factory           ,
            ComPtr< render_target >     in_sheet             ,
            const wstring               in_content = {}      ,
            const point                 in_origin  = {}      ,
            const float                 in_size    = { 15u } ,
            const colours               in_colour  = { ColorF::DarkSlateGray }
          )
      : factory( in_factory.Get() ) , sheet( in_sheet.Get() ) , content( in_content ) , 
        origin( in_origin) , size( in_size ) , colour( in_colour )
      {
         reset_format();
         reset_layout();
         reset_brush();
      }

      void reset_brush()
      {
         sheet->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );
      }

      void reset_format()
      {
          //result_win
         HRESULT result = factory->CreateTextFormat( name.c_str() ,
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
         factory->CreateTextLayout( content.c_str() ,
                                    content.size() ,
                                    format.Get() ,
                                    width ,
                                    height ,
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
           rrectangle.rect.top    = origin.y + 5;
           rrectangle.rect.right  = origin.x + width;
           rrectangle.rect.bottom = origin.y + height;

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

         void add( const wstring in_text , 
                   const point   in_origin = { 100.0f ,100.0f } ,
                   const float   in_size   = { 15u } ,
                   const colours in_colour = { ColorF::DarkSlateGray } )
         {            
            texts.emplace_back( factory , sheet , in_text , in_origin , in_size , in_colour);
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