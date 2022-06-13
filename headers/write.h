#pragma once

#include < string >
#include < vector >

#include < wrl.h >
#include < memory >

#include < d2d1.h >
#include < dwrite.h >

#include "..\headers\globals.h"
#include "..\headers\shared_graphics.h"
#include "..\headers\shared_write.h"
#include "..\headers\text.h"

namespace hid
{
   using namespace D2D1;
   using namespace Microsoft::WRL;

   class write : public shared_write
   {
         ComPtr< IDWriteFactory > write_factory {};
         vector< text >           texts {};
      
      public:

         void initialise( )
         {

            HRESULT result = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED ,
                                                  __uuidof( IDWriteFactory ) ,
                                                  & write_factory            );

            write_ptr = make_shared<write>(this);
         }

         //IDWriteTextFormat format( wstring in_text , text_style , text_weight , size );
         IDWriteFactory * factory()
         {
             return write_factory.Get();
         }

         void add( wstring in_text                                , 
                   point   in_origin     = { 100.0f ,100.0f }     ,
                   float   in_size       = { 15u }                ,
                   colours in_colour     = { colours::Yellow }    ,
                   area    in_dimensions = { 150.0f , 100.0f }    ,
                   wstring in_font       = { L"Times New Roman" } )
         {            
             texts.emplace_back( in_text , in_origin , in_size , in_colour , in_dimensions , in_font );
         }

         rectangle_midpoints mid_points( uint index ) const
         {
             return texts.at( index ).mid_points();
         }

         void draw()
         {
             for( auto & _text : texts ) _text.draw();
         }

   }; // class direct_write

} // namespace hid

//GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );