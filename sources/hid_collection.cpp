#include "..\headers\hid_collection.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_item.h"

namespace hid
{
    void hid_collection::operator = ( const _HIDP_LINK_COLLECTION_NODE & in_node )
    {
        LinkUsage        = in_node.LinkUsage;
        LinkUsagePage    = in_node.LinkUsagePage;
        Parent           = in_node.Parent;
        NumberOfChildren = in_node.NumberOfChildren;
        NextSibling      = in_node.NextSibling;
        FirstChild       = in_node.FirstChild;
        CollectionType   = in_node.CollectionType;  // As defined in 6.2.2.6 of HID spec
        IsAlias          = in_node.IsAlias; // This link node is an alias of the next link node.
    }

    void hid_collection::set_information_text()
    {
        std::wstring text;

        text = L"collection\t: ";
        text += locate::get_usages().collection_type( CollectionType );
        text += L"\npage\t: ";
        text += locate::get_usages().page( LinkUsagePage );
        text += L"\nusage\t: ";
        text += locate::get_usages().usage( LinkUsagePage , LinkUsage );

        information.set_content( text );
        information.set_layout_size( { 200.0f, 100.0f } );
        information.set_font_size( 10.0f );
        information.set_font_colour( D2D1::ColorF::Yellow );
    }

    void hid_collection::set_text_position( const vertex & in_position )
    {
        information.set_position_top_left( in_position );
    }
}