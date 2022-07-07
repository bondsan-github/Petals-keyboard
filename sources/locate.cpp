#include "..\headers\locate.h"

#include < cassert >
//#include < unordered_map >
#include < algorithm >

namespace hid
{
    void locate::add_service( service_identifier in_identifier , service * in_service )
    {
        services.emplace( in_identifier , in_service );
    }

    service & locate::get_service( service_identifier in_identifier )
    {
        // assert  
        return * services.find( in_identifier )->second;
    }

}