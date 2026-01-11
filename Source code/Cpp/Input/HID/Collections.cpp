#include "Input\HID\Collections.h"

#include "Input\HID\Device.h"
#include "Input\HID\Item.h"
#include "Input\HID\Usages.h"

namespace HID
{
    void Collections::add_buttons( report_type type, button_caps * buttons, uint size )
    {
        for( uint index {0}; index < size; index++ )
        {
            uint   collection_index = buttons[ index ].LinkCollection;
            Button button( buttons[ index ] );

            switch( type )
            {
                case report_type::input:
                {
                    collections_.at( collection_index ).add_button( type, button );
                } break;

                case report_type::output:
                {
                    collections_.at( collection_index ).add_button( type, button );
                } break;

                case report_type::feature:
                {
                    collections_.at( collection_index ).add_button( type, button );
                } break;

            }
        }
    }

    void Collections::add_values( report_type type, value_caps * values, uint size )
    {
        for( uint index{ 0 }; index < size; index++ )
        {
            uint   collection_index = values[ index ].LinkCollection;
            Value  value( values[ index ] );

            switch( type )
            {
                case report_type::input:
                {
                    collections_.at( collection_index ).add_value( type, value );
                } break;

                case report_type::output:
                {
                    collections_.at( collection_index ).add_value( type, value );
                } break;

                case report_type::feature:
                {
                    collections_.at( collection_index ).add_value( type, value );
                }
            }
        }
    }

    void Collections::add_collection( collection_node * nodes , uint size )
    {
        collections_.resize( size );

        uint index {};

        for( auto & node : collections_ )
        {
            node = nodes[ index ];
            
            index++;

            //node.collect_information();
        }
    }

    
    uint Collections::contact_amount()
    {
        uint amount { 0 };

        for( auto & collection : collections_ )
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

        for( auto & collection : collections_ )
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
