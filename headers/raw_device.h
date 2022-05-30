#pragma once

#include < Windows.h >

#include < hidsdi.h >
#include < hidpi.h >

#include "..\headers\globals.h"

namespace hid
{
   using namespace std;

   class raw_device abstract
   {
      protected:

         HANDLE           device       {};
         ushort           page         {};
         ushort           usage        {};
         
         HANDLE           file_pointer {};
         wstring          path         {}; // or std::filesystem::wpath

         //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
         //hidp_status    status       {};

         struct report
         {
            ushort byte_amount            {};
            ushort button_amount          {};
            ushort value_amount           {};
            ushort data_identifier_amount {};
         };

         const struct
         {
            uint data = ( 1 << 29 ) | 0x5;
            uint path = ( 1 << 29 ) | 0x7; // return value in character amount, not byte size
            uint info = ( 1 << 29 ) | 0xB;
         } requests;

         PHIDP_PREPARSED_DATA data        {};
         vector< char >       data_vector {};
         uint                 data_size   {};

         ulong                item_amount {};

         struct : public report {} input;
         struct : public report {} output;
         struct : public report {} feature;

      public:

         raw_device( HANDLE in_device )
         : device( in_device )
         {
            uint data_size {};

            GetRawInputDeviceInfo( device , requests.data , nullptr , & data_size );

            data_vector.resize( data_size );

            GetRawInputDeviceInfo( device , requests.data , data_vector.data() , & data_size );

            data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_vector.data() );

            HIDP_CAPS caps {};

            HidP_GetCaps( data , & caps );

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

            uint path_char_amount {};

            GetRawInputDeviceInfo( device , requests.path , nullptr     , & path_char_amount );

            path.resize( path_char_amount );

            GetRawInputDeviceInfo( device , requests.path , path.data() , & path_char_amount );  // wchar_t

            // open i_o device for query 
            file_pointer = CreateFileW( path.data() ,
                                        0 ,                                  // access
                                        FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                        0 ,                                  // security
                                        OPEN_EXISTING ,                      // creation
                                        FILE_ATTRIBUTE_NORMAL ,              // flags
                                        0 );                                 // template

          
         }

         bool is_multi_touch() { return page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD; }

   }; // class raw_device_base

} // namespace hid