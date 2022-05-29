#pragma once

#include < string >
#include < vector >

#include < wrl.h >

#include < d2d1.h >
#include < dwrite.h >

#include "..\headers\globals.h"
#include "..\headers\write.h"

namespace hid
{
   using namespace std;
   using namespace D2D1;
   using namespace Microsoft::WRL;

   struct line
   {
      D2D1_POINT_2F              a     {};
      D2D1_POINT_2F              b     {};
      ComPtr< ID2D1Brush >       brush {};
      float                      width {};
      ComPtr< ID2D1StrokeStyle > style {};
   };

   class graphics// : public window_pointer
   {
      private:
         
         HWND window {};
         ComPtr< ID2D1Factory >  factory       {};
         
         ComPtr< ID2D1HwndRenderTarget > sheet {};
         D2D1_SIZE_F             size          {};

         PAINTSTRUCT             paint         {};
         ColorF                  colour_clear  { 0.2f , 0.2f , 0.2f , 0.0f };

      public:
      
         write text;

         void initialise( const HWND in_window )
         {
            window = in_window;
              //using no = !;

            D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , factory.ReleaseAndGetAddressOf() );

            RECT rectangle {};

            GetClientRect( window , & rectangle );

            D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

            HRESULT result = factory->CreateHwndRenderTarget( RenderTargetProperties() ,
                                                              HwndRenderTargetProperties( window , size ) ,
                                                              sheet.ReleaseAndGetAddressOf() );

            text.initialise( sheet.Get() );
         }

         void reset( )
         {
           
         }

         //void set_sheet( const ID2D1HwndRenderTarget * in_sheet )
            //sheets.emplace_back( window_ptr , size );

         void draw()
         {
            if( window )
            {
               BeginPaint( window , & paint );

               if( sheet.Get() )
               {
                  sheet->BeginDraw();

                  sheet->SetTransform( Matrix3x2F::Identity() );

                  sheet->Clear( colour_clear );

                  text.draw();

                  sheet->EndDraw();
               }
               else
               {
               }

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

               if( sheet.Get() ) sheet->Resize( size );

               //calculate_layout();

               InvalidateRect( window , 0 , false );
            }
         }
   };

} // namespace hid

 /*
         class sheet
         {
            enum class request_type { window_ptr , size };

            using window_ptr = ID2D1HwndRenderTarget *;
            using size    = D2D1_SIZE_F;

            window_ptr _sheet {};
            size    _size  {};

            public:

            sheet( window_ptr const in_sheet = {} , const size in_size = {} )
            : _sheet( in_sheet ) , _size( in_size )
            {}

            size    size()    const { return _size; }
            window_ptr window_ptr() const { return _sheet; }
         };
         */

         //vector< sheet > sheets {};