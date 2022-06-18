#include "..\headers\globals.h"

namespace hid
{
    // wchar_t ~ unsigned short
    void error( const wchar_t * title_text )
    {
        // Retrieve the system error message for the last-error code

        const uint char_amount{ 200 };

        wchar_t message[ char_amount ]{};
        wchar_t display[ char_amount ]{};
        ulong   error_id               = GetLastError();

        FormatMessage(// FORMAT_MESSAGE_ALLOCATE_BUFFER |
                       FORMAT_MESSAGE_FROM_SYSTEM |   //  search the system message-table resource(s) for the requested message
                       FORMAT_MESSAGE_IGNORE_INSERTS , // later formatting
                       0 ,  // source
                       error_id ,
                       MAKELANGID( LANG_NEUTRAL , SUBLANG_DEFAULT ) ,
                       //( LPTSTR ) & message ,
                       message ,
                       char_amount ,  // amount of characters
                       0 ); // ... va_list

       // Display the error message and exit the process
        //display = LocalAlloc( LMEM_ZEROINIT , ( lstrlen( message ) + lstrlen( title_text ) + 40 ) * sizeof( wchar_t ) );

        StringCchPrintf( display ,
                         char_amount ,
                         L"%s : error %d: %s" , title_text , error_id , message );

        MessageBox( 0 , display , L"error" , MB_OK );

        ExitProcess( error_id );
    }

} // namespace hid