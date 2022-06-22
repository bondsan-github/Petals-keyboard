#pragma once

#include < windows.h >

namespace hid
{
   class gui_windows_ms
   {
      private:
         
         struct dimensions
         {
             float width {};
             float height {};
         };

         struct vertex
         {
             float x {};
             float y {};
         };

         using uint = unsigned int;

         HINSTANCE  instance          {};
         LPWSTR     parameters        {};
         int        show_flags        {};
         HWND       window_principle  {};
         HWND       parent_window     {};
         HMENU      menu              {};
         PCWSTR     title_text        { L"Precision multiple touch input" };
         DWORD      style             { WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE };
         DWORD      style_extra       { WS_EX_COMPOSITED | WS_EX_TRANSPARENT };
         WNDCLASSEX window_class      {};

         float      x                 { 0.5f };
         float      y                 { 0.5f };
         float      client_width      { 0.2f };
         float      client_height     { 0.2f };

         dimensions desktop_size      {};
         uint       desktop_dpi       { 96.0 };
         dimensions client_size       {};
         uint       client_dpi        { 96.0 };
         dimensions client_size_half  {};
         vertex     position_top_left {};
         vertex     position_center   {};
         vertex     desktop_center    {};

         MSG        message {};

         inline static const wchar_t class_name[] { L"precision_input" };

         static inline gui_windows_ms * this_pointer {};

                 LRESULT          result {};
         virtual LRESULT          message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
         static  LRESULT CALLBACK main_window_process( HWND window , UINT message , WPARAM w_param , LPARAM l_param );
         //void calculate_layout();

      public:
      
         void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );
         int  message_loop();

   }; // class windows

} // namespace hid