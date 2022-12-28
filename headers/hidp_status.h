#pragma once

#include <string>

namespace hid
{
   class hidp_status
   {
      public:

         std::string message( long in_code ) const
         {
            if( ( in_code >> 28 ) == 0x08 ) //0x80004400001
                return "null"; 

            else if( ( in_code & 0xff ) == 0x20 ) 
                return "not implemented"; // 

            else if( ( in_code & 0xff ) == 0x21 ) 
                return "not button array";

            else if( ( in_code & 0xff ) >= 0x00 && ( in_code & 0xff ) <= 0x20 ) 
                return messages[ in_code & 0xff ];

            else 
                return "unknown code";
         };

      private:

         const std::string messages[ 20 ]
         {
            "success" ,                // 00
            "invalid preparsed data" , // 01
            "invalid report type" ,    // 2
            "invalid report length" ,  // 3
            "usage not found" ,        // 4
            "value out of range" , // 5
            "bad log phy values" ,// 6
            "buffer to small" ,//7
            "internal error" ,//8
            "I8042 trans unknown" ,//9
            "incomplete report id" ,//a
            "not value array" ,//b
            "is value array" ,//c
            "data index not found" ,//d
            "data index out of range" ,//e
            "button not pressed" ,//f
            "report does not exist"// 0x10
         };

   }; // class hidp_status

} // namespace hid