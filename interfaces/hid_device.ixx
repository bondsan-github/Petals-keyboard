module;

#include <Windows.h>

#include <hidpi.h>
#include <hidsdi.h>

export module hid_device_module;

import std.core;

import globals;

import usages_text_module;
import item_type_module;

import raw_device_base_module;
import raw_device_module;
import raw_devices_module;

namespace hid
{
   using namespace std;
    
   export class hid_device : public raw_device
   {
      private: // variables

         using                      item_node         = HIDP_LINK_COLLECTION_NODE;

         HANDLE                     pointer           {};
         HIDD_ATTRIBUTES            attributes        {};
         HIDP_EXTENDED_ATTRIBUTES   attributes_extra  {};
         
         // For USB devices, the maximum string length is 126 wide characters 
         // (not including the terminating NULL character).         
         static const int           string_size       { 127 };
         wchar_t                    manufacturer      [ string_size ];
         wchar_t                    product           [ string_size ];
         wchar_t                    physical          [ string_size ];

         //ushort                     vendor            {};
         //ushort                     product           {};

         //wstring::size_type       string_size       { 127 };
         //wstring                  manufacturer      ( string_size , ' ' );
         
         vector< item >             items            {};
                  
         // concurrent points
         // x,y points x 5 + 3 buttons

      public: // functions
         
         // data
         /*
         hid_device( HANDLE in_pointer , raw_device_type in_type )
         : raw_device{ in_pointer , in_type }
         {
            HidD_GetAttributes        ( file_pointer , & attributes );
            HidD_GetManufacturerString( file_pointer , manufacturer , string_size );//manufacturer.data() , string_size );
            HidD_GetProductString     ( file_pointer , product      , string_size );
            HidD_GetPhysicalDescriptor( file_pointer , physical     , string_size );
            
            // convert collections to items
            vector< item_node > nodes {};

            nodes.resize( item_amount );

            HidP_GetLinkCollectionNodes( nodes.data() , & item_amount , data );
            
            items.resize( item_amount );

            //uint index {};

            for( const auto & node : nodes )
            {
               item new_item {};

               new_item.type   = item_type { node.CollectionType };
               new_item.page   = node.LinkUsagePage; // usages
               new_item.usage  = node.LinkUsage;
               new_item.alias  = node.IsAlias;
               new_item.amount = node.NumberOfChildren;

               // try catch out_of_range
               if( node.Parent ) 
                  new_item.origin = & items.at( node.Parent - 1);

               if( node.NextSibling )
                  new_item.next   = & items.at( node.NextSibling - 1);

               if( node.FirstChild )
               {
                  new_item.first  = & items.at( node.FirstChild - 1 );
               }

               //items.at( index ) = move( new_item );
               //index++;

               items.emplace_back( move( new_item ) );
            }

            using item_button = HIDP_BUTTON_CAPS;
            using item_value  = HIDP_VALUE_CAPS;

            ushort                button_amount       {};
            vector< item_button > button_input_items  {};
            vector< item_button > button_output_items {};
            vector< item_button > button_features     {};

            uint                  value_amount        {};
            vector< item_value >  value_input_items   {};
            vector< item_value >  value_output_items  {};
            vector< item_value >  value_features      {};

            button_input_items.resize ( input.button_amount );
            HidP_GetButtonCaps( HidP_Input   , button_input_items.data() , & input.button_amount   , data );

            button_output_items.resize( output.button_amount );
            HidP_GetButtonCaps( HidP_Output  , button_input_items.data() , & input.button_amount   , data );

            button_features.resize    ( feature.button_amount );
            HidP_GetButtonCaps( HidP_Feature , button_features.data()    , & feature.button_amount , data );


            value_input_items.resize  ( input.value_amount );
            HidP_GetValueCaps( HidP_Input    , value_input_items.data()  , & input.value_amount    , data );

            value_output_items.resize ( output.value_amount );
            HidP_GetValueCaps( HidP_Output   , value_output_items.data() , & output.value_amount   , data );

            value_features.resize     ( feature.value_amount ); 
            HidP_GetValueCaps( HidP_Feature  , value_features.data()     , & output.value_amount   , data );

            //for( auto & input_item : button_input_items )
                        //for each cap
            // id = cap.
         }
         */

         /*
         vector< item > _items() 
         { 
            return items; 
         }

         //~hid_device() { }
         */

         /*
         wstring text( item_type in_type )
         {
            using enum item_type;

            wstring text;

            switch( in_type )
            {
               case device:
               {
                  text =  L"manufacturer : ";
                  text += manufacturer;
                  text += L"\nproduct\t: ";
                  text += product;
                  text += L"\npage\t: ";
                  text += usages.page( page ); // page
                  text += L"\nusage\t: ";
                  text += usages.usage( page , usage ); // usage

                  return text;

               } break;

               case physical:
               case application:
               case logical:
               case report:
               case named_array:
               case usage_switch:
               case usage_modifier:
               {
                  text = L"type : ";
                  */

