#include "..\headers\write_d2d.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\locate.h"

namespace hid
{
    //using namespace D2D1;

    void write_d2d::initialise()
    {

        HRESULT result = DWriteCreateFactory( static_cast< DWRITE_FACTORY_TYPE >( write_factory_type::shared ),
                                              __uuidof( write_factory ) ,
                                              & write );


        locate::provide_write( this );

        //  translated using local system local language identifiers
    }

    text_format_pointer write_d2d::format( string       in_font ,
                                           font_collection_pointer in_collection ,
                                           text_weight  in_weight  ,
                                           text_style   in_style   ,
                                           text_stretch in_stretch ,
                                           float        in_size    ,
                                           string       in_locale  )
    {
        text_format_pointer format {};

        HRESULT result = write->CreateTextFormat( in_font.c_str() ,
                                                  in_collection.Get() ,
                                                  static_cast< font_weight  >( in_weight  ),
                                                  static_cast< font_style   >( in_style  ) ,
                                                  static_cast< font_stretch >( in_stretch ) ,
                                                  in_size ,
                                                  in_locale.c_str() ,
                                                  format.ReleaseAndGetAddressOf() );

        //format->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ); // _LEADING
        format->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );

        //trimming trim{};
        //trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;
        //format->SetTrimming( & trim , 0 );

        return format;
    }

    text_layout_pointer write_d2d::layout( string              in_content ,
                                           text_format_pointer in_format ,
                                           dimensions          in_dimensions ) // pixels * dpi
    {
        text_layout_pointer layout {};

        write->CreateTextLayout( in_content.c_str() ,
                                 in_content.size() ,
                                 in_format.Get() ,
                                 in_dimensions.width ,
                                 in_dimensions.height ,
                                 layout.ReleaseAndGetAddressOf() );

        return layout;
    }

    void write_d2d::add_text( string                in_content         ,
                               vertex                in_position_center ,
                               float                 in_size            ,
                               text_weight           in_weight          ,
                               text_style            in_style           ,
                               text_stretch          in_stretch         ,
                               colours               in_colour          ,
                               dimensions            in_dimensions      ,
                               string                in_font )
    {
        font_collection_pointer collection  {};
        page_window_pointer     page        = locate::graphics().get_page();
        brush_pointer           brush       = locate::graphics().brush_solid( in_colour );
        text_format_pointer     text_format = format( in_font , 
                                                      collection.Get() ,
                                                      in_weight ,
                                                      in_style ,
                                                      in_stretch ,
                                                      in_size ,
                                                      locale );
        text_layout_pointer    text_layout = layout( in_content , text_format , in_dimensions );
        rectangle              area { 100.0f , 100.0f , 300.0f , 300.0f }; // page.center() +- 100.0f

        //texts.emplace_back()
        /*
        page->DrawTextLayout( in_position_center ,
                              text_layout.Get() ,
                              brush.Get() );
                         /* text_options ,
                         measuring_mode /*
        */
    }


} // namespace hid