#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Button.h"
#include "Input\HID\Value.h"
#include "Input\HID\Usages.h"
#include "Input\HID\Item.h"

#include <string>
#include <vector>

namespace HID
{
    //class Device;

    class Collection : public HIDP_LINK_COLLECTION_NODE, public HID::Usages
    {
        private:

            //Device * device {};

            std::vector< HID::Button > input_buttons{};
            std::vector< HID::Value >  input_values{};

            std::vector< HID::Button > output_buttons{};
            std::vector< HID::Value >  output_values{};

            std::vector< HID::Button > feature_buttons{};
            std::vector< HID::Value >  feature_values{};

        public:

            //Collection() {};
            //Collection( Device * device ) : device( device ) {};

            void operator = ( const _HIDP_LINK_COLLECTION_NODE & );
            void operator = ( _HIDP_LINK_COLLECTION_NODE && ) noexcept;

            //void calculate_positions();

            void add_button( report_type, HID::Button & );
            void add_value( report_type, HID::Value & );

            Range range( ushort page,
                         ushort usage,
                         report_type report_type,
                         Item_type item_type );

            //std::vector<hid_button>::iterator get_input_buttons() { return input_buttons.begin(); }
            //uint get_contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            
            void update( RAWINPUT * data );
            //void update( RAWHID in_raw_data );
            //void draw();
    };
}