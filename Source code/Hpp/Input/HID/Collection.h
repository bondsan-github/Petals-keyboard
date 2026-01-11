#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Button.h"
#include "Input\HID\Value.h"
#include "Input\HID\Usages.h"
#include "Input\HID\Item.h"

#include <string>
#include <vector>
using std::vector;

namespace HID
{
    class Collection : public collection_node, public HID::Usages
    {
        protected:

            vector< HID::Button > input_buttons_;
            vector< HID::Value >  input_values_;

            vector< HID::Button > output_buttons_;
            vector< HID::Value >  output_values_;

            vector< HID::Button > feature_buttons_;
            vector< HID::Value >  feature_values_;

        public:

            //Collection() {};
            friend class Multiple_touch;

            void operator = ( const collection_node & );
            void operator = ( collection_node && ) noexcept;

            void add_button( report_type, HID::Button & );
            void add_value( report_type, HID::Value & );

            Range range( ushort page,
                         ushort usage,
                         report_type report_type,
                         Item_type item_type );

            //vector<hid_button> & input_buttons() { return input_buttons.begin(); }
            //uint get_contact_amount();
            //uint get_contact_identifier();
            //uint get_x();
            //uint get_y();
            
            void update( vector< uchar > & data );
            //void update( RAWINPUT * data );
            //void update( RAWHID in_raw_data );
            //void draw();
    };
}