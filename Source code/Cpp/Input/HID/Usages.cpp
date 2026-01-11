#include "Input\HID\Usages.h"

#include "Input\HID\Usage_text.h"

//#include <stdexcept>
#include <format>
#include <algorithm>

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

    std::wstring Usages::page( uint page )
    {
        if( page < pages.size() )
        {
            return pages.at( page );
        }
        else
        {
            return std::format( L"no string for 0x{:x}" , page ); // hex string
        }
    };

    std::wstring Usages::usage( uint page, uint usage )
    {
        if( page < usages.size() && usage < usages.at(page).size() && ! usages.at(page).empty() )
        {
            return usages.at( page ).at( usage );
        }
        else
        {
            return std::format( L"no string for 0x{:x}" , usage );
        }
    }

    std::wstring Usages::type( uint type )
    {
        //TODO: remove try catch
        try
        {
            return type_texts.at( type );
        }
        catch( std::out_of_range & exception )
        {
            return std::format( L"no sting for {:x}", type );
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
