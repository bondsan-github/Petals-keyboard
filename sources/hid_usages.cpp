#include "..\headers\hid_usages.h"

//#include < stdexcept >
#//include < format >

//#include "..\headers\locate.h"
//#include "..\headers\hid_usage_text.h"

namespace hid
{
    using namespace std;

    void hid_usages::initialise()
    {
        locate::provide_usages( this );
    }

    wstring hid_usages::page( uint in_page ) const
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

    wstring hid_usages::usage( uint in_page , uint in_usage ) const
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
            return usages.at( in_page ).at( in_usage ).first;
        }
        catch( out_of_range const & exception )
        {
            return format( L"{:x} usage" , in_usage ); // hex string
        }
    }

    wstring hid_usages::type( uint in_page , int in_usage ) const
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

} // namespace hid
