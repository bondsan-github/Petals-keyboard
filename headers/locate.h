#pragma once

// gameprogrammingpatterns.com/service-locator.html

#include < windows.h >
#include < cassert >
//#include < unordered_map >

namespace hid
{
    class graphics_d2d;
    class write_d2d;
    class hid_usages;

    class locate
    {
        public:

            static void       provide_window   ( HWND in_window );
            static void       provide_graphics ( graphics_d2d * in_graphics );
            static void       provide_write    ( write_d2d * in_write );
            static void       provide_usages   ( hid_usages * in_usages );

            static HWND           window   ();
            static graphics_d2d * graphics ();
            static write_d2d *    write    ();
            static hid_usages &   usages   ();
            
        private:

            static HWND           window_pointer;
            static graphics_d2d * graphics_pointer;
            static write_d2d    * write_pointer;
            static hid_usages   * usages_pointer;
    };
} // namespace hid
          