#pragma once

#include "..\headers\custom_types.h"

#include <string>
#include <vector>

namespace hid
{
    class hid_usages
    {
        public:
         
            hid_usages();
            ~hid_usages();
            // copy and move 

            std::wstring page( const uint &in_page ); // const
            std::wstring usage( const uint &in_page , const uint &in_usage );
            std::wstring collection_type( const uint &in_type );
            //std::wstring type  ( uint in_page , int in_usage );

        private:

            const std::vector< std::wstring > pages
            {
                L"undefined" ,               // 0x00
                L"generic desktop" ,         // 0x01
                L"simulation controls" ,     // 0x02
                L"vr controls" ,             // 0x03
                L"sport controls" ,          // 0x04
                L"game controls" ,           // 0x05
                L"generic device controls" , // 0x06
                L"keyboard/keypad" ,         // 0x07
                L"LED" ,                     // 0x08
                L"buton" ,                   // 0x09
                L"ordinal" ,                 // 0x0A
                L"telephony" ,               // 0x0B
                L"consumer" ,                // 0x0C
                L"digitisers" ,              // 0x0D ( a.k.a. digitizers ) i'm from england! :)
                L"haptics" ,                 // 0x0E
                L"physical input device" ,   // 0X0F
                // [ 0x0091 ] = L"arcade" ,  // c++20 array initialiser designator
                // [ 0x0092 ] = L"gaming device" ,
                // [ 0xFFF3 ] = L"microsoft bluetooth handsfree" , 
                // [ 0xFFFF ]
            };

            // hid 6.2.2.6
            const enum class collection_type : unsigned int // char
            {
                physical ,                   // 0x00
                application ,                // 0x01
                logical ,                    // 0x02
                report ,                     // 0x03
                named_array ,                // 0x04
                usage_switch ,               // 0x05
                usage_modifier ,             // 0x06
                reserved_start       = 0x07 ,// 0x07
                //...
                reserved_end         = 0x7F ,// 0x7F
                vendor_defined_start = 0x80, // 0x80
                //...
                vendor_defined_end   = 0xFF  // 0xFF
            };

            //using _type = collection_type;
            //using _text = std::wstring;
            //std::pair< _type , _text >;
            const std::vector< std::wstring > collection_type_text
            {
                L"physical" ,             // 0x00
                L"application" ,          // 0x01
                L"logical" ,              // 0x02
                L"report" ,               // 0x03
                L"named_array" ,          // 0x04
                L"usage_switch" ,         // 0x05
                L"usage_modifier" ,       // 0x06
                L"reserved_start" ,       // 0x07
                //...
                L"reserved_end" ,         // (8)0x7F
                L"vendor_defined_start" , // (9)0x80
                //...
                L"vendor_defined_end"     // (10)0xFF
            };

            // hid 3.4.1
            const enum class modifier_type
            {
                undefined ,
                reserved ,
                linear_direct , // 
                linear_signed ,
                linear_distance ,
                on_off_signed ,
                on_off_off ,    // momentary
                on_off_static , // one shot
                named_array ,
                collection_physical ,
                collection_application ,
            };
       
    }; // class hid_usages

} // namespace hid





