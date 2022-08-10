#include "..\headers\hid_collection.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

namespace hid
{
    wstring hid_collection::text()
    {
        wstring text;

        text = L"index\t: ";
        text += to_wstring( index );
        text += L"\ntype\t: ";
        //text += L"\nidentifier:\t ";
        //text += 
        text += hid_item_type_text.at( std::to_underlying( type ) ); // c++23
        text += L"\npage\t: ";
        text += locate::usages()->page( page );
        text += L"\nusage\t: ";
        text += locate::usages()->usage( page , usage );

        if( siblings )
        {
            text += L"\nsibling amount\t: ";
            text += to_wstring( siblings );
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
}