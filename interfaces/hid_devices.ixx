module;

export module hid_devices_module;

import std.core;

import raw_devices_module;
import hid_device_module;

namespace hid
{
   using namespace std;

   export class hid_devices
   {
      private: // variables
      
         raw_devices          raw;
         vector< hid_device > _devices; // multi_touch_devices

      public: // functions

        hid_devices()
        {
           vector< raw_device > raw_devices = raw.devices();

            for( auto & raw : raw_devices )
            {
               //if( raw.is_hid() ) // ignore keyboards and mice
               if( raw.is_multi_touch() )
               {
                  hid_device new_device( raw._pointer() , raw._type() );
                  
                  _devices.emplace_back( new_device );
               }
            }
        }

        vector< hid_device > devices()
        {
           return _devices;
        }
   };

} // nsamespace hid