#pragma once

// gameprogrammingpatterns.com/service-locator.html
#include "..\headers\service.h"
#include < unordered_map >
#include < any >

#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"
#include "..\headers\hid_usages.h"

namespace hid
{
    using namespace std;

    //class graphics_d2d;
    //class write_d2d;
    //class hid_usages;

    class locate
    {
        public:

            //template< typename service_type >
            static void add_service( service_identifier in_identifier , any in_service );
            
            //template< typename service_type >
            //static service_type get_service( service_identifier in_service );
            static graphics_d2d & graphics();
            static write_d2d    * write();
            static hid_usages   * usages();
            //static void add_service( service_identifier in_identifier , any in_service );
            //static any  get_service( service_identifier in_identifier );
            
            //static service & ( service_identifier in_identifier , service * = nullptr );

        private:

            static inline unordered_map< service_identifier , any > services {};
    };
}
          