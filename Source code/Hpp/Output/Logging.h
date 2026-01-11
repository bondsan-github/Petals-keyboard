#pragma once

#include <windows.h> 
#include <debugapi.h>// OutputDebugString
#include <string>
//#include <source_location>
//std::source_location = std::source_location::current()

//struct Check_token {};
//extern Check_token hr_check;

struct HRESULT_check 
{

    HRESULT_check( HRESULT result )
    {
        OutputDebugString(L"\nresult checked");
    }

    template<typename type>
    friend void operator >> ( int a, type & func ) {}
};

// int f() { return 1; }
// f() >> hr_check;
// f().operator>>(
// 
// how does Check_token oject pass extracted value to HRESULT_check?

extern HRESULT_check hr_check;

//void operator >> ( long a , HRESULT_check );

//struct Token 
//{
//    Token( std::wstring in_message = {} ) : message{ in_message } {}
//
//    std::wstring message {};
//};
//
//extern Token result_check;
//
class Logging
{
    public:

        //Logging( HRESULT result, std::wstring message );
        Logging() 
        {
            //OutputDebugString(L"\n Logging::Logging()");
        }

        ~Logging()
        {
            //OutputDebugString( L"\n Logging::~Logging()" );
        }

        void error_exit( const wchar_t * message, HRESULT result = 0); // print error message box and exit application
        
        void print_debug( const wchar_t * message, HRESULT result = 0);
        void print_debug( wchar_t * message );
        void print_debug( const char * message );

    protected:
    
        HRESULT result_ { E_FAIL };
        
        std::wstring message_ {};
        std::wstring system_message( long result = 0 );
};
//
//void operator >> ( Logging, Token );

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