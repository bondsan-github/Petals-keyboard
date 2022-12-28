#pragma once

#include "..\headers\custom_types.h"
#include <utility>

namespace hid
{
    class virtual_screen
    {
        private:

            // devices
            wchar_t *       device_name    = nullptr;

            // displays
            unsigned short  display_index  { 0 };
            std::vector< DISPLAY_DEVICE > displays; // { .cb = sizeof( DISPLAY_DEVICE ) };
        
            enum class      request : unsigned long { devices , guid };

            long            result {};
            wchar_t         szTemp[ 200 ];
            DEVMODE         defaultMode {};
        
        public:

            virtual_screen()
            {
                while( EnumDisplayDevices( device_name , display_index , & displays.at( display_index ) , std::to_underlying(request::devices)) )
                {
                    display_index++;
                } // end while for all display devices
            }
    };
}

// HMONITOR
// WM_DISPLAYCHANGE
// EnumDisplayMonitors  
// 
//defaultMode.dmSize = sizeof( DEVMODE );
//EnumDisplaySettings( ( LPWSTR ) displays.at( display_index ).DeviceName , ENUM_REGISTRY_SETTINGS , &defaultMode );
//if( displays.at( display_index ).StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP )
//{
    //DEVMODE DevMode { .dmSize = sizeof( DEVMODE ) };
    //DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_POSITION | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS ;
    //Result = ChangeDisplaySettingsEx( ( LPWSTR ) displays.at( display_index ).DeviceName , &DevMode , NULL , CDS_UPDATEREGISTRY , NULL );
    //The code below shows how to re-attach the secondary displays to the desktop
    //ChangeDisplaySettingsEx((LPSTR)DisplayDevice.DeviceName, &defaultMode, NULL, CDS_UPDATEREGISTRY, NULL);
//}

// Reinit DisplayDevice just to be extra clean
//ZeroMemory( & DisplayDevice , sizeof( DisplayDevice ) );
//DisplayDevice.cb = sizeof( DisplayDevice );