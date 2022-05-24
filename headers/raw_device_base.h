#pragma once

#include < Windows.h >

#include < hidsdi.h >
#include < hidpi.h >

#include "..\headers\globals.h"

namespace hid
{
   using namespace std;

   class raw_device_base
   {
      protected:
      
         raw_device_type  type  {};
         ushort           page  {};
         ushort           usage {};
         
         //NTSTATUS    hid_result { HIDP_STATUS_NULL };
         //hidp_status status     {};

         struct report
         {
            ushort byte_amount            {};
            ushort button_amount          {};
            ushort value_amount           {};
            ushort data_identifier_amount {};
         };
      
         HANDLE           pointer {};

         const struct
         {
            uint data = 0x20'000'005; // ( 2 << 7 ) & 5
            uint path = 0x20'000'007;  // the return value is the character amount, not the byte size
            uint info = 0x20'000'00b;
         } requests; // instantiates here

         PHIDP_PREPARSED_DATA data        {};
         vector< char >       data_vector {};
         uint                 data_size   {};
         
         ulong                item_amount {};

         struct : public report {} input;
         struct : public report {} output;
         struct : public report {} feature;

      public: // functions

         HANDLE          _pointer( void ) { return pointer; }
         raw_device_type _type( void )    { return type; }

         raw_device_base( HANDLE in_pointer , raw_device_type in_type ) 
         : pointer( in_pointer ) , type( in_type )
         {
            HIDP_CAPS caps {};

            uint data_size {};

            GetRawInputDeviceInfo( pointer , requests.data , nullptr            , & data_size );

            data_vector.resize( data_size ); 

            GetRawInputDeviceInfo( pointer , requests.data , data_vector.data() , & data_size);

            data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_vector.data() );

            HidP_GetCaps( data , & caps); // request hid capabilities

            page        = caps.UsagePage;
            usage       = caps.Usage;
            item_amount = caps.NumberLinkCollectionNodes;

            input.byte_amount              = caps.InputReportByteLength;
            input.button_amount            = caps.NumberInputButtonCaps;
            input.value_amount             = caps.NumberInputValueCaps;
            input.data_identifier_amount   = caps.NumberInputDataIndices;

            output.byte_amount             = caps.OutputReportByteLength;
            output.button_amount           = caps.NumberOutputButtonCaps;
            output.value_amount            = caps.NumberOutputValueCaps;
            output.data_identifier_amount  = caps.NumberOutputDataIndices;

            feature.byte_amount            = caps.FeatureReportByteLength;
            feature.button_amount          = caps.NumberFeatureButtonCaps;
            feature.value_amount           = caps.NumberFeatureValueCaps;
            feature.data_identifier_amount = caps.NumberFeatureDataIndices;
         }
         
         bool is_hid() { return type == raw_device_type::hid; }

         bool is_multi_touch() { return page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD; }

   }; // class raw_device_base

} // namespace hid


         //     new_device = old_device
         // int i          = 1;

         // copy from source to this , constructor // do inherited classes need to call base class constructor - 
         /*
         raw_device_base( const raw_device_base & source )
         {
            type  = source.type;
            page  = source.page;
            usage = source.usage;

            pointer = source.pointer;

            //preparsed_data.pointer = source.preparsed_data.pointer;
            //preparsed_data.size = source.preparsed_data.size;

            if( data ) HidD_FreePreparsedData( data );

            data_size = source.data_size;

            memcpy( data , source.data , data_size );

            item_amount = source.item_amount;

            input   = source.input;
            output  = source.output;
            feature = source.feature;
         }
         */
