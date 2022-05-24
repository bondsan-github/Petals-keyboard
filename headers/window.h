#pragma once

#include < windows.h >
#include < string >
#include < d2d1.h >
#include < dwrite.h >

#include "globals.h"

namespace hid
{
   using namespace std;
   using namespace D2D1;

   class window
   {
      protected:
         inline static HWND pointer {};
   };

   class d2d
   {
      protected:
         inline static IDWriteFactory        * write_factory      {};
         inline static ID2D1Factory          * factory            {};
         inline static ID2D1HwndRenderTarget * render_target      {};
         inline static D2D1_SIZE_F             render_target_size {};

         IDWriteTextFormat    * text_format  {}; // simple version of text_layout
         IDWriteTextLayout    * text_layout  {};
         wstring                text_name    { L"Times New Roman" };
         uint                   text_size    { 15 }; // 10.0f * 96.0f/72.0f, 
         DWRITE_TEXT_METRICS  * text_metrics {};
         ColorF                 text_colour  { ColorF::LightYellow };
         ID2D1SolidColorBrush * text_brush   {};
   };

   class main_window : public window , public d2d
   {
      protected: // variables

         HWND     ptr_parent   {};
         HMENU    ptr_menu     {};
         PCWSTR   window_name  {};
         DWORD    style        { WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE };
         DWORD    style_extra  { WS_EX_COMPOSITED | WS_EX_TRANSPARENT };
         WNDCLASS window_class {};
         HRESULT  result       {};
         int      x_1          { CW_USEDEFAULT };
         int      y_1          { CW_USEDEFAULT };
         int      x_2          { CW_USEDEFAULT };
         int      y_2          { CW_USEDEFAULT };
         MSG      message      {};

         PAINTSTRUCT paint        {};
         ColorF      colour_clear { 0.2f , 0.2f , 0.2f , 0.0f };
         
      protected: // functions

         void          message_loop();
         LRESULT       message_handler( UINT uMsg , WPARAM wParam , LPARAM lParam );
         PCWSTR        class_name() const { return L"Precision input"; }

         static LRESULT CALLBACK main_window_process( HWND ptr_window , UINT message , WPARAM w_param , LPARAM l_param );

         HWND          handle_window() const { return pointer; }

         void          calculate_layout();

         void          create_resources();
         void          discard_resources();

         virtual void  on_paint();
         void          on_resize();
      
      public: // functions

         main_window();
         ~main_window();
   };

   //( HWND const in_ptr_parent ) : ptr_parent( in_ptr_parent )

   main_window::main_window() //: pointer(nullptr)
   {
      //GetClassInfo( hInst , thisClassName , &wincl ))

      window_class.lpfnWndProc   = main_window::main_window_process;
      window_class.hInstance     = GetModuleHandle( 0 );
      window_class.lpszClassName = class_name();
      //window_class.hbrBackground = (HBRUSH)0;

      RegisterClass( & window_class );

      //SetWindowPos
      //HMONITOR monitor = MonitorFromWindow( GetModuleHandle(0) , MONITOR_DEFAULTTONEAREST);
      //MONITORINFO monitor_info {};
      //GetMonitorInfo( monitor , & monitor_info );

      pointer = CreateWindowEx( style_extra ,
                                class_name() , window_name ,
                                style ,
                                x_1 , y_1 , x_2 , y_2 ,
                                ptr_parent , ptr_menu ,
                                GetModuleHandle( 0 ) , this );

      create_resources();
   }

   void main_window::message_loop()
   {
      while( GetMessage( & message , 0 , 0 , 0 ) )
      {
         TranslateMessage( & message );
         DispatchMessage( & message );
      }

      //return message.message;
   }

   void main_window::on_paint()
   {
      render_target_size = render_target->GetSize();

      BeginPaint( pointer , & paint );

      render_target->BeginDraw();
      
      render_target->SetTransform( Matrix3x2F::Identity() );
      
      render_target->Clear( colour_clear );

      render_target->EndDraw();

      EndPaint( pointer , & paint );
   }

