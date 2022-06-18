#pragma once

namespace hid
{
   using namespace D2D1;
   using namespace Microsoft::WRL;

   class text;

   class write_d2d
   {

       private:

           ComPtr< IDWriteFactory > write_factory {};
           vector< text >           texts         {};
      
       public:

           void initialise();
         
         //text_Format format( wstring in_text , text_style , text_weight , size );

           IDWriteFactory * factory();

           void add( wstring in_text ,
                     point   in_origin     ={ 100.0f ,100.0f } ,
                     float   in_size       ={ 15u } ,
                     colours in_colour     ={ colours::Yellow } ,
                     area    in_dimensions ={ 150.0f , 100.0f } ,
                     wstring in_font       ={ L"Times New Roman" } );
         
           rect_points_mid middle_points( uint index );
         
           void draw();

   }; // class write_d2d

} // namespace hid

//GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );