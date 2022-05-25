#pragma once

#include < string >
#include < d2d1.h >
#include < dwrite.h >

#include "globals.h"

namespace hid
{
   using namespace D2D1;

   class write
   {
         IDWriteFactory *       write_factory {};

         IDWriteTextFormat *    text_format  {}; // simple version of text_layout
         IDWriteTextLayout *    text_layout  {};
         wstring                text_name    { L"Times New Roman" };
         uint                   text_size    { 15 }; // MS "size * 96.0f/72.0f"
         DWRITE_TEXT_METRICS *  text_metrics {};
         ColorF                 text_colour  { ColorF::LightYellow };

         ID2D1SolidColorBrush * text_brush   {};

      public:

         write()
         {
            DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED ,
                                 __uuidof( write_factory ) ,
                                 reinterpret_cast< IUnknown ** >( &write_factory ) );

            //GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics

            // Set the font weight to bold for the first 5 letters.
            // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
            // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );

            write_factory->CreateTextFormat( text_name.c_str() ,
                                             0 ,
                                             DWRITE_FONT_WEIGHT_REGULAR ,
                                             DWRITE_FONT_STYLE_NORMAL ,
                                             DWRITE_FONT_STRETCH_NORMAL ,
                                             text_size ,
                                             L"en-uk" , // locale       
                                             & text_format );

            //text_format->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ); //DWRITE_TEXT_ALIGNMENT_LEADING
            text_format->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );

            DWRITE_TRIMMING trim {};
            trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;

            text_format->SetTrimming( & trim , 0 );

            //render_target->CreateSolidColorBrush( text_colour , &text_brush );
         }

         //write_factory->Release();

   }; // class direct_write

} // namespace hid