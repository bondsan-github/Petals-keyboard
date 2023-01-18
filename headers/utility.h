#pragma once

namespace hid
{
    void error_exit( const wchar_t * message ); // print error message box and exit application
    void print_error( const wchar_t * message );
    void print_debug( const wchar_t * message );
}
