#include "..\headers\hid_device.h"

#include "..\headers\utility.h"
#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

#include <hidpi.h>

namespace hid
{
    hid_device::hid_device( const hid_raw_device & raw_device )
    {
        OutputDebugString( L"hid_device::hid_raw_device constructor\n" );

        device_pointer   = raw_device.get_device_pointer();
        data_preparsed   = std::move( raw_device.get_preparsed_data() );
        //data_preparsed   = raw_device.get_preparsed_data();
        capabilities     = raw_device.get_capabilities();
        page             = raw_device.get_page();
        usage            = raw_device.get_usage();
    }
    
    void hid_device::collect_information()
    {
        NTSTATUS result { HIDP_STATUS_INVALID_PREPARSED_DATA };

        // get device path character amount
        uint return_value = GetRawInputDeviceInfoW( device_pointer , request.path , 0 , & path_char_amount );
        if( return_value != 0 ) error_exit(L"unable to get device path byte count");

        device_path.resize( path_char_amount );

        return_value = 0;
        // get device path // use wchar_t[] buffer instead of string if driver issue
        return_value = GetRawInputDeviceInfoW( device_pointer , request.path , device_path.data() , & path_char_amount );
        if( return_value <= 0 ) error_exit( L"unable to get device path" );

        //OutputDebugString( path.data() );

        // open i_o device for query 
        device_pointer = CreateFileW( device_path.data() ,
                                    0 ,                                  // access
                                    FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                    0 ,                                  // security
                                    OPEN_EXISTING ,                      // creation
                                    FILE_ATTRIBUTE_NORMAL ,              // flags
                                    0 );                                 // template

        HidD_GetAttributes(         device_pointer , & attributes );
        HidD_GetManufacturerString( device_pointer , manufacturer_buffer , string_size );
        HidD_GetProductString(      device_pointer , product_buffer      , string_size );
        HidD_GetPhysicalDescriptor( device_pointer , physical_buffer     , string_size );

        manufacturer = manufacturer_buffer;
        product = product_buffer;
        physical = physical_buffer;

        set_text_device();

        // -- collections -------------------------------------------
        collection_amount = capabilities.NumberLinkCollectionNodes;
        collections.resize( collection_amount );

        PHIDP_PREPARSED_DATA data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() );

        _HIDP_LINK_COLLECTION_NODE * nodes = new _HIDP_LINK_COLLECTION_NODE[ collection_amount ];
        
        result = HidP_GetLinkCollectionNodes( nodes , &collection_amount , data );
        if( result == HIDP_STATUS_BUFFER_TOO_SMALL ) error_exit( L"collection buffer size error" );
        
        uint index{ 0 };
        for( auto & node : collections )
        {
            node = nodes[ index ];
            index++;
        }

        delete[] nodes;
        set_text_collections();
        // -- collections -------------------------------------------