   LRESULT CALLBACK main_window::main_window_process( HWND in_ptr_window , UINT message , WPARAM w_param , LPARAM l_param )
   {
      main_window * ptr_this{};

      if( message == WM_NCCREATE )
      {
         CREATESTRUCT * ptr_create = reinterpret_cast< CREATESTRUCT * >( l_param );

         ptr_this = static_cast< main_window * >( ptr_create->lpCreateParams );

         SetWindowLongPtr( in_ptr_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( ptr_this ) );

         ptr_this->pointer = in_ptr_window;
      }
      else
         ptr_this = reinterpret_cast< main_window * >( GetWindowLongPtr( in_ptr_window , GWLP_USERDATA ) );

      if( ptr_this )
         return ptr_this->message_handler( message , w_param , l_param );
      else
         return DefWindowProc( in_ptr_window , message , w_param , l_param );
   }

   // Recalculate drawing layout when the size of the window changes.
   void main_window::calculate_layout()
   {
      if( render_target )
      {
         D2D1_SIZE_F size = render_target->GetSize();

         //const float x = size.width / 2;
         //const float y = size.height / 2;
         //const float radius = min( x , y );
         //ellipse = D2D1::Ellipse( D2D1::Point2F( x , y ) , radius , radius );
      }
   }

   void main_window::create_resources()
   {
      RECT rectangle;
      GetClientRect( pointer , & rectangle );

      D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

      factory->CreateHwndRenderTarget( RenderTargetProperties() ,
                                       HwndRenderTargetProperties( pointer , size ) ,
                                       & render_target );

      DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED ,
                           __uuidof( write_factory ) ,
                           reinterpret_cast< IUnknown ** >( & write_factory ) );
      
      //GetMetrics( [ out ] DWRITE_TEXT_METRICS1 * textMetrics
      
      // Set the font weight to bold for the first 5 letters.
      // DWRITE_TEXT_RANGE textRange ={ 0, 5 };
      // pTextLayout_->SetFontWeight( DWRITE_FONT_WEIGHT_BOLD , textRange );

      write_factory->CreateTextFormat( text_name.c_str() ,
                                       0 ,
                                       DWRITE_FONT_WEIGHT_REGULAR ,
                                       DWRITE_FONT_STYLE_NORMAL ,
                                       DWRITE_FONT_STRETCH_NORMAL ,
                                       text_size ,
                                       L"en-uk" , // locale       
                                       & text_format );

      //text_format->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ); //DWRITE_TEXT_ALIGNMENT_LEADING
      text_format->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
      
      DWRITE_TRIMMING trim {};
      trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;

      text_format->SetTrimming( & trim , 0 );
                               
      render_target->CreateSolidColorBrush( text_colour , & text_brush );

      //CalculateLayout();
   }

   main_window::~main_window()
   {
      //discard_resources();
   }

   void main_window::discard_resources()
   {
      //release( & text_brush );
      //release( & render_target );
      //if(text_br )
      //if( render_target ) 
        // render_target->Release();
   }

   void main_window::on_resize()
   {
      if( render_target )
      {
         RECT rectangle;

         GetClientRect( pointer , & rectangle );

         D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

         render_target->Resize( size );

         calculate_layout();

         InvalidateRect( pointer , 0 , false );
      }
   }

   LRESULT main_window::message_handler( UINT message , WPARAM wParam , LPARAM lParam )
   {
      switch( message )
      {
         case WM_CREATE:
         {
            if( FAILED( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , & factory ) ) )
               return -1;  // Fail CreateWindowEx.

            return 0;
         }

         case WM_DESTROY:
         {
            discard_resources();

            //release( & write_factory );
            write_factory->Release();
            //release( & factory );
            factory->Release();

            PostQuitMessage( 0 );

            return 0;
         }

         case WM_PAINT:
         {
            on_paint();

            return 0;
         }
         // Other messages not shown...

         case WM_SIZE:
         {
            on_resize();
            return 0;
         }

         case WM_KEYDOWN:
         {
            switch( wParam )
            {
               case VK_ESCAPE:
               {
                  DestroyWindow( pointer );
                  return 0;
               }
            }
         }

      } // switch( message )

      return DefWindowProc( pointer , message , wParam , lParam );

   } // message_handler

} // namespace hid