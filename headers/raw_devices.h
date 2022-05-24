#pragma once

#include < vector >

#include "..\headers\raw_device.h"
#include "..\headers\globals.h"

namespace hid
{ 
   using namespace std;

   class raw_devices
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