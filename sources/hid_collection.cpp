#include "..\headers\hid_collection.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_item.h"

namespace hid
{
    hid_collection::hid_collection()
    {
        OutputDebugString( L"\n hid_collection::default constructor" );
    }
    
    hid_collection::hid_collection( const hid_collection & in_copy ) 
    {
        OutputDebugString( L"\n hid_collection::copy constructor" );

        if( this != &in_copy ) *this = in_copy;
    }

    hid_collection::hid_collection( hid_collection && in_move ) noexcept
    {
        OutputDebugString( L"\n hid_collection::move constructor" );

        if( this != &in_move ) *this = std::move( in_move );
    }

    hid_collection & hid_collection::operator = ( const hid_collection & assign_copy )
    {
        if( this != &assign_copy )
        {
            index    = assign_copy.index;
            type     = assign_copy.type;
            page     = assign_copy.page;
            usage    = assign_copy.usage;
            is_alias = assign_copy.is_alias;
            origin   = assign_copy.origin;   // parent  
            siblings = assign_copy.siblings; // children
            first    = assign_copy.first;    // child     
            next     = assign_copy.next;     // sibling 

            information = assign_copy.information;
        }

        return *this;
    }

    hid_collection & hid_collection::operator = ( hid_collection && assign_move ) noexcept
    {
        if( this != &assign_move )
        {
            index    = std::move( assign_move.index );
            type     = std::move( assign_move.type );
            page     = std::move( assign_move.page );
            usage    = std::move( assign_move.usage );
            is_alias = std::move( assign_move.is_alias );
            origin   = std::move( assign_move.origin ); // parent  
            siblings = std::move( assign_move.siblings ); // children
            first    = std::move( assign_move.first ); // child     
            next     = std::move( assign_move.next ); // sibling 

            information = std::move( assign_move.information );

            assign_move.reset();
        }

        return *this;
    }

    bool hid_collection::operator == ( const hid_collection & in_equality ) const
    {
        bool result{ false };

        if( type     == hid_item_type { in_equality.CollectionType } &&
            usage    == in_equality.LinkUsage &&
            page     == in_equality.LinkUsagePage &&
            origin   == in_equality.Parent &&
            siblings == in_equality.NumberOfChildren &&
            next     == in_equality.NextSibling &&
            first    == in_equality.FirstChild &&
            is_alias == in_equality.IsAlias
           ) result = true;

        return result;
    }

    hid_collection & hid_collection::operator = ( const HIDP_LINK_COLLECTION_NODE & in_node )
    {
        //new_item.index    = index;
        type     = hid_item_type{ in_node.CollectionType };
        page     = in_node.LinkUsagePage;
        usage    = in_node.LinkUsage;
        is_alias = in_node.IsAlias;
        siblings = in_node.NumberOfChildren;

        origin   = in_node.Parent;
        next     = in_node.NextSibling;
        first    = in_node.FirstChild;

        return *this;
    }

    void hid_collection::reset()
    {
        type     = hid_item_type::undefined;
        page     = 0; // -1
        usage    = 0; // -1
        is_alias = false;
        siblings = 0;

        origin   = 0; // -1
        next     = 0; // -1
        first    = 0; // -1
    }
    
    hid_collection::~hid_collection() 
    {
        OutputDebugString( L"\n hid_collection::de-constructor" );
    }

    void hid_collection::set_information()
    {
        std::wstring text;

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