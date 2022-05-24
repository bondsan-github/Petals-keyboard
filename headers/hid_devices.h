#pragma once

#include < vector >

#include < hidsdi.h >
#include < hidpi.h >

#include "raw_devices.h"
#include "hid_device.h"

namespace hid
{
   class hid_devices
   {
      private: // variables
      
         raw_devices          raw;
         vector< hid_device > _devices; // multi-touch devices

      public: // functions

        hid_devices()
        {
           vector< raw_device > raw_devices = raw.devices();

            for( auto & raw : raw_devices )
            {
               //if( raw.is_hid() ) // ignore keyboards and mice
               if( raw.is_multi_touch() )
               {
                  //hid_device new_device( raw._pointer() , raw._type() );
                  //_devices.emplace_back( new_device );

                  _devices.emplace_back( raw._pointer() , raw._type() );
               }
            }
        }

        vector< hid_device > devices()
        {
           return _devices;
        }
   };

} // nsamespace hid