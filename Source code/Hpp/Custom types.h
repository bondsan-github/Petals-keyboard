#pragma once

#include <map>
#include <string>

using uchar  = unsigned char;  //  8 bits
using ushort = unsigned short; // 16 bits
using uint   = unsigned int;   // 32 bits
using ulong  = unsigned long;  // long same as int
//using string = std::wstring;

template< typename Type >
static void set_name( Type com, const wchar_t * const name )
{
    com->SetPrivateData( __uuidof( com ) , static_cast< uint >( wcslen( name ) * 2 ) , name );
}

struct Range
{
    long minimum { 0 };
    long maximum { 0 };

    //range() {}
    //range( const long & in_minimum , const long & in_maximum ) : minimum( in_minimum ) , maximum( in_maximum ) {}
};

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// WinUser.h

const std::map< std::wstring , unsigned int > inputs_english
{
    { L"0" , 0x30u } ,
    { L"1" , 0x31u } ,
    { L"2" , 0x32u } ,
    { L"3" , 0x33u } ,
    { L"4" , 0x34u } ,
    { L"5" , 0x35u } ,
    { L"6" , 0x36u } ,
    { L"7" , 0x37u } ,
    { L"8" , 0x38u } ,
    { L"9" , 0x39u } ,
    // 0x3a
    // ...
    // 0x40
    { L"a" , 0x41 } ,
    { L"b" , 0x42 } ,
    { L"c" , 0x43 } ,
    { L"d" , 0x44 } ,
    { L"e" , 0x45 } ,
    { L"f" , 0x46 } ,
    { L"g" , 0x47 } ,
    { L"h" , 0x48 } ,
    { L"i" , 0x49 } ,
    { L"j" , 0x4a } ,
    { L"k" , 0x4b } ,
    { L"l" , 0x4c } ,
    { L"m" , 0x4d } ,
    { L"n" , 0x4e } ,
    { L"o" , 0x4f } ,
    { L"p" , 0x50 } ,
    { L"q" , 0x51 } ,
    { L"r" , 0x52 } ,
    { L"s" , 0x53 } ,
    { L"t" , 0x54 } ,
    { L"u" , 0x55 } ,
    { L"v" , 0x56 } ,
    { L"w" , 0x57 } ,
    { L"x" , 0x58 } ,
    { L"y" , 0x59 } ,
    { L"z" , 0x5a } ,
    //{ L"Left Windows" , VK_LWIN } ,
};

/*
class colours : public D2D1::ColorF //_D3DCOLORVALUE
{
public:
    friend bool operator not_eq ( const D2D1::ColorF & in_left , const D2D1::ColorF & in_right )
    {
        return { in_left.r == in_right.r and
                    in_left.g == in_right.g and 
                    in_left.b == in_right.b };
    }
};
*/
