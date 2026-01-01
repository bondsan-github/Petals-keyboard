#pragma once

#include <windows.h> // OutputDebugString
#include <string>

struct Token 
{
    Token( std::wstring in_message = {} ) : message{ in_message } {}

    std::wstring message {};
};

extern Token result_check;

class Logging
{
    public:

        Logging( HRESULT in_result = { E_FAIL } , std::wstring in_message = {} );
       
        void error_exit( const wchar_t * message , HRESULT result = S_OK ); // print error message box and exit application
        
        void print_debug( const wchar_t * message , HRESULT result = S_OK );

        void print_debug( const wchar_t * message );
        void print_debug( const char * message );

        friend void operator >> ( Logging , Token );

    private:
    //protected:

        HRESULT result { E_FAIL };
        
        std::wstring message {};

        std::wstring retreive_system_message( HRESULT result );
};

void operator >> ( Logging , Token );

//static Logging result_check;
//extern Logging result_check;





 // Helper for output debug tracing
 /*
inline void DebugTrace( _In_z_ _Printf_format_string_ const char * format , ... ) noexcept
{
#ifdef _DEBUG
    va_list args;
    va_start( args , format );

    char buff[ 1024 ] ={};
    vsprintf_s( buff , format , args );
    OutputDebugStringA( buff );
    va_end( args );
#else
    UNREFERENCED_PARAMETER( format );
#endif
}
*/