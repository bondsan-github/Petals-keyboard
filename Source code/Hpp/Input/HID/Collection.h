#pragma once

#include "Custom types.h"
#include "Graphics\Size.h"
#include "Graphics\DWrite\Text.h"

#include "Source code/Hpp/Input/HID/HID_Globals.h"
#include "Source code/Hpp/Input/HID/HID_Button.h"
#include "Source code/Hpp/Input/HID/HID_Value.h"
#include "Source code/Hpp/Input/HID/HID_Usages.h"
#include "Source code/Hpp/Input/HID/HID_Item.h"

#include <string>
#include <vector>
#include <hidpi.h>

namespace HID
{
    class Device;

    class Collection : public _HIDP_LINK_COLLECTION_NODE , public Usages
    {
        private:

            Device * device { nullptr };

            Text information {};
            //float font_size{ 15.0f };
            //D2D1::ColorF font_colour { D2D1::ColorF::Yellow };
            //D2D1_SIZE_F layout_size { 200.0f, 80.0f };
            
            std::vector< Button > input_buttons{};
            std::vector< Value >  input_values{};

            std::vector< Button > output_buttons{};
            std::vector< Value >  output_values{};

            std::vector< Button > feature_buttons{};
            std::vector< Value >  feature_values{};

            Size spacing { 15, 15 }; // spacers

        public:

            Collection() {}
            Collection( Device * in_device ) : device( in_device ) {}

            void operator = ( const _HIDP_LINK_COLLECTION_NODE & in_node );
            void operator = ( _HIDP_LINK_COLLECTION_NODE && in_node ) noexcept;

            void calculate_positions();

            void add_button( Report_type in_type , Button & in_button );
            void add_value( Report_type in_type , Value & in_value );

            void collect_information();
            void set_position( Point const & in_position );
            
            Point get_position() const { return information.get_position(); }
            float get_height()   const { return information.height();  }
            float get_right()    const { return information.right(); }
            float get_bottom()   const { return information.bottom(); }
            float get_top()      const { return information.top(); }

            Range get_range( ushort in_page ,
                             ushort in_usage ,
                             Report_type in_report_type ,
                             Item_type in_item_type );

            //std::vector<hid_button>::iterator get_input_buttons() { return input_buttons.begin(); }
            //uint get_contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            
            void update( RAWINPUT * in_raw_data );
            //void update( RAWHID in_raw_data );
            void draw();
    };
}