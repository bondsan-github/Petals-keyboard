#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <hidsdi.h>

//#include "..\headers\utility.h"
#include "..\headers\custom_types.h"
#include "..\headers\hid_globals.h"
//#include "..\headers\hid_local_item.h"
//#include "..\headers\hid_global_item.h"

namespace hid
{
    class hid_raw_device
    {
        private:

            HANDLE device_pointer { nullptr };

            std::vector< std::byte >  data_preparsed {}; // _int8 || uchar

            hid_capabilities capabilities; //_HIDP_CAPS

            ushort page  { 0 };
            ushort usage { 0 };

            requests request;

        public:

            //hid_raw_device();
            //~hid_raw_device();
            
            hid_raw_device( const HANDLE &in_device );
            
            //hid_raw_device( const hid_raw_device & copy );
            //hid_raw_device( hid_raw_device && move ) noexcept;
            //hid_raw_device & operator = ( const hid_raw_device & assign_copy );
            //hid_raw_device & operator = ( hid_raw_device && assign_move ) noexcept;
            //void reset();

            bool is_multi_touch();

            std::vector< std::byte > get_data_vector()const { return data_preparsed; }
            HANDLE               get_device_pointer() const { return device_pointer; }
            hid_capabilities     get_capabilities()   const { return capabilities;   }
            ushort               get_page()           const { return page;           }
            ushort               get_usage()          const { return usage;          }
   };

}