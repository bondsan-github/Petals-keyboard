module;

#include < d2d1.h >

export module multi_touch_module;

import std.core;

import globals;
import main_window_module;
import item_type_module;
import hid_device_module;
import hid_devices_module;
// 1. transparent full screen draw contacts

namespace hid 
{
   using namespace std;

   export class multi_touch : public main_window// one or more mutli-touch inputs for example touchpad , touchscreen. 
   {
      private: // variables

         

         class text_box : public d2d
         {
            //text_box() { }; // "If any non - default constructors are declared , the compiler doesn't provide a default constructor" 
            private:
            
               wstring           text       {};
               //IDWriteFactory *  factory    {};
               
               float             radius            {};
               D2D_RECT_F        rectagle          {};
               D2D1_ROUNDED_RECT rounded_rectangle {};

            public:

               text_box( wstring in_text ) : text( in_text ) 
               {
                  //write_factory->CreateTextLayout();
                  //GetMetrics();
               }

               void draw()
               {
                  //render_target->DrawTextLayout

                  //render_target->DrawRoundedRectangle( rrect , text_brush );
               }
         };

         vector< wstring > text_boxes {};

         void add_text_box( wstring in_string )
         {
            text_boxes.emplace_back( in_string );
         }

         hid_devices          devices;
         vector< hid_device > input;

         uint      row{};
         uint      column{};

         D2D_RECT_F position{};

         uint      index{};

         uint      spacer_row{ 20 };
         uint      spacer_column{ 20 };

         uint      width_device{ 250 };
         uint      height_device{ 100 };

         uint      width_item{ 200 };
         uint      height_item{ 100 };

         
      private: // functions

         virtual void on_paint() override; // final

      public: // functions

         multi_touch()
         {
            input = devices.devices();
                        
            if( input.empty() ) 
            {}
               //add_text_box( text_box( L"no precision touchpads found" , { 50 , 50 , 350 , 120 } ) );
            
            else
            {
               // draw_item_information()
               for( auto & device : input )
               {
                  wstring text { device.text( item_type::device ) };

                  add_text_box( text );



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
                  index++;
               }
            }

            message_loop();

         } // default constructor

   }; // class multi_touch

   void multi_touch::on_paint()
   {
      create_graphics_resources();

      if( SUCCEEDED( result ) )
      {
         render_target_size = render_target->GetSize();

         BeginPaint( pointer , &paint );

         render_target->BeginDraw();
         render_target->SetTransform( D2D1::Matrix3x2F::Identity() );
         render_target->Clear( colour_clear ); 

         //pRenderTarget->FillEllipse( ellipse , pBrush );
         //RectF()

         if( text_boxes.empty() ) { }
         else
         {
            for( auto & box : text_boxes )
            {
               //box->draw();
            }
         }

         result = render_target->EndDraw();

         if( FAILED( result ) || result == D2DERR_RECREATE_TARGET )
         {
            discard_graphics_resources();
         }

         EndPaint( pointer , &paint );
      }

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
