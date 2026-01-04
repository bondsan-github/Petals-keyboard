#pragma once

// Use the C++ standard templated min/max
//#define NOMINMAX

// DirectX apps don't need GDI
//#define NODRAWTEXT
//#define NOGDI
//#define NOBITMAP

// Include <winsvc.h> if you need this
//#define NOSERVICE

// WinHelp is deprecated
//#define NOHELP

//#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "Aliases.h"
#include "Graphics\Size.h"
#include "Graphics\Point.h"
#include "Output\Logging.h"

#include <set>

class Application;

class MSWindows : public Logging
{
    private:
         
        HINSTANCE  instance         {};
        LPWSTR     parameters       {};
        int        show_flags       {};
        MSG        window_message   {};

        WNDCLASSEX window_class     {};
        HWND       window_principle {};
        HWND       parent_window    {};
        // unordered_map< identifier , window * > window_siblings;

        HMENU      menu                     {};
        PCWSTR     title_text               { L"Application" };
        UINT       class_style              { CS_HREDRAW | CS_VREDRAW }; // re-draw on size change
        UINT       class_style_transparent  { CS_HREDRAW | CS_VREDRAW };
        DWORD      window_style             { WS_OVERLAPPEDWINDOW };
        DWORD      window_style_transparent { WS_POPUP };
        DWORD      style_extra              { WS_EX_TOPMOST };
        
        //bool       transparent { true };
        bool       transparent { false };
        DWORD      style_extra_transparent { WS_EX_NOREDIRECTIONBITMAP };

        bool fullscreen { false };
        //bool fullscreen { true };

        //WS_EX_LAYOUTRTL
        /*If( shell language ) == Hebrew, Arabic, or language supports reading order alignment
            window horizontal origin = on the right edge. // horizontal++ advance to the left.*/
        /*WS_EX_NOACTIVATE*/

        PAINTSTRUCT paint {};

        Size  desktop_size       {};
        uint  desktop_dpi        {};
        Size  client_size_       {};
        uint  window_dpi         { 96 };
        Point position_top_left  { 100,100 };
        Point position_center    {};
        Point desktop_center     {};
            
        static const inline wchar_t class_name [] { L"App" };

        LRESULT result { 0 };

        //static long long __stdcall message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
        static LRESULT CALLBACK message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter );
        //void calculate_layout();

        //static MSWindows * class_pointer;

        uint error_code = 0xffff'ffff; //max unsigned int 4294967295

        Application * application {};

        //EnumWindows()

        std::set<RECT> window_recangles {};

        //void window_rectangles();

        //static BOOL CALLBACK enumerate_windows( HWND window , LPARAM parameter );

    protected:
        
        //static Size client_size;
        //friend class Graphics;

    public:
      
        MSWindows( Application * application );
        //MSWindows() = default;

        ~MSWindows();

        HWND initialise( Size client_size );
        //void initialise( Application * application );
        //void initialise( Application * application );
        // ( HINSTANCE instance , LPWSTR parameters , int show_flags );
        
        MSWindows( const MSWindows & copy )                     = delete;
        MSWindows( const MSWindows && move )                    = delete;
        MSWindows & operator = ( const MSWindows & assignment ) = delete;
        MSWindows & operator = ( MSWindows && assigned_move )   = delete;
            
        void window_size_changed( uint width , uint height );
         
        RECT client_position(); // Point position() const;
        Size client_size();    //  Size  size() const;

        HWND window();
        
        int message_loop();

        //uint dpi();

        void register_input_device( ushort page , ushort usage );
};
