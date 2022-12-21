#pragma once

#include "..\headers\constants.h"

#include "..\headers\hid_item.h"
#include "..\headers\hid_local_item.h"

namespace hid
{
    // value item
    class hid_global_item : public hid_local_item
    {
        private:

            link       main_item     { 0 };

            ushort     bit_amount    { 0 };
            ulong      unit_exponent { 0 };
            ulong      unit          { 0 }; 
            // wstring unit_string { L"-" };

            bool       has_null      { false };
            bool       is_absolute   { false }; // or relative

            limits     physical      { limits{ 0 , 0 } };
            limits     logical       { limits{ 0 , 0 } };

        public:

            void set_link_main_item         ( const link in_link           ) { main_item = in_link; } // >= 0 else message error
            void set_bit_amount             ( const ushort in_bit_amount   ) { bit_amount = in_bit_amount; } // >= 0
            void set_unit_exponent          ( const ulong in_unit_exponent ) { unit_exponent = in_unit_exponent; }
            void set_unit                   ( const ulong in_unit          ) { unit = in_unit; }
            void set_has_null               ( const bool in_has_null       ) { has_null = in_has_null; }
            void set_is_absolute            ( const bool in_is_absolute    ) { is_absolute = in_is_absolute; }
            void set_physical_limit_minimum ( const long in_limit_minimum  ) { physical.minimum = in_limit_minimum; }
            void set_physical_limit_maximum ( const long in_limit_maximum  ) { physical.maximum = in_limit_maximum; }
            void set_logical_limit_minimum  ( const long in_limit_minimum  ) { logical.minimum = in_limit_minimum; }
            void set_logical_limit_maximum  ( const long in_limit_maximum  ) { logical.maximum = in_limit_maximum; }

            link   get_link_main_item()         const { return main_item; }
            ushort get_bit_amount()             const { return bit_amount; }
            ulong  get_unit_exponent()          const { return unit_exponent; }
            ulong  get_unit()                   const { return unit; }
            bool   get_has_null()               const { return has_null; }
            bool   get_is_absolute()            const { return is_absolute ; }
            long   get_physical_limit_minimum() const { return physical.minimum; }
            long   get_physical_limit_maximum() const { return physical.maximum; }
            long   get_logical_limit_minimum()  const { return logical.minimum; }
            long   get_logical_limit_maximum()  const { return logical.maximum; }
    };

        // uint usages = identifiers_usage.maximum - identifiers_usage.minumum;
        //for( int index{} ; index < usages ; index++ )

} // namespace hid

