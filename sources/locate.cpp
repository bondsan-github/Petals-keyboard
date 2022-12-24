#include "..\headers\locate.h"

#include < cassert >
//#include < unordered_map >
#include < any >

namespace hid
{

    //locate::locate( void ) { OutputDebugString( L"\n locate::constructor" ); }
    //locate::~locate( void ) { OutputDebugString( L"\n locate::de-constructor" ); }

    /*
    void locate::add_service( service_identifier in_identifier , any in_service )
    {
        services.emplace( in_identifier , in_service );
    }

    any locate::get_service( service_identifier in_identifier )
    {
        // assert  
        return services.find( in_identifier )->second;
    }
    */

    /*
    graphics_d2d & locate::graphics()
    {
        return any_cast< graphics_d2d & >( services.find( service_identifier::graphics )->second );
    }

    write_d2d * locate::write()
    {
        return any_cast< write_d2d * >( services.find( service_identifier::write )->second );
    }

    hid_usages * locate::usages()
    {
        return any_cast< hid_usages * >( services.find( service_identifier::usages )->second );
    }
    */
}