        _HIDP_BUTTON_CAPS * input_button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberInputButtonCaps ];
        input_buttons.resize( capabilities.NumberInputButtonCaps );
        result = HidP_GetButtonCaps( HidP_Input , input_button_array , & capabilities.NumberInputButtonCaps , data );

        index = 0;
        for( auto & button : input_buttons )
        {
            button = input_button_array[ index ];
            index++;
        }

        delete[] input_button_array;
        set_text_input_buttons();

        _HIDP_VALUE_CAPS * input_value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberInputValueCaps ];
        input_values.resize( capabilities.NumberInputValueCaps );
        result = HidP_GetValueCaps( HidP_Input , input_value_array , &capabilities.NumberInputValueCaps , data );
        
        index = 0;
        for( auto & value : input_values )
        {
            value = input_value_array[ index ];
            index++;
        }

        delete[] input_value_array;
        //set_text_input_values();

        output_buttons.resize( capabilities.NumberOutputButtonCaps );
        result = HidP_GetButtonCaps( HidP_Output , output_buttons.data() , &capabilities.NumberOutputButtonCaps , data );

        output_values.resize( capabilities.NumberOutputValueCaps );
        result = HidP_GetValueCaps( HidP_Output , output_values.data() , &capabilities.NumberOutputValueCaps , data );

        button_features.resize( capabilities.NumberFeatureButtonCaps );
        result = HidP_GetButtonCaps( HidP_Feature , button_features.data() , &capabilities.NumberFeatureButtonCaps , data );

        value_features.resize( capabilities.NumberFeatureValueCaps );
        result = HidP_GetValueCaps( HidP_Feature , value_features.data() , &capabilities.NumberFeatureValueCaps , data );

            //button.IsAlias ); // does button have multiple usages
            //button.Range.StringMin ); //HidD_GetIndexedString
            //button.Range.DesignatorMin ); // physical descriptor
    }

    hid_collection & hid_device::get_collection( const hid_button & in_button )
    {
        for( auto & node : collections )
        {
            if( node.LinkUsagePage == in_button.LinkUsagePage and 
                node.LinkUsage     == in_button.LinkUsage )
            {
                return node;
                break;
            }
        }
    }

    void hid_device::set_text_input_buttons()
    {
        vertex position {};// = collection.right , collection.top
        //uint index { 1 };

        //for( auto & button : input_buttons  )
        for( uint index = 0; index < input_buttons.size(); index++ )
        {
            position.y = get_collection( input_buttons.at(index) ).get_text_position_top();

            position.x = get_collection( input_buttons.at( index ) ).get_text_position_right();
            position.x += information_spacing.x;
            if( index > 0 )position.x += input_buttons.at( index - 1u ).get_text_position_right();
            position.x += information_spacing.x;

            input_buttons.at( index ).set_information_text();
            input_buttons.at( index ).set_text_position( position );
            
            //position.x += information_spacing.x;
        }
    }

    void hid_device::set_text_collections()
    {
        vertex position 
        { 
            device_text_position.x ,
            device_information.get_bottom() + collection_text_spacer
        };

        for( auto & node : collections )
        {
            node.set_information_text();
            node.set_text_position( position );

            position.y = node.get_text_position_bottom() + collection_text_spacer;
        }
    }

    void hid_device::set_text_device()
    {
        std::wstring content;

        content =  L"manufacturer\t: ";
        content += manufacturer;
        content += L"\nproduct\t\t: ";
        content += product;
        content += L"\npage\t\t: ";
        content += locate::get_usages().page( page );
        content += L"\nusage\t\t: ";
        content += locate::get_usages().usage( page , usage );

        device_information.set_content( content );
        device_information.set_position_top_left( device_text_position );
        device_information.set_layout_size( device_text_layout_size );
        device_information.set_font_size( device_text_font_size );
        device_information.set_font_colour( device_text_font_colour );
        //information.set_rectangle_line_colour( rectangle_line_colour );

        // += attributes.VendorID;
        // += attributes.ProductID;
        // += attributes.VersionNumber;
        // += physical
    }
   

    void hid_device::set_text_input()
    {
        
    }

    void hid_device::set_if_display_information( const bool in_bool )
    {
        draw_information = in_bool; 
    }

    void hid_device::draw()
    {
    // 1. transparent full screen draw contacts
        if( draw_information )
        {
            device_information.draw();
            
            for( const auto & item : collections ) item.draw();
            for( const auto & button : input_buttons ) button.draw();
            
            //lines.draw
        }
    }
    
    void hid_device::texts_items_input()
    {
        //for( auto & input : input.buttons )
           // write_ptr->add( input.text() );
    }

    
}

//using link = vector< item >::reference;
            /*
            if( node.Parent ) // one parent , above
               new_item.origin = & items.at( node.Parent - 1 );

            if( node.NextSibling ) // to right
               new_item.next   = & items.at( node.NextSibling - 1 );

            if( node.FirstChild ) // left-most
               new_item.first  = & items.at( node.FirstChild - 1 );
            */
            //collection.push_back( move( new_collection ) );//at( index ) = move( new_item );
            
// move constructor
      //hid_device( hid_device && destination ) //noexcept
      //~hid_device() { delete [] manufacturer }
            //uint collection_id = 0;

               /*for( auto & hid_collection : collections )
               {
                  // enum class tree_id { head , a , b , c
                  // if hid_collection.first
                  //collection_id += 1;
               }*/

             //wcout << "button ammount : " << dec << button_caps.size() << endl;

             /*
               for( auto & button : button_caps )
                  // Array field : The bit field created by an Input , Output , or Feature main item which is declared as an Array.
                  // An array field contains the index of a Usage , not the Usage value.
                  bit field  :  // Usage determines the field’s purpose.
               */
                            
               /*
               for( auto & feature : button_features )

                  wcout << "hid_collection : " << dec << feature.LinkCollection << endl;
                  wcout << "page       : " << usages.page( feature.UsagePage ).c_str() << endl;
                  wcout << "link page  : " << usages.page( feature.LinkUsagePage ).c_str() << endl;
                  wcout << "link usage : " << usages.usage( feature.LinkUsagePage , feature.LinkUsage ).c_str() << endl;

                  // button or value, data index for control
                  wcout << "report id        : " << feature.ReportID << endl;
                    wcout << "usage          : " << usages.usage( feature.UsagePage , feature.NotRange.Usage ).c_str() << endl;
                     if( feature.NotRange.StringIndex ) // "Do not emit String ID == 0" haftmann
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

//wcout << "path : " << path.data() << endl;
//wcout << "vendor     : 0x" << hex << attributes.VendorID << " , product : 0x" << attributes.ProductID << endl;

   /*       case physical:
            case application:
            case logical:
            case report:
            case named_array:
            case usage_switch:
            case usage_modifier:    */