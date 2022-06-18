#include "..\headers\hid_main_item.h"
//#include "..\headers\locate.h"
//#include "..\headers\hid_usages.h"

namespace hid
{
    wstring hid_main_item::text()
    {
        wstring text;

        text  = L"type\t: ";
        text += hid_item_type_text.at( to_underlying( type ) );
        text += L"\npage\t: ";
        text += locate::usages().page( page );
        text += L"\nusage\t: ";
        text += locate::usages().usage( page , usage );

        if( amount )
        {
            text += L"\nlink amount\t: ";
            text += to_wstring( amount );
        }

        if( origin )
        {
            text += L"\norigin\t: ";
            text += to_wstring( origin );
        }

        if( next )
        {
            text += L"\nnext\t: ";
            text += to_wstring( next );
        }

        if( first )
        {
            text += L"\nfirst\t: ";
            text += to_wstring( first );
        }

        return text;
    }

} // namespace hid