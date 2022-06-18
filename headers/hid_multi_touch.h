#pragma once

#include "..\headers\hid_devices.h"
#include "..\headers\gui_windows_ms.h"

#include "..\headers\hid_usages.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

// 1. transparent full screen draw contacts

namespace hid 
{
    using namespace std;

    // one or more mutli-touch inputs for example touchpad , touchscreen. 
    class hid_multi_touch : public hid_devices , public gui_windows_ms
    {
        private:
            
            hid_usages   usages;
            graphics_d2d graphics;
            write_d2d    write;

            virtual LRESULT message_handler( HWND in_window , UINT message , WPARAM w_parameter , LPARAM l_parameter ) override;

        public:

            void initialise( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );
            int begin();

    }; //class multi_touch

} // namespace hid
