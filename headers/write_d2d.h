#pragma once

#include "..\headers\constants.h"
#include "..\headers\text_d2d.h"

#include < string >
#include < vector >
#include < wrl.h >
#include < dwrite.h >

namespace hid
{
   using namespace std;
   using namespace D2D1;
   using namespace Microsoft::WRL;

   using colours = ColorF;
   using area    = D2D_SIZE_F;

   class write_d2d
   {
       private:

           ComPtr< IDWriteFactory > write_factory {};
           vector< text >           texts         {};
      
       public:

           void initialise();
         
         //text_Format format( wstring in_text , text_style , text_weight , size );

           IDWriteFactory & factory();

           void add( wstring in_text ,
                     vertex   in_origin    = { 100.0f ,100.0f }       ,
                     float   in_size       = { 15u }                  ,
                     colours in_colour     = { ColorF::Yellow }       ,
                     area    in_dimensions = { 150.0f , 100.0f }      ,
                     wstring in_font       = { L"Times New Roman" }   );
         
           rect_vertex_mid middle_vertices( uint index );
         
           void draw();

   }; // class write_d2d

} // namespace hid

//GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );