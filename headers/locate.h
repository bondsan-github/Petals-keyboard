#pragma once

// gameprogrammingpatterns.com/service-locator.html
#include < unordered_map >
#include < any >
#include < memory >

#include "..\headers\graphics_d2d.h"
#include "..\headers\hid_usages.h"
#include "..\headers\write_d2d.h"
#include "..\headers\gui_microsoft.h"

namespace hid
{
    using namespace std;

    //enum class service_identifier { window , graphics , write , usages , grid }; // devices
    //using graphics = graphics_d2d;

    class locate
    {
        public:

            locate( void );
            ~locate( void );

            //static void add_service( service_identifier in_identifier , any in_service );
            //static any  get_service( service_identifier in_identifier );

            static void set_graphics( graphics_d2d * const in_graphics ) 
            { 
                OutputDebugString( L"\n locate::set_graphics" );
                _graphics = in_graphics;//make_unique< graphics_d2d >( in_graphics );
            }

            static graphics_d2d & get_graphics() { return * _graphics; }

            static void set_usages( hid_usages * const in_usages ) 
            { 
                OutputDebugString( L"\n locate::set_usages" );
                _usages = in_usages;//make_unique< hid_usages >( in_usages );
            }

            static hid_usages & get_usages() { return * _usages; }//.get(); }

            static void set_write( write_d2d * const in_write ) 
            { 
                OutputDebugString( L"\n locate::set_write" );
                _write = in_write;//make_unique< write_d2d >( in_write );
            }

            static write_d2d & get_write() { return * _write; }//.get(); }

            static void set_windows( gui_microsoft * const in_windows ) 
            {
                OutputDebugString( L"\n locate::set_windows" );
                _windows = in_windows;//make_unique< gui_microsoft >( in_windows );
            }

            static gui_microsoft & get_windows() { return * _windows; }//.get(); }
            //static gui_microsoft * get_windows() { return _windows.get(); }

        private:

            static inline hid_usages    * _usages   { nullptr };//unique_ptr< hid_usages   >  _usages   {};
            static inline graphics_d2d  * _graphics { nullptr }; //unique_ptr< graphics_d2d >  _graphics {};
            static inline write_d2d     * _write    { nullptr };//unique_ptr< write_d2d    >  _write    {};
            static inline gui_microsoft * _windows  { nullptr };//unique_ptr< gui_microsoft > _windows  {};
            
            //static inline unordered_map< service_identifier , void * > services {};
            //static inline unordered_map< service_identifier , any    > services {};

            //static graphics_d2d & graphics();
            //static write_d2d    & write;
            //static hid_usages   & usages();
            //static service & ( service_identifier in_identifier , service * = nullptr );

    }; // class locate

} // namespace hid