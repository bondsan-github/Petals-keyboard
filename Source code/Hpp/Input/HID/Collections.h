#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Collection.h"

#include <vector>

namespace HID
{
    class Device;
    
    class Collections
    {
        private:

            // collection of same device items 
            std::vector< Collection > collections;

        public:

            Collections() {};

            void add_collection( _HIDP_LINK_COLLECTION_NODE * nodes, uint size );
           
            void add_buttons( Device & device, report_type type, button_caps * buttons, uint size );
            void add_values(  Device & device, report_type type, value_caps * values, uint size );

            uint contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            Range resolution();

            void update( RAWINPUT * raw_data )
            //void update( RAWHID in_raw_data )
            {
                for( auto & collection : collections ) collection.update( raw_data );
            }

           /* void draw()
            {
                for( auto & collection : collections ) collection.draw();
            }*/
    };
}
