#include "..\headers\hid_local_item.h"   

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include < bitset >

namespace hid
{
    hid_local_item::hid_local_item()
    {
        OutputDebugString( L"\n hid_local_item::constructor" );
        //usages = any_cast< hid_usages * >( locate::get_service( service_identifier::usages ) );
    }

    hid_local_item::~hid_local_item()
    {
        OutputDebugString( L"\n hid_local_item::de-constructor" );
    }

    void hid_local_item::set_information()
    {
        wstring text;

        text += L"index\t: ";
        text += to_wstring( get_index() );

        text += L"\npage\t: ";
        text += locate::get_usages().page(get_page());

        text += L"\norigin usage\t: ";
        text += locate::get_usages().usage( get_origin_page() , get_origin_usage() );

        text += L"\norigin page\t: ";
        text += locate::get_usages().page( get_origin_page() );

        if( get_is_range() )
        {
            text += L"\nusages\t: ";
            
            for( long usage = get_usages_range().begin ; usage < get_usages_range().end ; usage++ )
            {
                text += L"\nusage\t: ";
                text += locate::get_usages().usage(get_page() , usage);
            }
        }
        else
        {
            text += L"\nusage\t: ";
            text += locate::get_usages().usage(get_page() , get_usage());
        }

        text += L"\nreport\t: ";
        text += to_wstring( get_report_index() );

        if( get_report_amount() )
        {
            text += L"\nreport amount\t: ";
            text += get_report_amount();
        }

        if( get_is_absolute() ) text += L"\ndata is absolute";
        else                    text += L"\ndata is relative";

        if( get_bit_field() )
        {
            text += L"\nbit field\t: ";
            text += bitset< 16 >( get_bit_field() ).to_string< wchar_t , char_traits< wchar_t > , allocator< wchar_t > >();
        }

        // switch page 

        //text += has_strings;
        //text += has_designators;

        information.set_content( move( text ) );
    };
}