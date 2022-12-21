#include "..\headers\write_d2d.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\locate.h"
#include "..\headers\utility.h"

namespace hid
{
    //using namespace D2D1;

    write_d2d::write_d2d()
    {
        OutputDebugString( L"\n write_d2d::default constructor" );

        HRESULT result = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED,//static_cast< DWRITE_FACTORY_TYPE >( write_factory_type::shared ),
                                              __uuidof( IDWriteFactory ),//write_factory ) ,
                                              & write );


        //locate::add_service( service_identifier::write , this );
        locate::set_write( this );

        //  translated using local system local language identifiers
    }

    write_d2d::~write_d2d()
    {
        OutputDebugString( L"\n write_d2d::de-constructor" );
        
        if( write    ) write.Reset();
        if( fonts    ) fonts.Reset();
        if( family   ) family.Reset();
        if( names    ) names.Reset();
        if( analyser ) analyser.Reset();
        //write.Reset();
    }

    IDWriteTextFormat * write_d2d::get_format( string       in_font ,
                                               //ComPtr< font_collection > in_collection ,//font_collection_pointer in_collection ,
                                               //IDWriteFontCollection & in_collection ,
                                               DWRITE_FONT_WEIGHT in_weight ,//font_weight  in_weight  ,
                                               DWRITE_FONT_STYLE in_style , //font_style   in_style   ,
                                               DWRITE_FONT_STRETCH in_stretch ,//font_stretch in_stretch ,
                                               float        in_size    ,
                                               string       in_locale  ) const
    {
        HRESULT result = write->CreateTextFormat( in_font.c_str() ,
                                                  nullptr ,
                                                  in_weight ,
                                                  in_style ,
                                                  in_stretch ,
                                                  in_size ,
                                                  in_locale.c_str() ,
                                                  format.GetAddressOf() );
                                                  //format.ReleaseAndGetAddressOf() );


        if( result == E_FAIL ) { error( L"create format error" ); }

        //format->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ); // _LEADING
        //format->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
        //trimming trim{};    //trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;        //format->SetTrimming( & trim , 0 );
        
        //OutputDebugString( L"\n write_d2d::format reference count" );
        //printf("\n write_d2d::format reference count : %d" , )
        // what is pointer de-referencing
        return format.Get();
    }

    IDWriteTextLayout * write_d2d::get_layout( string              in_content ,
                                               text_format_pointer in_format ,
                                               dimensions          in_dimensions ) const// pixels * dpi
    {

        write->CreateTextLayout( in_content.c_str()   ,
                                 in_content.size()    ,
                                 in_format.Get()      ,
                                 in_dimensions.width  ,
                                 in_dimensions.height ,
                                 layout.ReleaseAndGetAddressOf() );

        return layout.Get();
    }

    /*
    void write_d2d::add_text( string       in_content ,
                              vertex       in_position_center ,
                              float        in_size ,
                              font_weight  in_weight ,
                              font_style   in_style ,
                              font_stretch in_stretch ,
                              colours      in_colour ,
                              dimensions   in_boundry ,
                              string       in_font )
    {
        font_collection_pointer collection  {};
        //page_window_pointer page            = locate::get_graphics().get_page();
        //brush_pointer           brush       = locate::graphics().brush_solid( in_colour );
        text_format_pointer     text_format = get_format( in_font , 
                                                          collection.Get() ,
                                                          in_weight ,
                                                          in_style ,
                                                          in_stretch ,
                                                          in_size ,
                                                          locale );

        text_layout_pointer    text_layout = get_layout( in_content , text_format , in_boundry );
        rectangle              area { 100.0f , 100.0f , 300.0f , 300.0f }; // page.center() +- 100.0f

        //texts.emplace_back()
        
    }
    */


} // namespace hid