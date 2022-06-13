#pragma once

#include < string >
#include < vector >
#include < memory >

#include < wrl.h >
#include < d2d1.h >

#include "..\headers\globals.h"
//#include "..\headers\shared_graphics.h"
#include "..\headers\locate.h"

namespace hid
{
   using namespace std;
   using namespace D2D1;
   using namespace Microsoft::WRL;

   class graphics
   {
      private:
         
         HWND                    window        {};
         ComPtr< ID2D1Factory >  factory       {};
         ComPtr< ID2D1HwndRenderTarget > sheet {};
         D2D1_SIZE_U             size          {};
         RECT                    rectangle     {};
         PAINTSTRUCT             paint         {};
         colours                 colour_clear  { 0.2f , 0.2f , 0.2f , 0.0f };
         HRESULT                 result        { E_FAIL };

      public:
      
          //using ✎ = write;

          //write text; 
          /*
          void add_line( point a , point b , float width , colours colour )
          {
              lines.emplace_back( sheet.Get() , a , b , width , colour );
          }

          void grid( D2D1_SIZE_F in_cell_amount )
          {
              sheet_grid.initialise( sheet.Get() , in_cell_amount );
          }

          void grid( float in_column_amount , float in_row_amount )
          {
              D2D1_SIZE_F cell_amounts{ in_column_amount , in_row_amount };

              sheet_grid.initialise( sheet.Get() , cell_amounts );
          }
          */

          void initialise( const HWND in_window )
          {
              window = in_window;

              locate::provide(this);
              //graphics_ptr = make_shared<graphics>( this );
              //graphics_ptr = this;

              D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , factory.ReleaseAndGetAddressOf() ); //

              reset();
          }

          void reset()
          {
              GetClientRect( window , & rectangle );

              size = SizeU( rectangle.right , rectangle.bottom );

              factory->CreateHwndRenderTarget( RenderTargetProperties() ,
                                               HwndRenderTargetProperties( window , size ) ,
                                               sheet.ReleaseAndGetAddressOf() );
          }

          ID2D1HwndRenderTarget * sheet_pointer()
          {
              return sheet.Get();
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
                                    
                  //sheet_grid.draw();
                  //text.draw();

                  //for( auto & line : lines )
                  //   line.draw();

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