#pragma once

#include < string >
#include < vector >
#include < Windows.h >
#include < hidsdi.h >

#include "..\headers\direct_2d.h"
#include "..\headers\hid_local_item.h"
#include "..\headers\hid_global_item.h"

namespace hid
{
   using namespace std;

   class hid_raw_device //abstract 
   {
      protected:

         HANDLE           device       {};

         ushort           page         {};
         ushort           usage        {};
         
         HANDLE           file_pointer {};
         wstring          path         {}; // or std::filesystem::wpath

         //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
         //hidp_status    status       {};

         const struct
         {
            uint data = ( 1 << 29 ) | 0x5;
            uint path = ( 1 << 29 ) | 0x7; // return value in character amount, not byte size
            uint info = ( 1 << 29 ) | 0xB;
         } requests; // instantiates here

         struct report // typedef ?
         {
            ushort byte_amount            {};

            ushort button_amount          {};
            ushort value_amount           {};
            ushort data_identifier_amount {};

            vector< hid_local_item >  buttons {};
            vector< hid_global_item > values  {};
         } input , output , feature;

         PHIDP_PREPARSED_DATA data        {};
         vector< char >       data_vector {};
         uint                 data_size   {};

         ulong                collection_amount {};

      public:

              hid_raw_device( HANDLE in_device );
         bool is_multi_touch();
         ~hid_raw_device() { CloseHandle( file_pointer ); }
   };

}