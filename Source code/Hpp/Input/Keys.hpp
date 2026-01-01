#pragma once

#include <map>

#include "Source code/Hpp/Custom types.hpp"
#include "Key.hpp"

const std::map< uint , Key > windows_keys
{
    { 0x00 , { Keys::none   , L"none"   } } ,
    { 0x0D , { Keys::enter  , L"Enter"  } } ,
    { 0x20 , { Keys::space  , L"Space"  } } ,
    { 0x1B , { Keys::escape , L"Escape" } } ,
    //{ 0u , { , L"" } } ,
    //{ 0u , { , L"" } } ,
};