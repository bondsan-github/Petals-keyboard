#include "Input\HID\Usages.h"

#include "Input\HID\Usage_text.h"

#include <stdexcept>
#include <format>

namespace HID
{
    Usages::Usages()
    {
        //OutputDebugString( L"Usages::default constructor\n" );
    }

    Usages::~Usages()
    {
        //OutputDebugString( L"Usages::de-constructor\n" );
    };

    std::wstring Usages::page( uint in_page )
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

    std::wstring Usages::usage( uint in_page , uint in_usage )
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

    std::wstring Usages::type( uint in_type )
    {
        //TODO: remove try catch
        try
        {
            return type_texts.at( in_type );
        }
        catch( std::out_of_range & exception )
        {
            return std::format( L"{:x} type" , in_type ); // hex string
        }
    }

    /*
    std::wstring Usages::type( uint in_page , int in_usage )
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
