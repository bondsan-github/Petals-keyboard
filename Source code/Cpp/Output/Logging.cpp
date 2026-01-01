#include "Output\Logging.h"

#include "Custom types.h"

#include <strsafe.h>
#include <iostream>
#include <sstream> // ostringstream

Token result_check;

void operator >> ( Logging logger , Token )
{
    if( logger.result not_eq S_OK )
    {
        //std::wostringstream output_stream{};
        //output_stream << ' ' << logger.retreive_system_message( in_result );
        //OutputDebugStringW( output_stream.str().c_str() );

        //std::wstring message {};

        logger.message += logger.retreive_system_message( logger.result );
        OutputDebugStringW( logger.message.c_str() );

        MessageBoxW( 0 , logger.message.c_str() , L"Application fail." , MB_OK );

        PostQuitMessage( logger.result );
    }
}

Logging::Logging( HRESULT in_result , std::wstring in_message )
: result { in_result } , message { in_message }
{}

std::wstring Logging::retreive_system_message( HRESULT result )
{
    const ulong character_amount { 500 };
    
    wchar_t system_message[ character_amount ] {};
    //std::wstring system_message( character_amount , '\n' );

    // Retrieve the system error message for the last-error code
    FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM |    //  search the system message-table resource(s) for the requested message
                    FORMAT_MESSAGE_IGNORE_INSERTS , // later formatting
                    0 ,                             // source
                    result ,
                    MAKELANGID( LANG_NEUTRAL , SUBLANG_DEFAULT ) ,
                    system_message ,
                    character_amount ,              // amount of characters to allocate
                    0 );                            // ... va_list
                   
    std::wstring message = system_message;

    return message;
}

void Logging::print_debug( const wchar_t * message )
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

void Logging::print_debug( const wchar_t * title_text , HRESULT result )
{
    // Create a text string initialised with the title_text parameter.
    std::wstring text { title_text };

    // If result is anything other than S_OK then append the system error message.
    if( result not_eq S_OK ) text += retreive_system_message( result );

    // Print the message to the debugger.
    OutputDebugStringW( text.c_str() );
}

void Logging::error_exit( const wchar_t * message, HRESULT in_result )
{

    std::wstring system_message = retreive_system_message( in_result );

    MessageBoxW( 0 , system_message.data() , L"Application fail." , MB_OK);

    OutputDebugStringW( system_message.c_str() );

    //ExitProcess( result );
    PostQuitMessage( in_result );
}

/*
    wchar_t buffer[1024] {};

    va_list AdditionalParameters;
    va_start( AdditionalParameters , pFormat );
    wvsprintf( buffer + StringLength , pFormat , AdditionalParameters );
    va_end( AdditionalParameters );
*/

// LoadStringRCEx()
