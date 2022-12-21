#pragma once

#include < windows.h >

#include "..\headers\direct_2d.h"
#include "..\headers\vertex.h"

namespace hid
{
    class gui_microsoft
    {
        private:
         
            //using  uint  = unsigned int;
            //using  ulong = unsigned long;

            //struct dimensions { int  width { 100 }; int  height { 100 }; };
            //struct vertex     { int  x     { 0 }; int  y      {}; };

            HINSTANCE  instance         {};
            LPWSTR     parameters       {};
            int        show_flags       { 0 };
         
            WNDCLASSEX window_class     {};
            HWND       window_principle {};
            HWND       parent_window    {};
            // unordered_map< identifier , window * > window_siblings;

            HMENU      menu        {};
            PCWSTR     title_text  { L"Precision multiple touch input" };
            UINT       class_style { CS_HREDRAW | CS_VREDRAW };
            DWORD      style       { WS_VISIBLE | WS_MAXIMIZE }; //WS_OVERLAPPEDWINDOW
            DWORD      style_extra {};//{ WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT };
    
         //WS_EX_LAYOUTRTL
         /*If( shell language ) == Hebrew, Arabic, or language supports reading order alignment
              window horizontal origin = on the right edge. // horizontal++ advance to the left.*/
         /*WS_EX_NOACTIVATE*/

            float      x                 { 0.5f }; // vertex
            float      y                 { 0.5f };
            float      client_width      { 0.2f };
            float      client_height     { 0.2f };

            dimensions desktop_size      {};
            uint       desktop_dpi       { 96 };
            dimensions client_size       { 1024 , 768 };
            uint       client_dpi        { 96 };
            dimensions client_size_half  {};
            vertex     position_top_left {};
            vertex     position_center   {};
            vertex     desktop_center    {};

            MSG        message {};
            
            static inline const wchar_t class_name [] { L"precision_input" };

            static inline gui_microsoft * this_pointer {}; //shared_pointer

            LRESULT result {};
            virtual LRESULT          message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
            static  LRESULT CALLBACK main_window_process( HWND window , UINT message , WPARAM w_param , LPARAM l_param );
          
            //void calculate_layout();

        //protected:

        public:
      
            gui_microsoft( void );
            gui_microsoft( const HINSTANCE in_instance , const LPWSTR in_parameters , const int in_show_flags );
            gui_microsoft( const gui_microsoft & copy );
            gui_microsoft( const gui_microsoft && move );

            gui_microsoft & operator = ( const gui_microsoft & assignment );
            gui_microsoft & operator = ( gui_microsoft && assigned_move );

            ~gui_microsoft();

            HWND get_window() const;
            int  message_loop();
            //uint dpi();
    };
}