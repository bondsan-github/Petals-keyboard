#pragma once

#include < string >
#include < vector >
#include < Windows.h >
#include < hidsdi.h >

//#include "..\headers\utility.h"
#include "..\headers\direct_2d.h"
#include "..\headers\hid_local_item.h"
#include "..\headers\hid_global_item.h"

namespace hid
{
    using namespace std;

    struct report
    {
        ushort byte_amount            { 0 };

        ushort button_amount          { 0 };
        ushort value_amount           { 0 };
        ushort data_identifier_amount { 0 };

        vector< hid_local_item >  buttons { 0 };
        vector< hid_global_item > values  { 0 };
    };

    const struct requests
    {
        uint data = ( 1 << 29 ) | 0x5;
        uint path = ( 1 << 29 ) | 0x7; // return value in character amount, not byte size
        uint info = ( 1 << 29 ) | 0xB;

    };

    class hid_raw_device
    {
        private:

            HANDLE device_pointer { nullptr };

            PHIDP_PREPARSED_DATA data_preparsed   { nullptr };
            vector< _int8 >      data_bytes       { 0 };
            uint                 data_byte_amount { 0 };

            HIDP_CAPS capabilities {};

            ushort page  { 0 };
            ushort usage { 0 };

            requests request;

      public:

           hid_raw_device( HANDLE in_device );
          //~hid_raw_device( void );

          bool is_multi_touch();

          HANDLE get_device_pointer()
          { 
              //if( device_pointer ) return device_pointer;
              //else error( L"device pointer is null" );

              return device_pointer;
          }
          HIDP_CAPS get_capabilities()  { return capabilities; }
          PHIDP_PREPARSED_DATA get_preparsed_data()  { return data_preparsed; }
          ushort get_page()   { return page; }
          ushort get_usage()  { return usage; }
   };

}