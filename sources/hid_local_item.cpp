#include "..\headers\hid_local_item.h"   

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include < bitset >

namespace hid
{
    wstring hid_local_item::text()
    {
        wstring text;

        text += L"\npage\t: ";
        text += locate::usages().page( page );

        if( is_range )
        {
            text += L"\nusages\t: ";
        }
        else
        {
            text += L"\nusage\t: ";
            text += locate::usages().usage( page , usage );
        }

        text += L"\nreport\t: ";
        text += to_wstring( report );

        if( report_amount )
        {
            text += L"\nreport amount\t: ";
            text += report_amount;
        }

        if( bit_field )
        {
            text += L"\nbit field\t: ";
            text += bitset< 16 >( bit_field ).to_string< wchar_t , char_traits< wchar_t > , allocator< wchar_t > >();
        }

        //text += is_absolute; // or relative
        //text += has_strings;
        //text += has_designators;

        return text;
    };

} // namespace hid