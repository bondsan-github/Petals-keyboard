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
                { 0x0001 , L"WM_CREATE" } ,
                { 0x0002 , L"WM_DESTROY" } ,
                { 0x0003 , L"WM_MOVE" } ,
                { 0x0005 , L"WM_SIZE" } ,
                { 0x0006 , L"WM_ACTIVATE" } ,
                { 0x0007 , L"WM_SETFOCUS" } ,
                { 0x000F , L"WM_PAINT" } ,

                { 0x0014 , L"WM_ERASEBKGND" } ,

                { 0x0018 , L"WM_SHOWWINDOW" } ,
                { 0x001C , L"WM_ACTIVATEAPP" } ,
                
                { 0x0020 , L"WM_SETCURSOR" } ,
                { 0x0024 , L"WM_GETMINMAXINFO" } ,
                
                { 0x0046 , L"WM_WINDOWPOSCHANGING" } ,
                { 0x0047 , L"WM_WINDOWPOSCHANGED" } ,
                
                { 0x007F , L"WM_GETICON" } ,

                { 0x0081 , L"WM_NCCREATE" } ,
                { 0x0083 , L"WM_NCCALCSIZE" } ,
                { 0x0084 , L"WM_NCHITTEST" } ,
                { 0x0085 , L"WM_NCPAINT"   } ,
                { 0x0086 , L"WM_NCACTIVATE"   } ,

                { 0x0100 , L"WM_KEYDOWN"   } ,
                { 0x0102 , L"WM_CHAR"   } ,

                { 0x0200 , L"WM_MOUSEMOVE"   } ,
                { 0x0281 , L"WM_IME_SETCONTEXT"   } ,
                { 0x0282 , L"WM_IME_NOTIFY"   } ,

                { 0x031F , L"WM_DWMNCRENDERINGCHANGED"   } ,
                
                
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
                    return L"\n" + map_itr->second;
                else
                    return std::format( L"\n0x{:x} message not in map" , in_message_value );
            }

    };
}
