#pragma once

#include < string >

#include < d2d1.h >
#include < dwrite.h >

#include "..\headers\globals.h"

namespace hid
{
   using namespace D2D1;
   using namespace std;

   class graphics
   {
         HWND                    window      {};

         ID2D1Factory          * factory     {};

         ID2D1HwndRenderTarget * target      {};
         D2D1_SIZE_F             target_size {};

         PAINTSTRUCT paint                   {};
         ColorF      colour_clear { 0.2f , 0.2f , 0.2f , 0.0f };

         //write     text;

      public:
      
         graphics()
         {
            //using no = !;

            if( ! factory )
               D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , & factory );
         }

         void target( const HWND in_window )
         {
            window = in_window;

            RECT rectangle {};

            GetClientRect( window , & rectangle );

            D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

            factory->CreateHwndRenderTarget( RenderTargetProperties() ,
                                             HwndRenderTargetProperties( window , size ) ,
                                             & target );
         }

         //void text_box 

         virtual void draw()
         {
            if( window )
            {
               BeginPaint( window , & paint );

               target->BeginDraw();

               target->SetTransform( Matrix3x2F::Identity() );

               target->Clear( colour_clear );

               target->EndDraw();

               EndPaint( window , & paint );
            }
         }
                     
         void resize()
         {
            if( window )
            {
               RECT rectangle;

               GetClientRect( window , & rectangle );

               D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

               target->Resize( size );

               //calculate_layout();

               InvalidateRect( window , 0 , false );
            }
         }

         //factory->Release();
   };

} // namespace hid