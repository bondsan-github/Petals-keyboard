#pragma once

#include < d2d1.h >

#include "hid_device.h"
#include "hid_devices.h"

#include "..\headers\main_window.h"
#include "..\headers\text_box.h"

// 1. transparent full screen draw contacts

namespace hid 
{
   using namespace std;

   class multi_touch : public main_window// one or more mutli-touch inputs for example touchpad , touchscreen. 
   {
      private: // variables

         struct line
         {
            D2D1_POINT_2F      a     {};
            D2D1_POINT_2F      b     {};
            ID2D1Brush      *  brush {};
            float              width {};
            ID2D1StrokeStyle * style {};
         };

         //vector< text_box >  text_boxes {};

         hid_devices          devices;
         vector< hid_device > input;

         uint      row{};
         uint      column{};

         D2D_RECT_F position{};

         uint      index{};

         uint      spacer_row{ 20 };
         uint      spacer_column{ 20 };
         
      private: // functions

         virtual void on_paint() override; // final

      public: // functions

         multi_touch()
         {
            input = devices.devices();
                        
            if( input.empty() ) 
            {
               add_text_box( L"no precision touchpads found" );
            }
            else
            {
               // draw_item_information()
               for( auto & device : input )
               {
                  wstring text { device.text( item_type::device ) };

                  add_text_box( text );
                  //text_boxes.emplace_back( in_string );


                  vector< item > items = device._items();

                  for( auto & item : items )
                  {
                     wstring text { item.text() };

                     add_text_box( text );
                  }

                  // input_modifiers  ( buttons , values , features ) 
                  // output_modifiers
                  // 
                  // press over force threshold for capital letter

                  //for(  )
               }
            }

            message_loop();

         } // default constructor

   }; // class multi_touch

   void multi_touch::on_paint()
   {
      create_resources();

         render_target_size = render_target->GetSize();

         BeginPaint( pointer , &paint );

         render_target->BeginDraw();
         render_target->SetTransform( Matrix3x2F::Identity() );
         render_target->Clear( colour_clear );

         if( text_boxes.empty() ) { }
         else
         {
            for( auto & box : text_boxes )
            {
               //box->draw();
            }
         }

         render_target->EndDraw();

         EndPaint( pointer , &paint );
   }

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
