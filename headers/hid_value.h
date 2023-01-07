#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\text_d2d.h"

#include <hidpi.h>

namespace hid
{
    class hid_value : public _HIDP_VALUE_CAPS
    {
        private:
            
            text information;

        public:

            void set_information_text();
            void set_text_position( const vertex & in_position )
            { information.set_position_top_left(in_position); }
            //float get_right();
            void operator = (const _HIDP_VALUE_CAPS & in_value);

            /*ushort get_report_index()            const { return report_index; }
            ushort get_report_amount()           const { return report_amount;   }
            ushort get_bit_field()               const { return bit_field;       }
            bool   get_is_absolute()             const { return is_absolute;     } // or relative
            ushort get_origin_usage()            const { return origin_usage;    }
            ushort get_origin_page()             const { return origin_page;     }
            bool   get_is_range()                const { return is_range;        }
            hid_range  get_usages_range()            const { return usages;          }
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