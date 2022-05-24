module;

export module item_type_module;

import std.core;

import globals;
import usages_text_module;

namespace hid
{
   using namespace std;

   struct item;
   export using link = vector< item >::pointer;

   export enum class item_type : unsigned long
   {
      null ,
      physical , //= 0x00 ,
      application , //= 0x01 ,
      logical , //= 0x02 ,
      report , //= 0x03 ,
      named_array , //= 0x04 ,
      usage_switch , //= 0x05 ,
      usage_modifier , //= 0x06 ,
      reserved_start , //= 0x07 ,
      reserved_end , //= 0x7F ,
      device , //= 0x80 , // vendor defined
      vendor_defined , //= 0xFF ,
   };

   // HID Usage Tables FOR Universal Serial Bus( USB ) Version 1.3
   // usb.org/sites/default/files/hut1_3_0.pdf
   const vector< wstring > item_type_text
   {
      L"null"           , //
      L"physical"       , //
      L"application"    , // 
      L"logical"        , // 
      L"report"         , //
      L"named array"    , //
      L"usage switch"   , //
      L"usage modifier" , //
      L"reserved start" , //
      L"reserved end"   , //
      L"device"         , //
      L"vendor defined" , //
   };

   // vector< report > input;
   // vector< report > output;

   //class item
   export struct item
   {
      //private:

      item_type type{ item_type::vendor_defined };

      ushort page   {};
      ushort usage  {};
      bool   alias  {};

      ushort amount {}; // children

      link   origin {}; // parent
      link   next   {}; // sibling
      link   first  {}; // child

      // public information
      // public drawable()

      wstring text()
      {
         wstring text;

         text  = L"type\t: ";
         text += item_type_text.at( to_underlying( type ) );
         text += L"\npage\t: ";
         text += usages.page( page );
         text += L"\nusage\t: ";
         text += usages.usage( page , usage );
         if( amount )
         {
            text += L"\nlink amount : ";
            text += to_wstring( amount );
         }

         return text;
      }
   }; // struct item

   export struct main_item : public item
   {
      uchar             report_id         {};
      vector< ushort >  _usages           {};
      //item_type
      vector< wstring > types             {};
      ushort            bit_field         {};
      //ushort            origin_page     {};
      //ushort            origin_usage    {};
      bool              range             {};
      bool              string            {};
      bool              designator        {};
      bool              absolute          {};
      ushort            report_amount     {};
      vector< ushort >  string_idents     {};
      vector< ushort >  designator_idents {};
      vector< ushort >  data_idents       {};

      vector< pair< long , long > > logical_limits{};
      vector< pair< long , long > > physical_limits{};

      //text += L"\nreport id\t: ";
      //text += report_id;
      

   }; // struct main_item    

   struct button : public item {};

   struct value  : public item
   {
      bool   has_null{};
      ushort bit_amount{};
      ulong  units_exponent{};
      ulong  units{};
   };
   
} // namespace hid