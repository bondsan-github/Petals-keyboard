#include "Output\Logging.h"

#include "Aliases.h"

//#include <Windows.h>
#include <strsafe.h>
#include <iostream>
#include <sstream>
#include <format>
//Logging::Logging( HRESULT result, std::wstring message )
//: result_( result ), message_( message )
//{}

std::wstring Logging::system_message( long result )
{
    if( !result )
    {
        result = GetLastError();
    }

    const ulong character_amount { 500 };
    
    wchar_t system_message[ character_amount ] {};
    //std::wstring system_message( character_amount , '\n' );

    // Retrieve the system error message for the last-error code
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM |   // search the system message-table resources
                   FORMAT_MESSAGE_IGNORE_INSERTS, // later formatting
                   0,                             // source
                   result,
                   MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ) ,
                   system_message,
                   character_amount,              // amount of characters to allocate
                   0 );                           // ... va_list
                   
    std::wstring message = system_message;

    return message;
}

void Logging::print_debug( wchar_t * message )
{
    std::wostringstream ouput_stream {};
    ouput_stream << message;

    OutputDebugStringW( ouput_stream.str().c_str() );
}

void Logging::print_debug( const char * message )
{
    std::ostringstream ouput_stream{};
    ouput_stream << message;

    OutputDebugStringA( ouput_stream.str().c_str() );
}

void Logging::print_debug( const wchar_t * message, HRESULT result )
{
    // Create a text string initialised with the message parameter.
    std::wstring text { message };

    text += system_message( result );

    // Print the message to the debugger.
    OutputDebugStringW( text.c_str() );
}

void Logging::error_exit( const wchar_t * message, HRESULT result )
{

    std::wstring sys_message = system_message( result );

    MessageBoxW( 0 , sys_message.data() , message , MB_OK );

    std::wstring debug_string = std::format(L"{}: {}", message, sys_message.c_str() );

    OutputDebugString( debug_string.c_str() );

    PostQuitMessage( result );
}

//Token result_check;
//
//void operator >> ( Logging logger , Token )
//{
//    if( logger.result_ not_eq S_OK )
//    {
//        //std::wostringstream output_stream{};
//        //output_stream << ' ' << logger.system_message( in_result );
//        //OutputDebugStringW( output_stream.str().c_str() );
//
//        //std::wstring message {};
//
//        logger.message_ += logger.system_message( logger.result_ );
//        OutputDebugStringW( logger.message_.c_str() );
//
//        MessageBoxW( 0 , logger.message_.c_str() , L"Application fail." , MB_OK );
//
//        PostQuitMessage( logger.result_ );
//    }
//} 

/*
    wchar_t buffer[1024] {};

    va_list AdditionalParameters;
    va_start( AdditionalParameters , pFormat );
    wvsprintf( buffer + StringLength , pFormat , AdditionalParameters );
    va_end( AdditionalParameters );
*/

// LoadStringRCEx()
