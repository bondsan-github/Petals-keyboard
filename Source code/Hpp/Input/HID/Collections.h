#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Collection.h"

#include <vector>

namespace HID
{
    class Collections
    {
        protected:

            std::vector< Collection > collections_; // collection of same device items 

        public:

            friend class Multiple_touch;

            Collections() {};

            void add_collection( collection_node * nodes, uint size );
           
           //remove device
            void add_buttons( report_type type, button_caps * buttons, uint size );
            void add_values(  report_type type, value_caps * values,   uint size );

            uint contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            Range resolution();

            void update( vector< uchar > & data )
            {
                for( auto & collection : collections_ ) collection.update( data );
            }
            //void update( RAWINPUT * raw_data )
            //void update( RAWHID in_raw_data )

           /* void draw()
            {
                for( auto & collection : collections ) collection.draw();
            }*/
    };
}
