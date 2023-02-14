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

    void hid_collections::add_values( hid_device * const in_device , item_type in_type , _HIDP_VALUE_CAPS * in_values , uint in_size )
    {
        for( uint index{ 0 }; index < in_size; index++ )
        {
            uint       collection_index = in_values[ index ].LinkCollection;
            hid_value  value( in_device , in_values[ index ] );

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
        
        float spacer_y = static_cast< float >( client_size.bottom ) - in_device.get_text_bottom();
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
    
    uint hid_collections::get_contact_amount_maximum()
    {
        uint amount { 0 };

        for( auto & collection : collections )
        {
            //amount = collection.get_contact_amount_maximum();
            break;
        }

        return amount;
    }

    range hid_collections::get_resolution()
    {
        range touchpad_resolution {};
        range values;

        for( auto & collection : collections )
        {
            touchpad_resolution.minimum = collection.get_range( 0x01 , 0x30 , report_type::input , value_type::logical ).maximum;
            touchpad_resolution.maximum = collection.get_range( 0x01 , 0x31 , report_type::input , value_type::logical ).maximum;

            if( touchpad_resolution.minimum > 0 and touchpad_resolution.maximum > 0 ) break;
        }

        return touchpad_resolution;
    }
    /*
    uint hid_collections::get_contact_identifier()
    {
        uint amount{ 0 };

        for( auto & collection : collections )
        {
            amount = collection.get_contact_amount();
        }

        return amount;
    }

    uint hid_collections::get_x()
    {
        uint x { 0 };

        for( auto & collection : collections )
        {
            x = collection.get_x();
        }

        return x;
    }
    */
} // namespace hid
