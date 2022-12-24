#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
   class write_d2d
   {
       private:

           IDWriteFactory *        write;

           //ComPtr< IDWriteTextFormat >     format;
           //ComPtr< IDWriteTextLayout >     layout;

           //ComPtr< font_collection >       fonts;
           //ComPtr< font_family >           family;
           //ComPtr< font_collection_names > names;
           //ComPtr< text_analyser >         analyser;
           string                          locale   { L"en-us" }; // en-GB

       public:

            write_d2d();
            //~write_d2d();
         
            void get_format( IDWriteTextFormat * in_format,
                             string              in_font_family_name    = L"Times New Roman" ,
                             ComPtr< IDWriteFontCollection > in_font_collection = nullptr ,
                             DWRITE_FONT_WEIGHT  in_font_weight = DWRITE_FONT_WEIGHT_NORMAL ,
                             DWRITE_FONT_STYLE   in_font_style = DWRITE_FONT_STYLE_NORMAL ,
                             DWRITE_FONT_STRETCH in_font_stretch = DWRITE_FONT_STRETCH_NORMAL ,
                             float               in_font_size    = 15.0f ,
                             string              in_font_locale  = L"en-us" );

            void get_layout( IDWriteTextLayout * in_layout ,
                             string              in_content ,
                             ComPtr< IDWriteTextFormat > in_text_format ,
                             D2D1_SIZE_F          in_dimensions ={ 200.0f , 200.0f } ); // pixels
           /*
           void add_text( string                in_content         = L"empty"             ,
                          vertex                in_position_center = { 0.5f , 0.5f }      , // dips 0..1
                          float                 in_size            = 8.0f                ,
                          font_weight           in_weight          = font_weight::regular ,
                          font_style            in_style           = font_style::normal   ,
                          font_stretch          in_stretch         = font_stretch::normal ,
                          colours               in_colour          = colours::Yellow      ,
                          dimensions            in_dimensions      = { 300.0f , 300.0 }   ,
                          string                in_font            = L"Times New Roman"   );
           */

   }; // class write_d2d

} // namespace hid

//GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );