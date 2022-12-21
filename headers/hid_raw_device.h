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

    class hid_raw_device
    {
        private:

            HANDLE           device       { nullptr };

            ushort           page         { 0 };
            ushort           usage        { 0 };
         
            HANDLE           file_pointer { nullptr };
            wstring          path         { L"no path" }; // or std::filesystem::wpath

            //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
            //hidp_status    status       { };

            const struct
            {
                uint data = ( 1 << 29 ) | 0x5;
                uint path = ( 1 << 29 ) | 0x7; // return value in character amount, not byte size
                uint info = ( 1 << 29 ) | 0xB;

            } requests; // instantiates here

            struct report
            {
                ushort byte_amount            { 0 };

                ushort button_amount          { 0 };
                ushort value_amount           { 0 };
                ushort data_identifier_amount { 0 };

                vector< hid_local_item >  buttons { 0 };
                vector< hid_global_item > values  { 0 };

            } input , output , feature;

             PHIDP_PREPARSED_DATA data        { nullptr }; // using PHIDP_PREPARSED_DATA
             vector< char >       data_vector { 0 };
             uint                 data_size   { 0 };

             ulong                collection_amount { 0 };

      public:

           hid_raw_device( void );
           hid_raw_device( const HANDLE in_device );
          ~hid_raw_device( void );

          hid_raw_device( const hid_raw_device & copy );
          //hid_raw_device( const hid_raw_device && move );// noexcept;

          //hid_raw_device & operator = ( const hid_raw_device & assignment );
          //hid_raw_device & operator = ( const hid_raw_device && assignment_move );// noexcept;

          ulong  get_collection_amount() const { return collection_amount; }
          HANDLE get_file_pointer()      const { return file_pointer; }
          PHIDP_PREPARSED_DATA get_data() const { return data; }

          report & get_input()   { return input; }
          report & get_output()  { return output; }
          report & get_feature() { return feature; }

          bool   is_multi_touch() const;

          ushort get_page()  const { return page; };
          ushort get_usage() const { return usage; };
   };

}