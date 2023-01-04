#pragma once
#include "custom_types.h"
#include <unordered_map>
#include <string>
#include <format>

namespace hid
{
    class window_messages
    {
        private:

            std::unordered_map< uint , std::wstring > messages
            {
                { 0x0081 , L"WM_NCCREATE" } ,
                { 0x0083 , L"WM_NCCALCSIZE" } ,
                { 0x0001 , L"WM_CREATE" } ,
                { 0x0046 , L"WM_WINDOWPOSCHANGING" } ,
                { 0x0083 , L"WM_NCCALCSIZE" } ,
                { 0x0047 , L"WM_WINDOWPOSCHANGED" } ,
                { 0x0003 , L"WM_MOVE" } ,
                { 0x0024 , L"WM_GETMINMAXINFO" } ,
                { 0x0085 , L"WM_NCPAINT"   } ,
                { 0x0084 , L"WM_NCHITTEST" }
            };

        public:

            window_messages()
            {
                //locate::set_window_messages(this);
            }

            std::wstring message_text( const uint in_message_value )
            {
                //try..catch 
                std::unordered_map< uint, std::wstring >::const_iterator map_itr = messages.find( in_message_value );

                if( map_itr != messages.end() )
                    return map_itr->second + L"\n";
                else
                    return std::format( L"0x{:x} message not in map\n" , in_message_value );
            }

    };
}
