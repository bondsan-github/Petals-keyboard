#include "Input\HID\Collections.h"

#include "Input\HID\Device.h"
#include "Input\HID\Item.h"
#include "Input\HID\Usages.h"

#include "Application.h"

namespace HID
{
    Collections::Collections( Application & application )
    : application( application )
    {
    }

    void Collections::add_buttons( Device & device , Report_type type , const button_caps & buttons , uint size )
    //void add_buttons( Device * device, Report_type type, _HIDP_BUTTON_CAPS * buttons, uint size )
    {
        for( uint index{ 0 }; index < size; index++ )
        {
            uint   collection_index = buttons[ index ].LinkCollection;
            Button button( device, buttons[ index ] );

            switch( type )
            {
                case Report_type::input:
                {
                    collections.at( collection_index ).add_button( type, button );
                } break;

                case Report_type::output:
                {
                    collections.at( collection_index ).add_button( type, button );
                } break;

                case Report_type::feature:
                {
                    collections.at( collection_index ).add_button( type, button );
                } break;

            }
        }
    }

    // const Device & device
    void Collections::add_values( const Device * const device, Report_type type, _HIDP_VALUE_CAPS * values , uint size )
    {
        for( uint index{ 0 }; index < size; index++ )
        {
            uint   collection_index = values[ index ].LinkCollection;
            Value  value( device , values[ index ] );

            switch( type )
            {
                case Report_type::input:
                {
                    collections.at( collection_index ).add_value( type, value );
                } break;

                case Report_type::output:
                {
                    collections.at( collection_index ).add_value( type, value );
                } break;

                case Report_type::feature:
                {
                    collections.at( collection_index ).add_value( type, value );
                }
            }
        }
    }

    void Collections::add_collection( _HIDP_LINK_COLLECTION_NODE * nodes , uint size )
    {
        collections.resize( size );

        uint index{ 0 };

        for( auto & node : collections )
        {
            node = nodes[ index ];
            node.collect_information();
            index++;
        }
    }

    void Collections::calculate_positions( Device const & device )
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
    }
    
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
            touchpad_resolution.minimum = collection.get_range( 0x01 , 0x30 , Report_type::input , Item_type::logical ).minimum;
            touchpad_resolution.maximum = collection.get_range( 0x01 , 0x31 , Report_type::input , Item_type::logical ).maximum;

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
