#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
   class write_d2d
   {
       private:

           ComPtr< IDWriteFactory >         write    { nullptr };

           //ComPtr< IDWriteTextFormat > format;//{ nullptr };
           //ComPtr< IDWriteTextLayout > layout;// {nullptr };

           ComPtr< font_collection >       fonts    { nullptr };
           ComPtr< font_family >           family   { nullptr };
           ComPtr< font_collection_names > names    { nullptr };
           ComPtr< text_analyser >         analyser { nullptr };
           string                          locale   { L"en-us" }; // en-uk

       public:

            write_d2d();
            ~write_d2d();

           //void initialise();
         
            //IDWriteTextFormat * get_format( string        in_font    = L"Times New Roman"   ,
            ComPtr< IDWriteTextFormat > get_format(
                             string in_font    = L"Times New Roman" ,
                                              //ComPtr< font_collection > in_collection = { nullptr } ,
                                              //IDWriteFontCollection * in_collection = nullptr ,
                              DWRITE_FONT_WEIGHT in_weight = DWRITE_FONT_WEIGHT_NORMAL ,
                                              //font_weight   in_weight  = font_weight::regular ,
                              DWRITE_FONT_STYLE in_style = DWRITE_FONT_STYLE_NORMAL ,
                                              //font_style    in_style   = font_style::normal ,
                              DWRITE_FONT_STRETCH in_stretch = DWRITE_FONT_STRETCH_NORMAL ,
                                              //font_stretch  in_stretch = font_stretch::normal ,
                              float         in_size    = 15.0f ,
                              string        in_locale  = L"en-us" );

            IDWriteTextLayout * get_layout( string              in_content ,
                                            //text_format_pointer in_text_format ,
                                            IDWriteTextFormat * in_text_format,
                                            dimensions          in_dimensions = { 200.0f , 200.0f } ) const; // pixels
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