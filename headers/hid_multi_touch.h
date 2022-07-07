#pragma once

#include "..\headers\hid_devices.h"
#include "..\headers\hid_usages.h"
#include "..\headers\gui_windows_ms.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"
#include "..\headers\grid_d2d.h"

//#define PRODUCT_HOME_BASIC;

namespace hid 
{
    class hid_multi_touch : public gui_windows_ms
    {  // one or more mutli-touch inputs for example touchpad , touchscreen. 
        private: 
            
            graphics_d2d graphics; // 1. transparent full screen draw contacts
            hid_usages   usages;
            write_d2d    write;
            hid_devices  input;
            grid_d2d     grid;
            PAINTSTRUCT  paint;

            virtual LRESULT message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter ) override;

        public:

            void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );
            int  begin();
    };

}
