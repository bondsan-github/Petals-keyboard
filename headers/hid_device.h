#pragma once

#include < vector >

#include < hidsdi.h >
#include < hidpi.h >

#include "..\headers\shared_graphics.h"
#include "..\headers\shared_write.h"

#include "..\headers\globals.h"
#include "..\headers\raw_device.h"
#include "..\headers\item.h"
#include "..\headers\line.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    class hid_device : public raw_device , public shared_graphics , public shared_write
    {
        HIDD_ATTRIBUTES            attributes { .Size = sizeof( HIDD_ATTRIBUTES ) };
        HIDP_EXTENDED_ATTRIBUTES   attributes_extra {};

        // For USB devices, the maximum string length is 126 wide characters 
        // (not including the terminating NULL character).         
        static const int string_size{ 127 };
        wchar_t          manufacturer[ string_size ]{};
        wchar_t          product[ string_size ]{};
        wchar_t          physical[ string_size ]{};
        //wstring::size_type string_size  { 127 };
        //wstring            manufacturer ( string_size , ' ' );

        vector< main_item > items{};

        void gather_information();
         // data
         // concurrent points
         // x,y points x 5 + 3 buttons

        vector< line > lines{};

        bool        draw_information{ true };

        wstring     text_font{ L"Cascasia code" }; // { L"Sitka" };
        float       text_size{ 10.0f };
        colours     text_colour{ colours::White };
        area        text_area{};
        float       column{};
        ushort      column_amount{};
        float       row{};
        ushort      row_amount{};

        uint        index{};

        public:

        hid_device( HANDLE in_device ) : raw_device( in_device )
        {
            if( is_multi_touch() ) 
            {
                gather_information();

                write_ptr->add( text_device() );

                // graphics // screen_width * position_x [ 0.000000..1.0000000 ]
                column_amount = 12;
                row_amount    = 12;

                //sheet_grid.initialise( column_amount , row_amount );

                //text_area = sheet_grid.cell_size();
                column    = 1;
                row       = 1;
            }
        }

        void texts_items_main()
        {
            //for( auto & item : items )
              //  write_ptr->add( item.text() );
        }

        void display_information()
        {
            draw_information = ! draw_information;  // switch
        }

        void draw()
        {
            if( draw_information )
            {
                //write::draw();

                //graphics_ptr.
            }
        }

        wstring text_device()
        {
            wstring text{};

            text =  L"manufacturer : ";
            text += manufacturer;
            text += L"\nproduct    : ";
            text += product;
            text += L"\npage       : ";
            text += usages.page( page );
            text += L"\nusage      : ";
            text += usages.usage( page , usage );

            // += 
            //attributes.VendorID;
            //attributes.ProductID;
            //attributes.VersionNumber;

            // += physical

            return text;
        }

        void texts_items_input()
        {
            for( auto & input : input.buttons )
                write_ptr->add( input.text() );
        }

    }; // class device

    void hid_device::gather_information()
    {
        HidD_GetAttributes( file_pointer , &attributes );
        HidD_GetManufacturerString( file_pointer , manufacturer , string_size );//manufacturer.data() , string_size );
        HidD_GetProductString( file_pointer , product , string_size );
        HidD_GetPhysicalDescriptor( file_pointer , physical , string_size );

        vector< HIDP_LINK_COLLECTION_NODE > nodes{};

        nodes.resize( item_amount );

        HidP_GetLinkCollectionNodes( nodes.data() , &item_amount , data );

        items.resize( item_amount );

        uint index {};

        for( const auto & node : nodes )
        {
            main_item new_item;

            new_item.type     = item_type{ node.CollectionType };
            new_item.page     = node.LinkUsagePage; // usages
            new_item.usage    = node.LinkUsage;
            new_item.is_alias = node.IsAlias;
            new_item.amount   = node.NumberOfChildren;

            new_item.origin   = node.Parent;
            new_item.next     = node.NextSibling;
            new_item.first    = node.FirstChild;

            //using link = vector< item >::reference;

            /*
            if( node.Parent ) // one parent , above
               new_item.origin = & items.at( node.Parent - 1 );

            if( node.NextSibling ) // to right
               new_item.next   = & items.at( node.NextSibling - 1 );

            if( node.FirstChild ) // left-most
               new_item.first  = & items.at( node.FirstChild - 1 );
            */
            items.at( index ) = move( new_item );

            index++;
        }

        using button_item = HIDP_BUTTON_CAPS;
        using value_item  = HIDP_VALUE_CAPS;

        vector< button_item > inputs{};
        vector< value_item >  input_values{};

        vector< button_item > output_buttons{};
        vector< value_item >  output_values{};

        vector< button_item > button_features{};
        vector< value_item >  value_features{};

        inputs.resize( input.button_amount );
        HidP_GetButtonCaps( HidP_Input , inputs.data() , &input.button_amount , data );

        input_values.resize( input.value_amount );
        HidP_GetValueCaps( HidP_Input , input_values.data() , &input.value_amount , data );

        output_buttons.resize( output.button_amount );
        HidP_GetButtonCaps( HidP_Output , inputs.data() , &input.button_amount , data );

        output_values.resize( output.value_amount );
        HidP_GetValueCaps( HidP_Output , output_values.data() , &output.value_amount , data );

        button_features.resize( feature.button_amount );
        HidP_GetButtonCaps( HidP_Feature , button_features.data() , &feature.button_amount , data );

        value_features.resize( feature.value_amount );
        HidP_GetValueCaps( HidP_Feature , value_features.data() , &output.value_amount , data );

        for( auto & input : inputs )
        {
            local_item new_item{};

            // type = input
            new_item.page          = input.UsagePage;

            new_item.report        = input.ReportID;
            new_item.report_amount = input.ReportCount; // Available in API version >= 2 only.

            new_item.bit_field     = input.BitField;

            new_item.is_alias      = input.IsAlias;

            new_item.origin          = input.LinkCollection;
            new_item.origin_page     = input.LinkUsagePage;
            new_item.origin_usage    = input.LinkUsage;

            new_item.is_range        = input.IsRange;
            //new_item.usage         = input.NotRange.Usage;
            new_item.is_absolute     = input.IsAbsolute;

            new_item.has_designators = input.IsDesignatorRange;
            new_item.has_strings     = input.IsStringRange;

            if( new_item.is_range )
            {
                new_item.usages.begin = input.Range.UsageMin;
                new_item.usages.end   = input.Range.UsageMax;

                new_item.datas.begin  = input.Range.DataIndexMin;
                new_item.datas.end    = input.Range.DataIndexMax;
            }
            else
            {
                new_item.usage = input.NotRange.Usage;
                new_item.data  = input.NotRange.DataIndex;
            }

            if( new_item.is_alias )
            {

            }
            else
            {

            }

            if( new_item.has_strings )
            {
                new_item.strings.begin = input.Range.StringMin;
                new_item.strings.end   = input.Range.StringMax;
                  //HidD_GetIndexedString
            }
            else
            {
                new_item.string = input.NotRange.StringIndex;
            }


            if( new_item.has_designators )
            {
                new_item.designators.begin = input.Range.DesignatorMin;
                new_item.designators.end   = input.Range.DesignatorMax;
            }
            else
            {
                new_item.designator = input.NotRange.DesignatorIndex;
            }

            //items.push_back( move( new_item ) );
            this->input.buttons.emplace_back( move( new_item ) );
        } 

        for( auto & input_value : input_values )
        {
            //value new_value {};
            //input_value.BitField;
        }

        //new_item.origin = input.LinkCollection; vector<main_item>::reference

        //for each cap
        // id = cap.
    }

} // namespace hid

