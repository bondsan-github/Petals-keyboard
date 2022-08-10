#include "..\headers\hid_local_item.h"   

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include < bitset >

namespace hid
{
    wstring hid_local_item::text()
    {
        wstring text;

        text += L"index\t: ";
        text += to_wstring( index );

        text += L"\npage\t: ";
        text += locate::usages()->page( page );

        text += L"\norigin usage\t: ";
        text += locate::usages()->usage( origin_page , origin_usage );

        text += L"\norigin page\t: ";
        text += locate::usages()->page( origin_page );

        if( is_range )
        {
            text += L"\nusages\t: ";
            
            for( ushort usage = usages.begin ; usage < usages.end ; usage++ )
            {
                text += L"\nusage\t: ";
                text += locate::usages()->usage( page , usage );
            }
        }
        else
        {
            text += L"\nusage\t: ";
            text += locate::usages()->usage( page , usage );
        }

        text += L"\nreport\t: ";
        text += to_wstring( report_index );

        if( report_amount )
        {
            text += L"\nreport amount\t: ";
            text += report_amount;
        }

        if( is_absolute ) text += L"\ndata is absolute";
        else              text += L"\ndata is relative";

        if( bit_field )
        {
            text += L"\nbit field\t: ";
            text += bitset< 16 >( bit_field ).to_string< wchar_t , char_traits< wchar_t > , allocator< wchar_t > >();
        }

        // switch page 

        //text += has_strings;
        //text += has_designators;

        return text;
    };
}