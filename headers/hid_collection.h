#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\hid_item.h"
#include "..\headers\text_d2d.h"

#include <string>
#include <hidpi.h>

namespace hid
{
    class hid_collection : public _HIDP_LINK_COLLECTION_NODE
    {
        private:

            text          information;
            //float font_size{ 15.0f };
            //D2D1::ColorF font_colour { D2D1::ColorF::Yellow };
            //D2D1_SIZE_F layout_size { 200.0f, 80.0f };

        public:

            hid_collection() {}

            void operator = ( const _HIDP_LINK_COLLECTION_NODE & in_node );

            void set_information_text();
            void set_text_position(const vertex & in_position);

            vertex get_text_position() const { return information.get_position_top_left(); }
            float get_text_position_right() const { return information.get_right(); }
            float get_text_position_bottom() const { return information.get_bottom(); }
            float get_text_position_top() const { return information.get_top(); }

            void draw() const { information.draw(); }
            
    };
}