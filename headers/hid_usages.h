#pragma once

#include "..\headers\constants.h"
#include < string >
#include < vector >

namespace hid
{
   using namespace std;

   class hid_usages
   {
      public:
         
         void    initialise();
         wstring page  ( uint in_page ) const;
         wstring usage ( uint in_page , uint in_usage ) const;
         wstring type  ( uint in_page , int in_usage ) const;

      private:

         //stringstream stream;

         vector< wstring > pages  =// up to 0xFFFF
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
            L"digitisers" ,              // 0x0D ( aka digitizers ) i'm from england! :)
            L"haptics" ,                 // 0x0E
            L"physical input device" ,   // 0X0F
            // [ 0x0091 ] = L"arcade" ,  // c++20 array initialiser designator
            // [ 0x0092 ] = L"gaming device" ,
            // [ 0xFFF3 ] = L"microsoft bluetooth handsfree" , 
         };

         // hid 3.4.1
         enum class modifier_type
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
       
   };

}





