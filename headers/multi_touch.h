#pragma once

#include < d2d1.h >

#include "hid_device.h"
#include "hid_devices.h"

#include "..\headers\window.h"
#include "..\headers\text_box.h"

// 1. transparent full screen draw contacts

namespace hid 
{
   using namespace std;

   // one or more mutli-touch inputs for example touchpad , touchscreen. 
   class multi_touch : public window , public hid_devices
   {
      bool      display_information {};

      uint      row            {};
      uint      column         {};

      uint      index          {};

      uint      spacer_row { 20 };
      uint      spacer_column { 20 };
         
      public:

         multi_touch()
         {
            if( display_information )
            {
               if( input.empty() )
               {
                  text_box no_devices( L"no precision multi-touch devices found" );

                  no_devices.draw();
               }
               else
               {
                  for( auto & device : input )
                  {
                     // 
                     text_box device_text( device.text( item_type::device ) );

                     paint.text_box();
                  }
               }
            }
                  // input_modifiers  ( buttons , values , features ) 
                  // output_modifiers
                  // 
                  // press over force threshold for capital letter
                  // delay after press for context 
                  // combined movement is mouse // 

         }

   }; // class multi_touch


} // namespace hid


// this is not to re-invent the wheel simply add a spoke
// 
// touchpad HID - mouse + keyboard
// one finger navigation - mouse pointer | context | direct touch 
// two finger context
// ten finger 

/* references:
*    windows/driver samples/hid/hclient
*    www-user.tu-chemnitz.de/~heha/hsn/free.var , hidparse
*    stackoverflow.com
*    quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/
*    C++ How to program 10th edition , Deitel & Associates, Inc , ISBN-10: 0-13-444823-5 , ISBN-13: 978-0-13-444823-7
*/

//class value  {};

//class button
//{
//   private: // variables
//      HANDLE           device_pointer{};
//
//   public:
//
//      button( const HANDLE in_device_pointer ) : device_pointer( in_device_pointer )
//};

//class collection
//{
//   public:
//      collection( const PHIDP_PREPARSED_DATA in_data , const uint in_ammount )
//     // : preparsed_pointer( in_data ) , collection_amount( in_ammount )
//
//   private: // variables
//     
//      //HIDP_LINK_COLLECTION_NODE node {};
//      //PHIDP_PREPARSED_DATA                preparsed_pointer {};
//};
