#pragma once

// gameprogrammingpatterns.com/service-locator.html
#include "..\headers\service.h"
#include < unordered_map >

namespace hid
{
    class locate
    {
        public:

            static void      add_service( service_identifier in_identifier , service * in_service );
            static service * get_service( service_identifier in_identifier );
            
            //static service & ( service_identifier in_identifier , service * = nullptr );

        private:

            static inline std::unordered_map< service_identifier , service * > services {};
    };
}
          