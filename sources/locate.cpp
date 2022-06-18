#include "..\headers\locate.h"

#include < cassert >
//#include < unordered_map >

namespace hid
{
    void locate::provide_window( HWND in_window )
    {
        window_pointer = in_window;
    }

    void locate::provide_graphics( graphics_d2d * in_graphics )
    {
        graphics_pointer = in_graphics;
    }

    void locate::provide_write( write_d2d * in_write )
    {
        write_pointer = in_write;
    }

    void locate::provide_usages( hid_usages * in_usage )
    {
        usages_pointer = in_usage;
    }


    HWND locate::window()
    {
        assert( window_pointer != nullptr );

        return window_pointer;
    }

    graphics_d2d * locate::graphics()
    {
        assert( graphics_pointer != nullptr );

        return graphics_pointer;
    }

    write_d2d * locate::write()
    {
        assert( write_pointer != nullptr );

        return write_pointer;
    }

    hid_usages & locate::usages()
    {
        assert( usages_pointer != nullptr );

        return * usages_pointer;
    }
}
            //static enum class service { window , graphics , text };
            //using service = void *;
            //static inline unordered_map< service , void * > services {};

            /*
            template< typename pointer_type >
            static void provide( pointer_type * in_service , service in_type )
            {
               services.emplace( static_cast< type >( in_service ) , in_type );
            }

            template< typename type >
            static type * request( service in_type )
            {
                assert( services.count( in_type ) );

                return services.find( in_type );
            }
            */

    //template< typename type = locate_type::window >
    //struct service { static type * service_pointer; };
    //static void provide( type in_service )
    // //service< locate_type::graphics> graphics_service;
    // //for( auto & service : serivces )
    //static vector< service > services;
