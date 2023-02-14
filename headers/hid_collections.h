#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\hid_globals.h"

#include "..\headers\hid_collection.h"

#include <vector>
#include <hidpi.h>

namespace hid {

    class hid_device;

    class hid_collections
    {
        private:

            // collection of same device items 
            std::vector<hid_collection> collections;

            //float collection_text_spacer { 120.0f };

        public:

            void add_collections( _HIDP_LINK_COLLECTION_NODE * in_nodes , uint in_size );
            void set_collections_positions( const hid_device & in_device );

            void add_buttons( hid_device * in_device , item_type in_type , _HIDP_BUTTON_CAPS * in_buttons , uint in_size );
            void add_values( hid_device * in_device , item_type in_type , _HIDP_VALUE_CAPS * in_value , uint in_size );

            uint get_contact_amount_maximum();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            range get_resolution();

            void update_input( RAWINPUT * in_raw_data )
            //void update( RAWHID in_raw_data )
            {
                for( auto & collection : collections ) collection.update_input( in_raw_data );
            }

            void draw()
            {
                for( auto & collection : collections ) collection.draw();
            }
    };
}
