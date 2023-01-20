#pragma once

#include "..\headers\hid_collections.h"
#include "..\headers\hid_device.h"
#include "..\headers\locate.h"

namespace hid
{
    void hid_collections::add_buttons( hid_device * in_device , item_type in_type , _HIDP_BUTTON_CAPS * in_buttons , uint in_size )
    {
        for( uint index{ 0 }; index < in_size; index++ )
        {
            uint       collection_index = in_buttons[ index ].LinkCollection;
            hid_button button( in_device , in_buttons[ index ] );

            switch( in_type )
            {
                case item_type::input:
                {
                    collections.at( collection_index ).add_button( in_type , button );
                } break;

                case item_type::output:
                {
                    collections.at( collection_index ).add_button( in_type , button );
                } break;

                case item_type::feature:
                {
                    collections.at( collection_index ).add_button( in_type , button );
                } break;

            }
        }
    }

    void hid_collections::add_values( hid_device * in_device , item_type in_type , _HIDP_VALUE_CAPS * in_value , uint in_size )
    {
        for( uint index{ 0 }; index < in_size; index++ )
        {
            uint       collection_index = in_value[ index ].LinkCollection;
            hid_value value( in_device , in_value[ index ] );

            switch( in_type )
            {
                case item_type::input:
                {
                    collections.at( collection_index ).add_value( in_type , value );
                } break;

                case item_type::output:
                {
                    collections.at( collection_index ).add_value( in_type , value );
                } break;

                case item_type::feature:
                {
                    collections.at( collection_index ).add_value( in_type , value );
                }
            }
        }
    }

    void hid_collections::add_collections( _HIDP_LINK_COLLECTION_NODE * in_nodes , uint in_size )
    {
        collections.resize( in_size );

        uint index{ 0 };

        for( auto & node : collections )
        {
            node = in_nodes[ index ];
            node.set_information_text();
            index++;
        }
    }

    void hid_collections::set_collections_positions( const hid_device & in_device )
    {
        RECT client_size = locate::get_windows().get_client_rectangle();
        
        ulong spacer_y = client_size.bottom - in_device.get_text_bottom();
        spacer_y -= collections.front().get_text_height() * collections.size();
        spacer_y /=  collections.size() + 1 ;

        vertex collection_position // spacing = screen_height - device_text.bottom / collection_amount
        {
            in_device.get_text_left() ,
            in_device.get_text_bottom() + 60.0f// + spacer_y
        };

        auto collection_itr = collections.begin();

        for( ; collection_itr < collections.end() ; collection_itr++ )
        {
            collection_itr->set_text_position( collection_position );

            collection_position.y += 160;//spacer_y; // search all collections for highest text bottom

            collection_itr->set_item_positions();
        }
    }

    uint hid_collections::contacts_maximum()
    {
        uint amount { 0 };

        for( auto collection : collections )
        {
            if( collection.contacts_maximum() > 0 )
            {
                amount = collection.contacts_maximum();
                break;
            }
        }

        return amount;
    }

} // namespace hid
