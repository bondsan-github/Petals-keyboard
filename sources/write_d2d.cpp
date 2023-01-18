//http://www.computerofthetides.com/blog/2014/01/Character-Formatting-Extensions-with-DirectWrite.html

#include "..\headers\write_d2d.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\locate.h"
#include "..\headers\utility.h"

namespace hid
{
    //using namespace D2D1;

    write_d2d::write_d2d()
    {
        //OutputDebugString( L"write_d2d::default constructor\n" );
    }

    void write_d2d::initialise()
    {
        HRESULT result = DWriteCreateFactory( //DWRITE_FACTORY_TYPE_ISOLATED,
                                              DWRITE_FACTORY_TYPE_SHARED ,
                                              __uuidof( IDWriteFactory ),
                                              //& write );
                                              reinterpret_cast< IUnknown ** >( & write ) );
        locate::set_write( this );

        //https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/november/windows-with-c-exploring-fonts-with-directwrite-and-modern-c
        //English (United Kingdom)	en-GB	hex 0x809	decimal 2057
        /*wchar_t locale[LOCALE_NAME_MAX_LENGTH];
        VERIFY( GetUserDefaultLocaleName( locale , countof( locale ) ) );
        */
    }

    write_d2d::~write_d2d()
    {
        //if( write ) { write->Release(); write = nullptr; }
    }

    /*
    void write_d2d::get_format( IDWriteTextFormat * in_format ,
                                wstring              in_font_family_name ,
                                ComPtr< IDWriteFontCollection > in_font_collection ,
                                DWRITE_FONT_WEIGHT  in_font_weight ,
                                DWRITE_FONT_STYLE   in_font_style ,
                                DWRITE_FONT_STRETCH in_font_stretch ,
                                float               in_font_size ,
                                string              in_font_locale )
    {
        HRESULT result = write->CreateTextFormat( in_font_family_name.c_str() ,
                                                  nullptr , // in_font_collection // (NULL sets it to use the system font collection).
                                                  in_font_weight ,
                                                  in_font_style ,
                                                  in_font_stretch ,
                                                  in_font_size ,
                                                  in_font_locale.c_str() ,
                                                  & in_format );// address of pointer to COM object

        if( result == E_FAIL ) { error( L"create format error" ); }

        //format->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ); // _LEADING
        //format->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
        //trimming trim{};    //trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;     
        //format->SetTrimming( & trim , 0 );
    }
    */

    /*
    void write_d2d::get_layout( IDWriteTextLayout * in_layout,
                                string                      in_content ,
                                ComPtr< IDWriteTextFormat > in_format ,
                                D2D1_SIZE_F                 in_dimensions )// pixels * dpi
    {
        write->CreateTextLayout( in_content.c_str()   ,
                                 in_content.size()    ,
                                 in_format.Get()      ,
                                 in_dimensions.width  ,
                                 in_dimensions.height ,
                                 //in_layout.ReleaseAndGetAddressOf() );
                                 & in_layout ); 
    }
    */

} // namespace hid