#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\text_d2d.h"
#include "..\headers\hid_button.h"
#include "..\headers\hid_value.h"
#include "..\headers\hid_globals.h"

#include <string>
#include <vector>
#include <hidpi.h>

namespace hid
{
    class hid_device;

    class hid_collection : public _HIDP_LINK_COLLECTION_NODE
    {
        private:

            hid_device * device { nullptr };

            text_d2d information {};
            //float font_size{ 15.0f };
            //D2D1::ColorF font_colour { D2D1::ColorF::Yellow };
            //D2D1_SIZE_F layout_size { 200.0f, 80.0f };
            
            std::vector<hid_button> input_buttons{};
            std::vector<hid_value>  input_values{};

            std::vector<hid_button> output_buttons{};
            std::vector<hid_value>  output_values{};

            std::vector<hid_button> feature_buttons{};
            std::vector<hid_value>  feature_values{};

            vertex information_spacing { 15.0f, 15.0f }; // spacers

        public:

            hid_collection() {}
            hid_collection( hid_device * in_device ) : device( in_device ) {}
            void operator = ( const _HIDP_LINK_COLLECTION_NODE & in_node );
            void operator = ( _HIDP_LINK_COLLECTION_NODE && in_node ) noexcept;

            void set_item_positions();

            void add_button( item_type in_type , hid_button & in_button );
            void add_value( item_type in_type , hid_value & in_value );

            void set_information_text();
            void set_text_position( const vertex & in_position );
            
            vertex get_text_position()       const { return information.get_position_top_left(); }
            float get_text_height()          const { return information.get_formated_height();  }
            float get_text_position_right()  const { return information.get_right(); }
            float get_text_position_bottom() const { return information.get_bottom(); }
            float get_text_position_top()    const { return information.get_top(); }

            range get_range( const ushort & in_page ,
                               const ushort & in_usage ,
                               const report_type & in_report_type ,
                               const value_type & in_value_type );
            //std::vector<hid_button>::iterator get_input_buttons() { return input_buttons.begin(); }
            //uint get_contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            
            void update_input( RAWINPUT * in_raw_data );
            //void update( RAWHID in_raw_data );
            void draw() const;
    };
}