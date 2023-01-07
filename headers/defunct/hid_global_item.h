#pragma once

#include "..\headers\custom_types.h"

#include "..\headers\hid_item.h"
#include "..\headers\hid_local_item.h"

namespace hid
{
    class hid_global_item : public hid_local_item
    {
        private:

            ushort     main_item     { 0 };

            ushort     bit_amount    { 0 };
            ulong      unit_exponent { 0 };
            ulong      unit          { 0 };  // unit type ?
            // wstring unit_string { L"-" };

            bool       has_null      { false };
            bool       is_absolute   { false }; // or relative

            limits     physical      { limits{ 0 , 0 } }; // physical_limit
            limits     logical       { limits{ 0 , 0 } }; // logical_limit

        public:

            hid_global_item();
            hid_global_item( const hid_global_item & in_copy );
            hid_global_item( hid_global_item && in_move ) noexcept;
            ~hid_global_item();

            hid_global_item & operator = ( const hid_global_item & assign_copy );
            hid_global_item & operator = ( hid_global_item && assign_move ) noexcept;

            void reset();

            void set_link_main_item         ( ushort in_link         ) { main_item        = in_link;          } // <= 0 else message error
            void set_bit_amount             ( ushort in_bit_amount   ) { bit_amount       = in_bit_amount;    } // <= 0
            void set_unit_exponent          ( ulong in_unit_exponent ) { unit_exponent    = in_unit_exponent; }
            void set_unit                   ( ulong in_unit          ) { unit             = in_unit;          }
            void set_has_null               ( bool in_has_null       ) { has_null         = in_has_null;      }
            void set_is_absolute            ( bool in_is_absolute    ) { is_absolute      = in_is_absolute;   }
            void set_physical_limit_minimum ( long in_limit_minimum  ) { physical.minimum = in_limit_minimum; }
            void set_physical_limit_maximum ( long in_limit_maximum  ) { physical.maximum = in_limit_maximum; }
            void set_logical_limit_minimum  ( long in_limit_minimum  ) { logical.minimum  = in_limit_minimum; }
            void set_logical_limit_maximum  ( long in_limit_maximum  ) { logical.maximum  = in_limit_maximum; }

            ushort get_link_main_item()         { return main_item; }
            ushort get_bit_amount()             { return bit_amount; }
            ulong  get_unit_exponent()          { return unit_exponent; }
            ulong  get_unit()                   { return unit; }
            bool   get_has_null()               { return has_null; }
            bool   get_is_absolute()            { return is_absolute ; }
            long   get_physical_limit_minimum() { return physical.minimum; }
            long   get_physical_limit_maximum() { return physical.maximum; }
            long   get_logical_limit_minimum()  { return logical.minimum; }
            long   get_logical_limit_maximum()  { return logical.maximum; }
    };

        // uint usages = identifiers_usage.maximum - identifiers_usage.minumum;
        //for( int index{} ; index < usages ; index++ )

} // namespace hid

