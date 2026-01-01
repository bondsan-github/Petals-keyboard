#pragma once

#include "Custom types.h"

#include "Graphics\DWrite\Text.h"
#include "Input\HID\Usages.h"

#include <hidpi.h>
#include <string>

namespace HID
{
    class Device;

    class Value : public _HIDP_VALUE_CAPS , public Usages
    {
        private:
            
            Text         information {};
            std::wstring content {};
            ulong        value_unsigned { 0ul }; // = 0xffff'ffff
            long         value_signed { -1 };

            Device * device {};

        public:

            Value( Device * const in_device , _HIDP_VALUE_CAPS const & construct_value );

            void  set_position( Point position ) { information.position( position ); }
            void  append_text( std::wstring text ) { information.add( text ); }

            float right() const { return information.right(); }
            float top()   const { return information.top(); }

            void  update( RAWINPUT * in_raw_data );
            void  collect_information();
            void  update_information();

            //hid_device * device() const { return device; }
            long  value() const { return value_signed; }

            void  draw() { information.draw(); }
    };
}