#pragma once

#include < windows.h >
#include < string >

#include "..\headers\globals.h"
#include "..\headers\graphics.h"

namespace hid
{
   using namespace std;

   class window
   {
      private:
         
         HINSTANCE instance     {};
         LPWSTR    parameters   {};
         int       show_flags   {};

         HRESULT  result        { E_FAIL };

         HWND     window_ptr    {};
         
         HWND     parent_window {};
         HMENU    menu          {};
         PCWSTR   title_text    { L"Precision multi-touch input" };
         DWORD    style         { WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE };
         DWORD    style_extra   { WS_EX_COMPOSITED | WS_EX_TRANSPARENT };
         WNDCLASSEX window_class  {};
         
         int      x      { CW_USEDEFAULT };
         int      y      { CW_USEDEFAULT };
         int      width  { CW_USEDEFAULT };
         int      height { CW_USEDEFAULT };
         
         MSG      message       {};

         // long * ( uint , uint , uint )
         LRESULT message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
         inline static const wchar_t class_name[] = { L"Precision input" };

         static LRESULT CALLBACK main_window_process( HWND window , UINT message , WPARAM w_param , LPARAM l_param );
         //void          calculate_layout();

      public:
      
         void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );
         int message_loop();

         graphics paint;
   };

   void window::initialise( const HINSTANCE in_instance , const LPWSTR in_parameters , const int in_show_flags )
   {
      instance = in_instance; parameters = in_parameters; show_flags = in_show_flags;

      window_class.cbSize = sizeof( WNDCLASSEX );

      window_class.style = CS_HREDRAW | CS_VREDRAW;
      window_class.lpfnWndProc   = window::main_window_process;
      window_class.hInstance     = in_instance;//instance;//GetModuleHandle( 0 ); //instance that contains the window procedure for the class.
      window_class.lpszClassName = L"Precision input";//class_name;
      
      window_class.cbClsExtra    = 0; // extra bytes after structure
      window_class.cbWndExtra    = 0; // extra bytes following the window instance.
      window_class.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 ); //( HBRUSH ) ( COLOR_GRAYTEXT + 1 );		//brush_background;
      window_class.hCursor       = 0;
      window_class.hIcon         = 0;
      window_class.hIconSm       = 0;
      window_class.lpszMenuName  = 0;

      ATOM atom {};
      
      atom = RegisterClassEx( & window_class );
      
      //error( L"register class ex" );

      window_ptr = CreateWindowEx( WS_EX_COMPOSITED | WS_EX_TRANSPARENT,//style_extra ,
                                   L"Precision input",//class_name ,
                                   L"application",//title_text ,
                                   WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE,//style ,
                                   0,0,//x , y , 
                                   200,200,//CW_USEDEFAULT, CW_USEDEFAULT,//width , height ,
                                   0,//parent_window , 
                                   0,//menu ,
                                   in_instance,//instance ,
                                   this );


      if( window_ptr == nullptr ) error( L"create window ex" );

      paint.initialise( window_ptr );

      //ShowWindow( hWnd,SW_SHOWDEFAULT );
      //UpdateWindow( hWnd );
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

   // This is just used to forward Windows messages from a global window
   // procedure to our member function window procedure because we cannot
   // assign a member function to WNDCLASS::lpfnWndProc.

   LRESULT CALLBACK window::main_window_process( HWND in_window , UINT message , WPARAM w_param , LPARAM l_param )
   {
      window * this_ptr {};
      LRESULT  result   {};

      // If we are creating the window, set the window_ptr to the instance of CAppWindow associated with the window as the HWND's user data.
      // That way when we get messages besides WM_CREATE we can call the instance's WndProc and reference non-static member variables.

      if( message == WM_NCCREATE )
      {
         CREATESTRUCT * create_ptr = reinterpret_cast< CREATESTRUCT * >( l_param );

         this_ptr = static_cast< window * >( create_ptr->lpCreateParams );

         SetWindowLongPtr( in_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( this_ptr ) );

         //this_ptr->window_ptr = window_ptr;   
      }
      else
      {
         this_ptr = reinterpret_cast< window * >( GetWindowLongPtr( in_window , GWLP_USERDATA ) );

      }
    
      if( this_ptr )
      return this_ptr->message_handler( in_window , message , w_param , l_param );

      return DefWindowProc( in_window , message , w_param , l_param );
   }

   //window::~window()

   LRESULT window::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
   {
      switch( message )
      {
         case WM_CREATE:
         {
         } break;

         //WM_NCDESTROY

         case WM_DESTROY:
         {
            PostQuitMessage( 0 );
         } break;

         case WM_PAINT:
         {
            paint.draw();
         } break;
         
         // Other messages not shown...

         case WM_SIZE:
         {
            //paint.resize();
         } break;

         case WM_KEYDOWN:
         {
            switch( wParam )
            {
               case VK_ESCAPE:
               {
                  PostQuitMessage( 0 );//DestroyWindow( in_window );
               } break;

            }
         } 

      } // switch( message )

      return DefWindowProc( in_window , message , wParam , lParam );

   } // message_handler

} // namespace hid

//GetClassInfo( hInst , thisClassName , &wincl ))

//SetWindowPos
      //HMONITOR monitor = MonitorFromWindow( GetModuleHandle(0) , MONITOR_DEFAULTTONEAREST);
      //MONITORINFO monitor_info {};
      //GetMonitorInfo( monitor , & monitor_info );
      //S_OK