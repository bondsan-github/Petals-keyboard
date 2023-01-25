#pragma once

#include "..\headers\custom_types.h"

#include "..\headers\gui_microsoft.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"

#include "..\headers\hid_devices.h"
#include "..\headers\hid_usages.h"

//#define PRODUCT_HOME_BASIC;

namespace hid 
{
    class hid_multiple_touch  // one or more mutliple touch inputs for example touchpad , touchscreen. 
    {  
        private: 
            
            gui_microsoft window;
            graphics_d2d  graphics; // 1. transparent full screen draw contacts
            write_d2d     write;
            
            hid_usages    usages;
            hid_devices   input;

            //states state { states::running };

        public:

            hid_multiple_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags );

            //void start();
            //void update();
            //void set_state( states in_state ) { state = in_state; }
    };

}
