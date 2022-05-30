#pragma once

#include < d2d1.h >

#include "hid_device.h"
#include "hid_devices.h"

#include "..\headers\windows.h"
#include "..\headers\hid_devices.h"

// 1. transparent full screen draw contacts

namespace hid 
{
   using namespace std;

   // one or more mutli-touch inputs for example touchpad , touchscreen. 
   class multi_touch //: public window , public hid_devices
   {
      window      main_window;
      hid_devices input;

      bool        display_information { true };
      
      float       text_size   { 15.0f };
      ColorF      text_colour { ColorF::White };
      float       column      {};
      float       row         {};
      uint        index       {};
     
     public:

         // multi_touch(

         void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
         {
            main_window.initialise( instance , parameters , show_flags );
         }

         //point placement( float column , float row )
           // return point { column * 100 , row * 100 };

         int start()
         {
            if( display_information )
            {
               if( input.devices().empty() )
               {
                  main_window.paint.text.add( L"no precision multi-touch devices found" );
               }
               else
               {
                  main_window.paint.grid( 10 , 5 );

                  auto & grid_ = main_window.paint.sheet_grid;
                  auto & text_ = main_window.paint.text;

                  column = 1;
                  row    = 0;
                  
                  point placement = grid_.cell( column , row );

                  for( auto & device : input.devices() )
                  {
                     text_.add( device.text_device() , placement , text_size , text_colour );

                     vector< wstring > item_texts { device.text_items() };

                     placement = grid_.cell( column , row );

                     for( auto & text : item_texts )
                     {              
                        //if( item->next ) // item->next.placement.
                        //   placement = { placement.x += 200, placement.y };

                        placement = grid_.cell( column , row += 1 );

                        // first is parent
                        text_.add( text , placement , text_size , text_colour );
                     }
                  }
               }
            }

            return main_window.message_loop();
         }

   }; // class multi_touch


} // namespace hid


// this is not to re-invent the wheel simply add a spoke
// 
// touchpad HID - mouse + keyboard
// one finger navigation - mouse window_ptr | context | direct touch 
// two finger context
// ten finger 

/* references:
*    windows/driver samples/hid/hclient
*    www-user.tu-chemnitz.de/~heha/hsn/free.var , hidparse
*    stackoverflow.com
*    quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/
*    C++ How to program 10th edition , Deitel & Associates, Inc , ISBN-10: 0-13-444823-5 , ISBN-13: 978-0-13-444823-7
*/

// input_modifiers  ( buttons , values , features ) 
                  // output_modifiers
                  // 
                  // press over force threshold for capital letter
                  // delay after press for context 
                  // combined movement is mouse // 
                  // 
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