/*
                  point text_device_position    = grid_.cell( column , row );

                  row += 2;
                  point text_item_main_position = grid_.cell( column , row );

                  column += 2;
                  point text_item_local_position = grid_.cell( column , row );

                  //for( auto & device : input.devices() )
                  //{

                 // device 0
              hid_device & device = input.devices().front();

              // text device 0
              write.add( device.text_device() , text_device_position , text_size , text_colour , text_area , text_font );

              // text items 0
              wstring text_first = device.main_items().begin()->text();

              // first main item
              write.add( text_first , text_item_main_position , text_size , text_colour , text_area , text_font );

              // line from device to first main item
              point a = write.mid_points( 0 ).bottom;
              point b = write.mid_points( 1 ).top;

              main_window.paint.add_line( a , b , 0.5 , colours::White );

              // items main
              vector< main_item >::const_iterator item = device.main_items().begin();

              // second item
              item++;

              // for all other items
              for( ; item != device.main_items().end() ; item++ )
              {
                  write.add( item->text() , grid_.cell( column , row ) , text_size , text_colour , text_area );

                  row += 2;
              }

              for( auto & text : write.texts() )
              {
                  if( text.item->next )
                  {
                      a = text.mid_points
                          b = write.mid_points( item->next ).top;
                  }
              }

              column = 5;
              row    = 3;

              for( auto & text : device.texts_items_input() )
              {
                  write.add( text , grid_.cell( column , row ) , text_size , text_colour , text_area );
                  row += 2;
              }
              //point a = *text;//&text.mid_points( text ).bottom;
              //point b = write.mid_points( 1 ).top;
              //main_window.paint.add_line( a , b , 0.5 , colours::White );

           //} if devices input empty
           */








// move constructor
      //hid_device( hid_device && destination ) //noexcept

      //~hid_device() { delete [] manufacturer }


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
                  wcout << "LinkCollection   : " << value.LinkCollection << endl;   // A unique internal index window_ptr

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

   /*
            case physical:
            case application:
            case logical:
            case report:
            case named_array:
            case usage_switch:
            case usage_modifier:
            */