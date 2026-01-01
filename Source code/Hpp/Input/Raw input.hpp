#pragma once

#include <windows.h>

#include "..\headers\custom_types.h"
#include "..\headers\hid_globals.h"
#include "..\headers\window_messages.h"
#include "..\headers\vertex.h"
//https://learn.microsoft.com/en-us/windows/win32/winmsg/using-windows
//https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features
namespace hid
{
    class graphics_d2d;

    class gui_microsoft
    {
        private:
         
            HINSTANCE  instance         { nullptr };
            LPWSTR     parameters       { nullptr };
            int        show_flags       { 0 };
            MSG        window_message   {};

            WNDCLASSEX window_class     {};
            HWND       window_principle { nullptr };
            HWND       parent_window    { nullptr };
            // unordered_map< identifier , window * > window_siblings;

            HMENU      menu        { nullptr };
            PCWSTR     title_text  { L"Precision multiple touch input" };
            UINT       class_style { CS_HREDRAW | CS_VREDRAW };
            //DWORD      style       { WS_VISIBLE | WS_MAXIMIZE }; 
            DWORD      style       { WS_VISIBLE | WS_MAXIMIZE | WS_DLGFRAME };//| WS_OVERLAPPEDWINDOW };
            DWORD      style_extra { 0l };//{ WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT };
    
         //WS_EX_LAYOUTRTL
         /*If( shell language ) == Hebrew, Arabic, or language supports reading order alignment
              window horizontal origin = on the right edge. // horizontal++ advance to the left.*/
         /*WS_EX_NOACTIVATE*/

            PAINTSTRUCT paint {};
            graphics_d2d * graphics { nullptr };

            float       x                 { 0.0f }; // vertex
            float       y                 { 0.0f };
            float       client_width      { 800.0f };
            float       client_height     { 600.0f };

            D2D1_SIZE_U desktop_size      {};
            uint        desktop_dpi       { 0 };

            D2D1_SIZE_F client_size       { 0.0f , 0.0f };
            uint        client_dpi        { 96 };

            D2D1_SIZE_F client_size_half  {};

            vertex      position_top_left {};
            vertex      position_center   {};
            vertex      desktop_center    {};
            
            static inline const wchar_t class_name [] { L"precision_input" };

            //static inline gui_microsoft * this_pointer {}; //unique_pointer

            LRESULT result { 0 };
            bool message_handled{ false };

            //LRESULT result {};
            static long long __stdcall message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
            static long long __stdcall window_setup( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
            //LRESULT WINAPI message_handler_thunk( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );
            //void calculate_layout();

            uint error_code = 0xffff'ffff; //max unsigned int 4294967295
            uint raw_input_size { 0 };

        public:
      
            gui_microsoft();
            void initialise( const HINSTANCE in_instance , const LPWSTR in_parameters , const int in_show_flags );
           
            gui_microsoft( const gui_microsoft & copy ) = delete;
            gui_microsoft( const gui_microsoft && move ) = delete;
            gui_microsoft & operator = ( const gui_microsoft & assignment ) = delete;
            gui_microsoft & operator = ( gui_microsoft && assigned_move ) = delete;
            
            void set_graphics( graphics_d2d * in_graphics ) { graphics = in_graphics; }
            RECT get_client_rectangle();

            void register_input_device( const page_and_usage & in_device )
            {
                RAWINPUTDEVICE device;
                device.usUsagePage = in_device.page;
                device.usUsage = in_device.usage;
                device.dwFlags = RIDEV_DEVNOTIFY; // | RIDEV_EXINPUTSINK | RIDEV_INPUTSINK // attached and detached
                device.hwndTarget = window_principle;

                RegisterRawInputDevices( &device, 1, sizeof( RAWINPUTDEVICE ) );
            }

            ~gui_microsoft();

            HWND get_window() const;
            void message_loop();
            //uint dpi();
    };
}