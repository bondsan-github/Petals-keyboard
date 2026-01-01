#pragma once

#include "Custom types.h"
#include "Input\HID\Usages.h"
#include "Graphics\DWrite\Text.h"

#include <hidpi.h>
#include <string>

namespace HID
{
    class Device;
    
    class Button : public button_caps, public Usages
    {
        private:

            bool on { false };

            Text         information;
            std::wstring content{};
            Device &     device;

            //button_caps capabilities {};

        public:

            Button( Device & device, const button_caps & button_capabilities );
            
            void collect_information();

            void append_text( std::wstring text ) { information.add( text ); }
            void set_position( Point const & position ) { information.position( position ); }
            void set_layout_size( D2D1_SIZE_F const & size ) { information.layout_size( size ); }

            Point position() const { return information.position(); }

            float top() const    { return information.top();    }
            float right() const  { return information.right();  }
            float width() const  { return information.width();  }
            float height() const { return information.height(); }
            
            void update( RAWINPUT * raw_data );
            void update_information();

            //void update( RAWHID in_raw_data );

            void draw() { information.draw(); }

            /*
            ushort      bit_field()               const { return BitField;       }
            bool        is_absolute()             const { return IsAbsolute;     } // or relative
            ushort      origin_usage()            const { return origin_usage;    }
            ushort      origin_page()             const { return origin_page;     }
            bool        is_range()                const { return is_range;        }
            hid_range   usages_range()            const { return usages;          }
            ushort      usage()                   const { return usages;          }
            ushort      data_identifier()         const { return data_identifier; }
            hid_range   data_identifiers()        const { return data_identifiers; }
            bool        has_strings()             const { return has_strings;     }
            ushort      string_index()            const { return string;          } // HidD_GetIndexedString        
            hid_range   strings_range()           const { return strings;         }
            long        strings_index_begin()     const { return strings.begin; }
            long        strings_index_end()       const { return strings.end;   }
            bool        has_designators()         const { return has_designators; }
            ushort      designator()              const { return designator;      } // describes body part recommended control. Index points to a designator in the Physical descriptor
            hid_range   designators_range()       const { return designators;     }
            long        designators_range_begin() const { return designators.begin;   }
            long        designators_range_end()   const { return designators.end;     }*/
    };
}