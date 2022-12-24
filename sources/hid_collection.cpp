#include "..\headers\hid_collection.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

namespace hid
{
    //hid_collection::hid_collection() { OutputDebugString( L"\n hid_collection::default constructor" ); }
    //hid_collection::hid_collection( hid_collection & copy ) { OutputDebugString( L"\n hid_collection::copy constructor" );}
    /*
    hid_collection::hid_collection( hid_collection && in_move )
    {
        OutputDebugString( L"\n hid_collection::move constructor" );

        index = move( in_move.index );
        type = move( in_move.type );
        page = move( in_move.page );
        usage = move( in_move.usage );
        is_alias = move( in_move.is_alias );
        origin = move( in_move.origin ); // parent  
        siblings = move( in_move.siblings ); // children
        first = move( in_move.first ); // child     
        next = move( in_move.next ); // sibling 

        information = move( in_move.information);
    }
    */
    //hid_collection::~hid_collection() { OutputDebugString( L"\n hid_collection::de-constructor" ); }

    void hid_collection::set_information()
    {
        wstring text;

        text = L"index\t: ";
        text += to_wstring( get_index() );
        text += L"\ntype\t: ";
        //text += L"\nidentifier:\t ";
        //text += 
        text += hid_item_type_text.at( std::to_underlying( get_type() ) ); // c++23
        text += L"\npage\t: ";
        text += locate::get_usages().page( get_page() );
        text += L"\nusage\t: ";
        text += locate::get_usages().usage(get_page() , get_usage());

        if( siblings )
        {
            text += L"\nsibling amount\t: ";
            text += to_wstring( get_sibling_amount() );
        }

        if( origin )
        {
            text += L"\norigin\t: ";
            text += to_wstring( get_origin() );
        }

        if( next )
        {
            text += L"\nnext\t: ";
            text += to_wstring( get_next() );
        }

        if( first )
        {
            text += L"\nfirst\t: ";
            text += to_wstring( get_first() );
        }

        information.set_content( text );
    }
}