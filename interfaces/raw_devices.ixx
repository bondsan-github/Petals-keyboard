module;

#include < windows.h >

#include < hidsdi.h >
#include < hidpi.h >

export module raw_devices_module;

import std.core;

import globals;
import raw_device_base_module;
import raw_device_module;

namespace hid
{ 
   using namespace std;

   export class raw_devices
   {
      private:

         vector< raw_device > _devices {};
         
      public:

         raw_devices()
         {
            uint                         amount   {};
            vector< RAWINPUTDEVICELIST > raw_list {};

            GetRawInputDeviceList( nullptr         , & amount , sizeof( RAWINPUTDEVICELIST ) ); // request total number of hid raw devices
            raw_list.resize( amount );
            GetRawInputDeviceList( raw_list.data() , & amount , sizeof( RAWINPUTDEVICELIST ) ); // request hid raw device list

            for( auto & raw : raw_list )
            {
               HANDLE          pointer = raw.hDevice;
               raw_device_type type    = raw_device_type( raw.dwType );  // try catch out of bounds

               _devices.emplace_back( pointer , type );
            }
         }

         vector< raw_device > devices() { return _devices; }
         
   }; // class raw_devices

} // namespace hid