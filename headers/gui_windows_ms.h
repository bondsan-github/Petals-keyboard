#pragma once

namespace hid
{
   using namespace std;

   class gui_windows_ms
   {
      private:
         
         HINSTANCE  instance         {};
         LPWSTR     parameters       {};
         int        show_flags       {};
         HWND       window_principle {};
         HWND       parent_window    {};
         HMENU      menu             {};
         PCWSTR     title_text       { L"Precision multi-touch input" };
         DWORD      style            { WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE };
         DWORD      style_extra      { WS_EX_COMPOSITED | WS_EX_TRANSPARENT };
         WNDCLASSEX window_class     {};
         
         int      x      { CW_USEDEFAULT };
         int      y      { CW_USEDEFAULT };
         int      width  { CW_USEDEFAULT };
         int      height { CW_USEDEFAULT };
         
         MSG      message       {};

         inline static const wchar_t class_name[] { L"Precision input" };

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