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

   class line
   {
      private:
      
         using point = D2D1_POINT_2F;
      
         D2D1_POINT_2F              a      {};
         D2D1_POINT_2F              b      {};
      
         float                      width  {};
         ColorF                     colour { ColorF::Yellow };
         ComPtr< render_target >    sheet  {};
         ComPtr< ID2D1SolidColorBrush  >  brush  {};
         ComPtr< ID2D1StrokeStyle >       style  {};

      public:

         line( ComPtr< render_target > in_sheet , point in_a , point in_b ,
               float in_width = 1.0f , ColorF in_colour = ColorF::Yellow )
            : sheet( in_sheet ) , a( in_a ) , b( in_b ) ,
              width( in_width ) , colour( in_colour )
         {
            sheet->CreateSolidColorBrush( colour , brush.ReleaseAndGetAddressOf() );
            //factory->createStrokeStyle
         };

         void draw()
         {
            if( sheet.Get() )
               sheet->DrawLine( a, b, brush.Get() , width , style.Get() );
         }
   };

   class grid // : public drawable
   {
      private:
       
         using point = D2D1_POINT_2F;

         ComPtr< render_target > sheet {};
         D2D1_SIZE_F             size  {};
         D2D1_SIZE_F             cell_amount {};

         vector< line >          lines {};

      public:

         void initialise( ComPtr< render_target > in_sheet , D2D1_SIZE_F in_cell_amount )
         {
            sheet       = in_sheet;
            cell_amount = in_cell_amount;
            size        = sheet->GetSize(); // size in dips

            float cell_width  = size.width  / cell_amount.width;
            float cell_height = size.height / cell_amount.height;

            for( float x {} ; x <= size.width ; x += cell_width )
               for( float y {} ; y <= size.height ; y += cell_height )
               {
                  // horizontal
                  lines.emplace_back( sheet.Get() , point{ 0 , y } , point{ size.width , y } , 2.0f );
                  // vertical
                  lines.emplace_back( sheet.Get() , point{ x , 0 } , point{ x , size.height } , 2.0f );
               }
         };

         point cell( const uint column , const uint row )
         {
            float cell_width  = size.width  / cell_amount.width;
            float cell_height = size.height / cell_amount.height;

            point origin { column * cell_width , row * cell_height };

            return origin;
         }

         void draw()
         {
            for( auto & line : lines ) line.draw();
         }
   };

   class graphics
   {
      private:
         
         HWND                    window        {};
         ComPtr< ID2D1Factory >  factory       {};
         ComPtr< window_render_target > sheet  {};
         D2D1_SIZE_U             size          {};
         RECT                    rectangle     {};
         PAINTSTRUCT             paint         {};
         ColorF                  colour_clear  { 0.2f , 0.2f , 0.2f , 0.0f };
         HRESULT                 result        { E_FAIL };

      public:
      
         write text;
         grid  sheet_grid;

         void grid( D2D1_SIZE_F in_cell_amount )
         {
            sheet_grid.initialise(sheet.Get() , in_cell_amount );
         }

         void grid( float in_column_amount , float in_row_amount )
         {
            D2D1_SIZE_F cell_amounts { in_column_amount , in_row_amount };

            sheet_grid.initialise( sheet.Get() , cell_amounts );
         }

         void initialise( const HWND in_window )
         {
            window = in_window;
              //using no = !;

            D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , factory.ReleaseAndGetAddressOf() );

            GetClientRect( window , & rectangle );

            size = SizeU( rectangle.right , rectangle.bottom );

            result = factory->CreateHwndRenderTarget( RenderTargetProperties() ,
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
                  sheet_grid.draw();

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