#pragma once

#include < vector >

#include < hidsdi.h >
#include < hidpi.h >

#include "..\headers\raw_devices.h"
#include "..\headers\hid_device.h"

namespace hid
{
   class hid_devices //: public raw_devices
   {
      protected:
         
         vector< hid_device > input; // multi-touch devices

      public:

        hid_devices()
        {
           using                     raw_device_list = RAWINPUTDEVICELIST;
           uint                      amount          {};
           vector< raw_device_list > raw_list        {};

           GetRawInputDeviceList( nullptr         , & amount , sizeof( raw_device_list ) );

           raw_list.resize( amount );

           GetRawInputDeviceList( raw_list.data() , & amount , sizeof( raw_device_list ) );

           for( auto & device : raw_list )
           { 
              hid_device new_device( device.hDevice );

              if( new_device.is_multi_touch() )
                 input.emplace_back( move( new_device ) );
           }

        }

   }; // class hid_devices

} // namespace hid