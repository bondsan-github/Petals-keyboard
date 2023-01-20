#include "..\headers\hid_usages.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usage_text.h"

#include <stdexcept>
#include <format>

namespace hid
{
    hid_usages::hid_usages()
    {
        //OutputDebugString( L"hid_usages::default constructor\n" );
        
        locate::set_usages( this );
    }

    hid_usages::~hid_usages()
    {
        //OutputDebugString( L"hid_usages::de-constructor\n" );
    };

    std::wstring hid_usages::page( const uint &in_page )
    {
        try
        {
            return pages.at( in_page );
        }
        catch( std::out_of_range const & exception )
        {
            return std::format( L"{:x} page" , in_page ); // hex string
        }
    };

    std::wstring hid_usages::usage( const uint &in_page , const uint &in_usage )
    {
        try
        {
            return usages.at( in_page ).at( in_usage );
        }
        catch( std::out_of_range & exception )
        {
            return std::format( L"{:x} usage" , in_usage ); // hex string
        }
    }

    std::wstring hid_usages::collection_type( const uint &in_type )
    {
        // remove try catch
        try
        {
            return collection_type_text.at( in_type );
        }
        catch( std::out_of_range & exception )
        {
            return std::format( L"{:x} type" , in_type ); // hex string
        }
    }

    /*
    std::wstring hid_usages::type( uint in_page , int in_usage )
    {
        try
        {
            pages.at( in_page );
        }
        catch( std::out_of_range & exception ) //out_of_range & error 
        {
            return std::format( L"{:x} usage" , in_usage ); // hex string               
        }

        try
        {
            return usages.at( in_page ).at( in_usage ).second;
        }
        catch( std::out_of_range & exception )
        {
            return std::format( L"{:x} usage" , in_usage ); // hex string
        }
    }
    */

} // namespace hid
