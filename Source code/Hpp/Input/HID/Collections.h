#pragma once

#include "Custom types.h"

#include "Input\HID\Globals.h"
#include "Input\HID\Collection.h"

#include <vector>
#include <hidpi.h>

#include "Application.h"

namespace HID
{
    class Device;
    //class Application;

    class Collections
    {
        private:

            // collection of same device items 
            std::vector< Collection > collections;

            //float spacer { 120.0f };
            Application & application;

        public:

            Collections( Application & application );

            // do these add or replace existing?
            void collection( const _HIDP_LINK_COLLECTION_NODE & nodes, uint size );
            void calculate_positions( const Device & device );
           
            void add_buttons( const Device & device, Report_type type, const button_caps & buttons, uint size );
            void add_values(  const Device & device, Report_type type, const value_caps & value, uint size );

            uint contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            Range resolution();

            void update( const RAWINPUT & raw_data )
            //void update( RAWHID in_raw_data )
            {
                for( auto & collection : collections ) collection.update( raw_data );
            }

            void draw()
            {
                for( auto & collection : collections ) collection.draw();
            }
    };
}
