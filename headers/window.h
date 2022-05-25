#pragma once

#include < windows.h >
#include < string >

#include "..\headers\globals.h"
#include "..\headers\graphics.h"

namespace hid
{
   using namespace std;
   using namespace D2D1;

   class window
   {
      HWND     pointer      {};
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

      graphics paint; 
      // draw()
      // resize()

      LRESULT       message_handler( UINT uMsg , WPARAM wParam , LPARAM lParam );
      PCWSTR        class_name() const { return L"Precision input"; }

      static LRESULT CALLBACK main_window_process( HWND ptr_window , UINT message , WPARAM w_param , LPARAM l_param );

      void          calculate_layout();

      public:

             window();

         int message_loop();
   };

   //( HWND const in_ptr_parent ) : ptr_parent( in_ptr_parent )

   window::window()
   {
      //GetClassInfo( hInst , thisClassName , &wincl ))

      window_class.lpfnWndProc   = window::main_window_process;
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
   }

   int window::message_loop()
   {
      while( GetMessage( & message , 0 , 0 , 0 ) )
      {
         TranslateMessage( & message );
         DispatchMessage( & message );
      }

      return message.message;
   }


   LRESULT CALLBACK window::main_window_process( HWND in_ptr_window , UINT message , WPARAM w_param , LPARAM l_param )
   {
      window * ptr_this{};

      if( message == WM_NCCREATE )
      {
         CREATESTRUCT * ptr_create = reinterpret_cast< CREATESTRUCT * >( l_param );

         ptr_this = static_cast< window * >( ptr_create->lpCreateParams );

         SetWindowLongPtr( in_ptr_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( ptr_this ) );

         ptr_this->pointer = in_ptr_window;
      }
      else
         ptr_this = reinterpret_cast< window * >( GetWindowLongPtr( in_ptr_window , GWLP_USERDATA ) );

      if( ptr_this )
         return ptr_this->message_handler( message , w_param , l_param );
      else
         return DefWindowProc( in_ptr_window , message , w_param , l_param );
   }

   //window::~window()

   LRESULT window::message_handler( UINT message , WPARAM wParam , LPARAM lParam )
   {
      switch( message )
      {
         case WM_CREATE:
         {
            return 0;
         }

         case WM_DESTROY:
         {

            PostQuitMessage( 0 );

            return 0;
         }

         case WM_PAINT:
         {
            paint.draw();

            return 0;
         }
         // Other messages not shown...

         case WM_SIZE:
         {
            paint.resize();
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