#pragma once

// gameprogrammingpatterns.com/service-locator.html

#include <cassert>
#include "..\headers\graphics.h"

namespace hid
{
    class locate
    {
        public:

            static void provide( graphics * in_graphics )
            {
                graphics_pointer = in_graphics;
            }

            static graphics * get_graphics()
            {           
                assert( graphics_pointer != nullptr );

                return graphics_pointer;
            }
            
        private:

            static graphics * graphics_pointer;
    };
}

    //enum class locate_type { window , graphics , text };
    //template< typename type = locate_type::window >
    //struct service { static type * service_pointer; };
    //static void provide( type in_service )
    // //service< locate_type::graphics> graphics_service;
    // //for( auto & service : serivces )
    //static vector< service > services;
