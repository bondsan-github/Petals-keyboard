#include "Input\HID\Collections.h"

#include "Input\HID\Device.h"
#include "Input\HID\Item.h"
#include "Input\HID\Usages.h"

namespace HID
{
    void Collections::add_buttons( Device & device, report_type type, button_caps * buttons, uint size )
    {
        for( uint index {0}; index < size; index++ )
        {
            uint   collection_index = buttons[ index ].LinkCollection;
            Button button( device, buttons[ index ] );

            switch( type )
            {
                case report_type::input:
                {
                    collections.at( collection_index ).add_button( type, button );
                } break;

                case report_type::output:
                {
                    collections.at( collection_index ).add_button( type, button );
                } break;

                case report_type::feature:
                {
                    collections.at( collection_index ).add_button( type, button );
                } break;

            }
        }
    }

    void Collections::add_values( Device & device, report_type type, value_caps * values, uint size )
    {
        for( uint index{ 0 }; index < size; index++ )
        {
            uint   collection_index = values[ index ].LinkCollection;
            Value  value( device , values[ index ] );

            switch( type )
            {
                case report_type::input:
                {
                    collections.at( collection_index ).add_value( type, value );
                } break;

                case report_type::output:
                {
                    collections.at( collection_index ).add_value( type, value );
                } break;

                case report_type::feature:
                {
                    collections.at( collection_index ).add_value( type, value );
                }
            }
        }
    }

    void Collections::add_collection( _HIDP_LINK_COLLECTION_NODE * nodes , uint size )
    {
        collections.resize( size );

        uint index {};

        for( auto & node : collections )
        {
            node = nodes[ index ];
            
            index++;

            //node.collect_information();
        }
    }

    /*void Collections::calculate_positions(Device const & device)
    {
        Size client_size = application.get_client_size();
        
        float spacer_y = static_cast< float >( client_size.height() ) - device.bottom();

        spacer_y -= collections.front().get_height() * collections.size();
        spacer_y /=  collections.size() + 1 ;

        Point collection_position // spacing = screen_height - device_text.bottom / collection_amount
        {
            device.left(),
            device.bottom() + 60// + spacer_y
        };

        auto collection_itr = collections.begin();

        for( ; collection_itr < collections.end() ; collection_itr++ )
        {
            collection_itr->set_position( collection_position );

            collection_position.y( collection_position.y() + 160) ;//spacer_y; // search all collections for highest text bottom

            collection_itr->calculate_positions();
        }
    }*/
    
    uint Collections::contact_amount()
    {
        uint amount { 0 };

        for( auto & collection : collections )
        {
            //amount = collection.get_contact_amount_maximum();
            break;
        }

        return amount;
    }

    Range Collections::resolution()
    {
        Range touchpad_resolution {};
        //Range values {};

        for( auto & collection : collections )
        {
            touchpad_resolution.minimum = collection.range( 0x01, 0x30, report_type::input, Item_type::logical ).minimum;
            touchpad_resolution.maximum = collection.range( 0x01, 0x31, report_type::input, Item_type::logical ).maximum;

            if( touchpad_resolution.minimum > 0 and touchpad_resolution.maximum > 0 ) break;
        }

        return touchpad_resolution;
    }
    /*
    uint Collections::contact_identifier()
    {
        uint amount{ 0 };

        for( const auto & collection : collections )
        {
            amount = collection.get_contact_amount();
        }

        return amount;
    }

    uint Collections::x()
    {
        uint x { 0 };

        for( const auto & collection : collections )
        {
            x = collection.x();
        }

        return x;
    }
    */
} // namespace hid
