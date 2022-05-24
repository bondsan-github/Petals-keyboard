module;

#include < windows.h >

#include < d2d1.h >
#include < dwrite.h >

export module main_window_interface;

import std.core;

import globals;


namespace hid
{
   using namespace std;
   using namespace D2D1;

   /*using write_format   = IDWriteTextFormat;
   using write_factory  = IDWriteFactory;
   using window_surface = ID2D1HwndRenderTarget;
   using size_float     = D2D1_SIZE_F;*/

   export struct window
   {
      static HWND pointer;
   };

   export struct d2d
   {
      //static inline const IDWriteFactory * write_factory;
      static IDWriteFactory        * write_factory;
      static ID2D1Factory          * factory;
      static ID2D1HwndRenderTarget * render_target;
      static D2D1_SIZE_F             render_target_size;

   };
   
   export class main_window : public window , public d2d// abstract
   {
      protected:

         HWND     ptr_parent   {};
         HMENU    ptr_menu     {};
         //HWND     ptr_window   {};
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

         //IDWriteFactory *        write_factory      {};
         //static inline const IDWriteFactory * write_factory;

         PAINTSTRUCT             paint              {};
         ColorF                  colour_clear       { 0.2f , 0.2f , 0.2f , 0.0f };

         IDWriteTextFormat *     text_format        {}; // simple version of text_layout
         IDWriteTextLayout *     text_layout        {};
         wstring                 text_name          { L"Times New Roman" };
         uint                    text_size          { 15 }; // 10.0f * 96.0f/72.0f, 
         DWRITE_TEXT_METRICS *   text_metrics       {};
         ColorF                  text_colour        { D2D1::ColorF::LightYellow };
         ID2D1SolidColorBrush *  text_brush         {};

         //D2D1_RECT_U            placement;
         //D2D1_ELLIPSE           ellipse;

      //private: // functions
      protected:

         void          message_loop();
         LRESULT       message_handler( UINT uMsg , WPARAM wParam , LPARAM lParam );
         PCWSTR        class_name() const { return L"Precision input"; }

         static LRESULT CALLBACK main_window_process( HWND ptr_window , UINT message , WPARAM w_param , LPARAM l_param );

         HWND          handle_window() const { return pointer; }
         void          CalculateLayout();
         void          create_graphics_resources();
         void          discard_graphics_resources();

         virtual void  on_paint();// = 0;
         void          on_resize();

      public: // functions

         main_window();
         ~main_window();
   };

   main_window::main_window()//( HWND const in_ptr_parent ) : ptr_parent( in_ptr_parent )
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
      //message_loop();
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
      create_graphics_resources();

      //if( SUCCEEDED( result ) )
      //{
      render_target_size = render_target->GetSize();

      BeginPaint( pointer , &paint );

      render_target->BeginDraw();

      render_target->SetTransform( D2D1::Matrix3x2F::Identity() );

      render_target->Clear( colour_clear ); //D2D1::ColorF::DarkGrey ) );

      //pRenderTarget->FillEllipse( ellipse , pBrush );

      //result = 
      render_target->EndDraw();

      if( FAILED( result ) || result == D2DERR_RECREATE_TARGET )
      {
         discard_graphics_resources();
      }

      EndPaint( pointer , &paint );
      //}
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
   void main_window::CalculateLayout()
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

   void main_window::create_graphics_resources()
   {
      RECT rectangle;
      GetClientRect( pointer , & rectangle );

      D2D1_SIZE_U size = SizeU( rectangle.right , rectangle.bottom );

      d2d::factory->CreateHwndRenderTarget( RenderTargetProperties() ,
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
      //trim.delimiter = 0;
      //trim.delimiterCount = 0;

      text_format->SetTrimming( & trim , 0 );
                               
      render_target->CreateSolidColorBrush( text_colour , & text_brush );

      CalculateLayout();
   }

   ~main_window::main_window()
   {
      discard_graphics;
   }

   void main_window::discard_graphics_resources()
   {
      release( & text_brush );
      release( & render_target );
   }

   void main_window::on_resize()
   {
      if( render_target )
      {
         RECT rectangle;

         GetClientRect( pointer , & rectangle );

         D2D1_SIZE_U size = D2D1::SizeU( rectangle.right , rectangle.bottom );

         render_target->Resize( size );

         CalculateLayout();

         InvalidateRect( pointer , 0 , false );
      }
   }

   LRESULT main_window::message_handler( UINT message , WPARAM wParam , LPARAM lParam )
   {
      switch( message )
      {
         case WM_CREATE:
         {
            if( FAILED( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED , &factory ) ) )
               return -1;  // Fail CreateWindowEx.

            return 0;
         }

         case WM_DESTROY:
         {
            discard_graphics_resources();

            release( & write_factory );
            release( & factory );

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