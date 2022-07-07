#pragma once

#include "..\headers\direct_2d.h"

namespace hid
{
   class write_d2d
   {
       private:

           ComPtr< write_factory >         write    {};

           ComPtr< font_collection >       fonts    {};
           ComPtr< font_family >           family   {};
           ComPtr< font_collection_names > names    {};
           ComPtr< text_analyser >         analyser {};
           string                          locale   { L"en-us" };

           //vector< text > texts {};
      
       public:

           void initialise();
         
           text_format_pointer format( string        in_font    = L"Times New Roman"   ,
                                       font_collection_pointer in_collection = nullptr ,
                                       text_weight   in_weight  = text_weight::regular ,
                                       text_style    in_style   = text_style::normal   ,
                                       text_stretch  in_stretch = text_stretch::normal ,
                                       float         in_size    = 15.0f                ,
                                       string        in_locale  = L"en-us"             );

           text_layout_pointer layout( string              in_content                         ,
                                       text_format_pointer in_text_format                     ,
                                       dimensions          in_dimensions = { 200.0f , 200.0 } ); // pixels

           void add_text( string                in_content         = L"empty"             ,
                          vertex                in_position_center = { 0.5f , 0.5f }      , // dips 0..1
                           float                 in_size            = 15.0f                ,
                           text_weight           in_weight          = text_weight::regular ,
                           text_style            in_style           = text_style::normal   ,
                           text_stretch          in_stretch         = text_stretch::normal ,
                           colours               in_colour          = colours::Yellow      ,
                           dimensions            in_dimensions      = { 200.0f , 200.0 }   ,
                           string                in_font            = L"Times New Roman"   );

   }; // class write_d2d

} // namespace hid

//GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );