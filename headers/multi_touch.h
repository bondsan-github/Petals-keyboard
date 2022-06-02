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

         wstring     text_font     { L"Sitka" };
         float       text_size     { 10.0f };
         colours     text_colour   { colours::White };
         area        text_area     {};
         float       column        {};
         ushort      column_amount {};
         float       row           {};
         ushort      row_amount    {};

         uint        index         {};
     
      public:

        void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
        {
           main_window.initialise( instance , parameters , show_flags );
        }

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
                 column_amount = 15;
                 row_amount    = 12;

                 main_window.paint.grid( column_amount , row_amount );

                 auto & grid_ = main_window.paint.sheet_grid;
                 auto & write = main_window.paint.text;

                 text_area    = grid_.cell_size();
                  
                 column = 1;
                 row    = 1;

                 point device_position    = grid_.cell( column , row ); 
                 
                 row += 2;
                 point item_head_position = grid_.cell( column , row ); 
                 
                 column += 2;
                 point item_main_position = grid_.cell( column , row );

                 vector< hid_device >::const_reference device = input.devices().front();

                 //for( auto & device : input.devices() )
                 //{
                    // device
                    write.add( device.text_device() , device_position , text_size , text_colour , text_area , text_font );

                    // items
                    vector< wstring > item_texts { device.text_items() };
                    
                    // head_item
                    write.add( item_texts.front() , item_head_position , text_size , text_colour , text_area , text_font );
                    
                    vector< wstring >::const_iterator text = item_texts.begin();
                    
                    // second item
                    text++;

                    for( ; text != item_texts.end() ; text++ )
                    {  
                        write.add( * text , grid_.cell( column , row ) , text_size , text_colour , text_area );
                        row+=2;
                    }

                    column = 5;
                    row    = 3;
                    //point item_input_position = grid_.cell( column , item_head_position.y );

                    for( auto & text : device.text_input() )
                    {
                        write.add( text , grid_.cell( column , row ) , text_size , text_colour , text_area );
                        row+=2;
                    }

                 //} if devices input empty

              } 

           }// if display information

           return main_window.message_loop();
        }

   }; //class multi_touch

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
