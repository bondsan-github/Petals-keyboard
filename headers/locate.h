#pragma once

// gameprogrammingpatterns.com/service-locator.html

#include "..\headers\hid_multiple_touch.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\hid_usages.h"
#include "..\headers\write_d2d.h"
#include "..\headers\gui_microsoft.h"
#include "..\headers\hid_devices.h"

namespace hid
{
    class locate
    {
        private:

        static inline hid_multiple_touch * application { nullptr };
        static inline gui_microsoft * windows{ nullptr };
        static inline graphics_d2d * graphics{ nullptr };
        static inline write_d2d * write{ nullptr };
        
        static inline hid_usages    * usages   { nullptr };
        static inline hid_devices * input_devices{ nullptr };

        public:

            ~locate();

            static void set_application( hid_multiple_touch * in_application )
            {
                application = in_application;
            }

            static hid_multiple_touch & get_application()
            {
                return *application;
            }

            static void set_input_devices( hid_devices * in_input_devices )
            {
                input_devices = in_input_devices;
            }

            static hid_devices & get_input_devices()
            {
                return *input_devices;
            }

            static void set_graphics( graphics_d2d * in_graphics ) 
            { 
                graphics = in_graphics;
            }

            static graphics_d2d & get_graphics() 
            {
                return *graphics;
            }

            static void set_usages( hid_usages * in_usages ) 
            { 
                usages = in_usages;
            }

            static hid_usages & get_usages() 
            {
                return *usages;
            }

            static void set_write( write_d2d * in_write ) 
            { 
                write = in_write;
            }

            static write_d2d & get_write() 
            {
                return *write;
            }

            static void set_windows( gui_microsoft * in_windows ) 
            {
                windows = in_windows;
            }

            static gui_microsoft & get_windows() 
            {
                return *windows;
            }

    }; // class locate

} // namespace hid