                  /*
                  text += collection_type_text.at( collection.CollectionType );
                  wcout << "    page : " << usages.page( collection.LinkUsagePage ).c_str() << endl;
                  wcout << "      usage : " << usages.usage( collection.LinkUsagePage , collection.LinkUsage ).c_str() << endl;

                  if( collection.IsAlias )
                     wcout << "    This link node is an alias of the next link node." << endl;

                  wcout << "    parent : " << collection.Parent << endl;
                  wcout << "    next sibling : " << collection.NextSibling << endl;

                  if( collection.NumberOfChildren )
                  {
                     wcout << "      amount of children : " << collection.NumberOfChildren << endl;
                     wcout << "      first child : " << collection.FirstChild << endl;
                     }
                  */

                  /*
                  return text;
               } break;

               default:
               {
                  return L"unknown collection type";
               } break;

            } // switch in_type

         } // text()
         */
   }; // class device

} // namespace hid



            //uint collection_id = 0;
            
               /*for( auto & collection : collections )
               {
                  // enum class tree_id { head , a , b , c 
                  // if collection.first 
                  //collection_id += 1;
               }*/
             
             //wcout << "button ammount : " << dec << button_caps.size() << endl;

             /*
               for( auto & button : button_caps )
               {
                  wcout << endl;

                  wcout << "collection : " << dec << button.LinkCollection << endl; // parent
                  wcout << " report id : " << dec << button.ReportID << endl; // unique data index for control, button or value
                  wcout << "  link page : " << usages.page( button.LinkUsagePage ).c_str() << endl;
                  wcout << "  link usage : " << usages.usage( button.LinkUsagePage , button.LinkUsage ).c_str() << endl;
                  wcout << "   page : " << usages.page( button.UsagePage ).c_str() << endl;
                  //wcout << "   type       : " << usages.type( button.LinkUsagePage , )

                  if( button.IsRange )
                  {
                     wcout << "usage min     : " << button.Range.UsageMin << endl;
                     wcout << "usage max     : " << button.Range.UsageMax << endl;

                     wcout << "data index min : " << button.Range.DataIndexMin << endl;
                     wcout << "data index max : " << button.Range.DataIndexMax << endl;
                  }
                  else if( button.IsStringRange )
                  {
                     wcout << "string min : " << button.Range.UsageMin << endl;
                     wcout << "string max : " << button.Range.UsageMax << endl;

                     wcout << "data index min : " << button.Range.DataIndexMin << endl;
                     wcout << "data index max : " << button.Range.DataIndexMax << endl;
                  }
                  else if( button.IsDesignatorRange )
                  {
                     wcout << "designator min : " << button.Range.DesignatorMin << endl;
                     wcout << "designator max : " << button.Range.DesignatorMax << endl;

                     wcout << "data index min : " << button.Range.DataIndexMin << endl;
                     wcout << "data index max : " << button.Range.DataIndexMax << endl;
                  }
                  else
                  {
                     wcout << "    usage : " << usages.usage( button.UsagePage , button.NotRange.Usage ).c_str() << endl;
                     //wcout << "type"

                     if( button.NotRange.StringIndex ) // "Do not emit String ID == 0" haftmann
                        wcout << "    string index : " << dec << button.NotRange.StringIndex << endl; // ushort

                     if( button.NotRange.DesignatorIndex )
                        wcout << "    designator index : " << button.NotRange.DesignatorIndex << endl; //ushort

                     wcout << "    data index : " << button.NotRange.DataIndex << endl; //ushort
                  }

                  // Array field : The bit field created by an Input , Output , or Feature main item which is declared as an Array.
                  // An array field contains the index of a Usage , not the Usage value.
                  wcout << "    bit field  : 0b" << std::bitset<16>( button.BitField ) << endl; // Usage determines the field’s purpose. 

                  if( button.IsAbsolute )
                     wcout << "    data is absolute not relative" << endl;

                  if( button.IsAlias )
                     wcout << "    button has a set of aliased usages" << endl;
               }
               */

               //wcout << endl;
               //wcout << "button feature ammount : " << dec << button_features.size() << endl;

               /*
               for( auto & feature : button_features )
               {
                  wcout << endl;

                  wcout << "collection : " << dec << feature.LinkCollection << endl;
                  wcout << "page       : " << usages.page( feature.UsagePage ).c_str() << endl;
                  wcout << "link page  : " << usages.page( feature.LinkUsagePage ).c_str() << endl;
                  wcout << "link usage : " << usages.usage( feature.LinkUsagePage , feature.LinkUsage ).c_str() << endl;

                  // button or value, data index for control
                  wcout << "report id        : " << feature.ReportID << endl;

                  if( feature.IsAlias )    wcout << " * button has a set of aliased usages" << endl;
                  //wcout << "bit field        : 0b" << std::bitset<16>( button.BitField ) << endl;
                  if( feature.IsAbsolute ) wcout << " * data is absolute not relative" << endl; // button is digital not analogue?

                  if( feature.IsRange )
                  {
                     wcout << "usage min : " << feature.Range.UsageMin << endl;
                     wcout << "usage max : " << feature.Range.UsageMax << endl;
                  }
                  else if( feature.IsStringRange )
                  {
                     wcout << "string min : " << feature.Range.UsageMin << endl;
                     wcout << "string max : " << feature.Range.UsageMax << endl;
                  }
                  else if( feature.IsDesignatorRange )
                  {
                     wcout << "designator min : " << feature.Range.DesignatorMin << endl;
                     wcout << "designator max : " << feature.Range.DesignatorMax << endl;
                  }
                  else
                  {
                     wcout << "usage          : " << usages.usage( feature.UsagePage , feature.NotRange.Usage ).c_str() << endl;

                     if( feature.NotRange.StringIndex ) // "Do not emit String ID == 0" haftmann
                        wcout << "string index   : " << dec << feature.NotRange.StringIndex << endl; // ushort

                     if( feature.NotRange.DesignatorIndex )
                        wcout << "designator index : " << feature.NotRange.DesignatorIndex << endl; //ushort

                     wcout << "data index     : " << feature.NotRange.DataIndex << endl; //ushort
                  }
               }
               */

               /*
               for( auto & value : value_caps )
               {
                  wcout << endl;

                  if( value.IsRange ) {}

                  wcout << "usage page : " << value.UsagePage << endl;
                  wcout << "report id  : " << value.ReportID << endl; // get_data
                  wcout << "IsAlias    : " << value.IsAlias << endl;

                  wcout << "BitField         : " << value.BitField << endl;
                  wcout << "LinkCollection   : " << value.LinkCollection << endl;   // A unique internal index pointer

                  wcout << "LinkUsage        : " << value.LinkUsage << endl;
                  wcout << "LinkUsagePage    : " << value.LinkUsagePage << endl;

                  wcout << "IsRange          : " << value.IsRange << endl;
                  wcout << "IsStringRange    : " << value.IsStringRange << endl;
                  wcout << "IsDesignatorRange: " << value.IsDesignatorRange << endl;
                  wcout << "IsAbsolute       : " << value.IsAbsolute << endl;

                  wcout << "HasNull          : " << value.HasNull << endl;        // Does this channel have a null report   union
                  wcout << "BitSize          : " << value.BitSize << endl;        // How many bits are devoted to this value?

                  wcout << "ReportCount      : " << value.ReportCount << endl;    // See Note below.  Usually set to 1.

                  wcout << "UnitsExp         : " << value.UnitsExp << endl;
                  wcout << "Units            : " << value.Units << endl;
                */

                  // This one tries to generate SI units
                  /*static const TCHAR * DecodeUnit( ULONG unit , int & exp ) {
                     static TCHAR buf[ 64 ];
                     switch( unit ) {
                        case 0x11: exp-=2; return T( "m" );     // meter
                        case 0x101: exp-=3; return T( "kg" );   // kilo gram
                        case 0x1001: return T( "s" );           // second
                        case 0xF011: exp-=2; return T( "m/s" ); // 
                        case 0xF111: exp-=5; return T( "mN" );
                        case 0xE011: exp-=2; return T( "m/s²" );
                        case 0xE111: exp-=5; return T( "N" );
                        case 0xE121: exp-=7; return T( "J" );  // joule
                        case 0xE012: return T( "rad/s²" );
                        case 0xF0D121: exp-=7; return T( "V" ); // volt
                        case 0x100001: return T( "A" );         // amp
                        case 0xE1F1: exp-=1; return T( "Pa" );
                     }*/

                     /*
                  wcout << "LogicalMin       : " << value.LogicalMin << endl;
                  wcout << "LogicalMax       : " << value.LogicalMax << endl;
                  wcout << "PhysicalMin      : " << value.PhysicalMin << endl;
                  wcout << "PhysicalMax      : " << value.PhysicalMax << endl;
               }*/

//wcout << "path : " << path.data() << endl;
//wcout << "page  : " << usages.page(caps.UsagePage).c_str() << endl;
//wcout << "usage : " << usages.usage( caps.UsagePage , caps.Usage ).c_str() << endl;
//wcout << "vendor     : 0x" << hex << attributes.VendorID << " , product : 0x" << attributes.ProductID << endl;

//collection_text += format( L"manufacturer : {}" , manufacturer );//  endl;
//collection_text += format( L"\nproduct      : {}" , product );// << endl;
