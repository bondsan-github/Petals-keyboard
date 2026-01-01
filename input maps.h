#pragma once

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// WinUser.h

#include <map>
#include <string>

const std::map< std::wstring , unsigned int  > inputs_english
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