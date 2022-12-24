#include "..\headers\hid_usages.h"

#include < stdexcept >
#include < format >

#include "..\headers\locate.h"
#include "..\headers\hid_usage_text.h"

namespace hid
{
    using namespace std;

    hid_usages::hid_usages()
    {
        //OutputDebugString( L"\n hid_usages:default :constructor" );
        
        locate::set_usages( this );
    }

    //hid_usages::~hid_usages() { OutputDebugString( L"\n hid_usages::de-constructor" ); };

    const wstring hid_usages::page( const uint in_page )
    {
        try
        {
            return pages.at( in_page );
        }
        catch( out_of_range const & exception )
        {
           //string exception_text(exception.what() );
           //return wstring( to_wstring( in_page ) );
            return format( L"{:x} page" , in_page );//, static_cast<const char *>( exception.what() ) ); // hex string
        }
    };

    const wstring hid_usages::usage( const uint in_page , const uint in_usage )
    {
        try
        {
            pages.at( in_page );
        }
        catch( out_of_range const & exception )
        {
            return format( L"{:x} usage" , in_usage ); // hex string
        }

        try
        {
            return usages.at( in_page ).at( in_usage ).first;
        }
        catch( out_of_range const & exception )
        {
            return format( L"{:x} usage" , in_usage ); // hex string
        }
    }

    const wstring hid_usages::type( const uint in_page , const int in_usage ) 
    {
        try
        {
            pages.at( in_page );
        }
        catch( out_of_range const & exception ) //out_of_range & error 
        {
            return format( L"{:x} usage" , in_usage ); // hex string               
        }

        try
        {
            return usages.at( in_page ).at( in_usage ).second;
        }
        catch( out_of_range const & exception )
        {
            return format( L"{:x} usage" , in_usage ); // hex string
        }
    }

}
