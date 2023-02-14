#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\text_d2d.h"
#include "..\headers\vertex.h"

#include <hidpi.h>

namespace hid
{
    class hid_device;

    class hid_button : public _HIDP_BUTTON_CAPS
    {
        private:

            bool on { false };
            text_d2d information;
            std::wstring content{};
            hid_device * device { nullptr };
            //_HIDP_BUTTON_CAPS capabilities {};

        public:

            hid_button( hid_device * in_device, const _HIDP_BUTTON_CAPS & in_button_capabilities );
            
            void set_information_text();
            void append_information_text( std::wstring in_text ) { information.add_content(in_text); }
            void set_text_position(const vertex & in_position ) { information.set_position_top_left(in_position); }
            void set_layout_size( const D2D1_SIZE_F & in_size ) { information.set_layout_size( in_size ); }

            vertex get_text_position() const { return information.get_position_top_left(); }
            float get_text_top() const { return information.get_top(); }
            float get_text_right() const { return information.get_right(); }
            float get_text_width() const { return information.get_formated_width();  }
            float get_text_height() const { return information.get_formated_height(); }
            
            void update( RAWINPUT * in_raw_data );
            void update_information_text();

            //void update( RAWHID in_raw_data );

            void draw() const { information.draw(); }

            /*
            ushort get_bit_field()               const { return BitField;       }
            bool   get_is_absolute()             const { return IsAbsolute;     } // or relative
            ushort get_origin_usage()            const { return origin_usage;    }
            ushort get_origin_page()             const { return origin_page;     }
            bool   get_is_range()                const { return is_range;        }
            hid_range  get_usages_range()            const { return usages;          }
            ushort  get_usage()            const { return usages;          }
            ushort get_data_identifier()         const { return data_identifier; }
            hid_range  get_data_identifiers()        const { return data_identifiers; }
            bool   get_has_strings()             const { return has_strings;     }
            ushort get_string_index()            const { return string;          } // HidD_GetIndexedString        
            hid_range  get_strings_range()           const { return strings;         }
            long   get_strings_index_begin()     const { return strings.begin; }
            long   get_strings_index_end()       const { return strings.end;   }
            bool   get_has_designators()         const { return has_designators; }
            ushort get_designator()              const { return designator;      } // describes body part recommended control. Index points to a designator in the Physical descriptor
            hid_range  get_designators_range()       const { return designators;     }
            long   get_designators_range_begin() const { return designators.begin;   }
            long   get_designators_range_end()   const { return designators.end;     }*/
    };
}