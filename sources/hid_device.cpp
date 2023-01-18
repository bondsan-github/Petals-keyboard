#include "..\headers\hid_device.h"

#include "..\headers\utility.h"
#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

#include <hidpi.h>

#include <fstream>
#include <iostream>

namespace hid
{
    hid_device::hid_device( HANDLE in_device )
    {
        //OutputDebugString( L"hid_device::parametertised constructor\n" );
        //https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/

        raw_handle = in_device;

        NTSTATUS result{ HIDP_STATUS_INVALID_PREPARSED_DATA };
        uint data_size{ 0 };

        //RIDI_DEVICEINFO
        GetRawInputDeviceInfoW( raw_handle , request.data , nullptr , &data_size );

        data_preparsed.resize( data_size );

        GetRawInputDeviceInfoW( raw_handle , request.data , data_preparsed.data() , &data_size );

        //GetPreparsedData( device_pointer , data );
        result = HidP_GetCaps( reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) , &capabilities );

        page  = capabilities.UsagePage;
        usage = capabilities.Usage;

        unsigned int structure_size = sizeof( RID_DEVICE_INFO );

        GetRawInputDeviceInfoW( raw_handle , request.info , &info , &structure_size );

        identity.vendor = info.hid.dwVendorId;
        identity.product = info.hid.dwProductId;

        std::wstring message;
        message = L" vendor: " + std::to_wstring(identity.vendor);
        message += L"  product: " + std::to_wstring( identity.product);

        OutputDebugStringW( message.c_str() );
    }

    bool hid_device::is_multi_touch()
    {
        return ( page == HID_USAGE_PAGE_DIGITIZER && usage == HID_USAGE_DIGITIZER_TOUCH_PAD );
    }

    hid_device::~hid_device()
    {
        //if( device_pointer ) CloseHandle( device_pointer );
    }

    std::wstring hid_device::get_path()
    {
        // get device path character amount
        uint return_value = GetRawInputDeviceInfoW( raw_handle , request.path , 0 , &path_char_amount );

        path.resize( path_char_amount );

        return_value = 0;
        // get device path // use wchar_t[] buffer instead of string if driver issue
        return_value = GetRawInputDeviceInfoW( raw_handle , request.path , path.data() , &path_char_amount );

        std::wstring debug_string = L"\n";
        debug_string += path.data();
        debug_string += L"\n";
        OutputDebugStringW( debug_string.data() );

        return path;
    }
    
    void hid_device::collect_information()
    {
        NTSTATUS result { HIDP_STATUS_INVALID_PREPARSED_DATA };

        get_path();       
        
        // cannot have exclusive file access
        //https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use
        
        // open i_o device for query 
        file_handle = CreateFileW( path.data() ,
                                   0 ,//GENERIC_READ | GENERIC_WRITE ,  // access
                                   FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                   0 ,                                  // security
                                   OPEN_EXISTING ,                      // creation
                                   0 ,//FILE_ATTRIBUTE_NORMAL ,         // flags
                                   0 );                                 // template
        
        if( file_handle == INVALID_HANDLE_VALUE ) print_error( L"unable to open device" );
        
        HidD_GetAttributes(         file_handle , & attributes );
        HidD_GetManufacturerString( file_handle , manufacturer_buffer , string_size );
        HidD_GetProductString(      file_handle , product_buffer      , string_size );
        HidD_GetPhysicalDescriptor( file_handle , physical_buffer     , string_size );

        manufacturer = manufacturer_buffer;
        product = product_buffer;
        physical = physical_buffer;

        set_text_device();

        // -- collections -------------------------------------------
        ulong collection_amount = capabilities.NumberLinkCollectionNodes;

        PHIDP_PREPARSED_DATA data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() );

        _HIDP_LINK_COLLECTION_NODE * nodes = new _HIDP_LINK_COLLECTION_NODE[ collection_amount ];
        
        result = HidP_GetLinkCollectionNodes( nodes , &collection_amount, data );
        if( result == HIDP_STATUS_BUFFER_TOO_SMALL ) error_exit( L"collection buffer size error" );
        
        collections.add_collections( nodes , capabilities.NumberLinkCollectionNodes );
        
        delete[] nodes;
        // ---------------------------------------------

        _HIDP_BUTTON_CAPS * button_array { nullptr };
        _HIDP_VALUE_CAPS * value_array{ nullptr };

        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberInputButtonCaps ];
        result = HidP_GetButtonCaps( HidP_Input , button_array , & capabilities.NumberInputButtonCaps , data );
        collections.add_buttons( this , item_type::input , button_array , capabilities.NumberInputButtonCaps );
        delete[] button_array;

        value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberInputValueCaps ];
        result = HidP_GetValueCaps( HidP_Input , value_array , &capabilities.NumberInputValueCaps , data );
        collections.add_values( this , item_type::input , value_array , capabilities.NumberInputValueCaps );
        delete[] value_array;
        
        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberOutputButtonCaps ];
        result = HidP_GetButtonCaps( HidP_Output , button_array , &capabilities.NumberOutputButtonCaps , data );
        collections.add_buttons( this , item_type::output , button_array , capabilities.NumberOutputButtonCaps );
        delete[] button_array;

        value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberOutputValueCaps ];
        result = HidP_GetValueCaps( HidP_Output , value_array , &capabilities.NumberOutputValueCaps , data );
        collections.add_values( this , item_type::output , value_array , capabilities.NumberOutputValueCaps );
        delete[] value_array;

        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberFeatureButtonCaps ];
        result = HidP_GetButtonCaps( HidP_Feature , button_array , &capabilities.NumberFeatureButtonCaps , data );
        collections.add_buttons( this , item_type::feature , button_array , capabilities.NumberFeatureButtonCaps );
        delete[] button_array;

        value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberFeatureValueCaps ];
        result = HidP_GetValueCaps( HidP_Feature , value_array , &capabilities.NumberFeatureValueCaps , data );
        collections.add_values( this , item_type::feature , value_array , capabilities.NumberFeatureValueCaps );
        delete[] value_array;

        collections.set_collections_positions( *this );

        //CloseHandle(device_pointer);
        //device_pointer = INVALID_HANDLE_VALUE;
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

        information.set_content( content );
        information.set_position_top_left( text_position );
        information.set_layout_size( text_layout_size );
        information.set_font_size( text_font_size );
        information.set_font_colour( text_font_colour );
        //information.set_rectangle_line_colour( rectangle_line_colour );

        // += attributes.VendorID;
        // += attributes.ProductID;
        // += attributes.VersionNumber;
        // += physical
    }

    void hid_device::set_if_display_information( const bool in_bool )
    {
        draw_information = in_bool; 
    }

    void hid_device::update( RAWHID input_report )
    {

        //if( HidD_GetInputReport( device_pointer , buffer , buffer_size ) ) {}
        //else print_error(L"\n unable to get input report" );

        collections.update( input_report );
    }

    void hid_device::draw()
    {
    // 1. transparent full screen draw contacts
        if( draw_information )
        {
            information.draw();
            collections.draw();
            
            //lines.draw
        }
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