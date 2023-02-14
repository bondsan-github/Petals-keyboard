#include "..\headers\hid_device.h"

#include "..\headers\utility.h"
#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

#include <hidpi.h>

#include <fstream>
#include <iostream>

#include <fileapifromapp.h>

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

        //std::wstring message;
        //message = L" vendor: " + std::to_wstring( identity.vendor );
        //message += L"  product: " + std::to_wstring( identity.product );
        //OutputDebugStringW( message.c_str() );

        // find in collections 0x0d , 0x55 Contact Count Maximum
        // contacts.resize( contacts_maximum );
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

        /*
        std::wstring debug_string = L"\n";
        debug_string += path.data();
        debug_string += L"\n";
        OutputDebugStringW( debug_string.data() ); */

        return path;
    }

    void hid_device::collect_information()
    {
        NTSTATUS result{ HIDP_STATUS_INVALID_PREPARSED_DATA };

        get_path();

        // cannot have exclusive file access
        //https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use

        // open i_o device for query 
        file_handle = CreateFileW( path.c_str() ,
                                   0 ,//GENERIC_READ ,//| GENERIC_WRITE ,   // access
                                   FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                   ( LPSECURITY_ATTRIBUTES ) 0 ,        // security
                                   OPEN_EXISTING ,                      // creation
                                   FILE_FLAG_OVERLAPPED , //0 ,//FILE_ATTRIBUTE_NORMAL ,         // flags
                                   0 );                                 // template

        if( file_handle == INVALID_HANDLE_VALUE ) print_error( L"unable to open device" );

        HidD_GetAttributes( file_handle , &attributes );
        HidD_GetManufacturerString( file_handle , manufacturer_buffer , string_size );
        HidD_GetProductString( file_handle , product_buffer , string_size );
        HidD_GetPhysicalDescriptor( file_handle , physical_buffer , string_size );

        //SeTcbPrivilege 

        //BY_HANDLE_FILE_INFORMATION file_information {};
        //GetFileInformationByHandle( file_handle, &file_information);

        //CloseHandle( file_handle );

        manufacturer = manufacturer_buffer;
        product      = product_buffer;
        physical     = physical_buffer;

        /*ulong buffer_amount{0};
        HidD_GetNumInputBuffers( file_handle, &buffer_amount);
        std::wstring message;
        message = L"\n buffer amount: " + std::to_wstring( buffer_amount ); // as default of 32
        OutputDebugStringW( message.data() );*/

        set_text_device();

        // -- collections -------------------------------------------
        ulong collection_amount = capabilities.NumberLinkCollectionNodes;

        PHIDP_PREPARSED_DATA data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() );

        _HIDP_LINK_COLLECTION_NODE * nodes = new _HIDP_LINK_COLLECTION_NODE[ collection_amount ];

        result = HidP_GetLinkCollectionNodes( nodes , &collection_amount , data );
        if( result == HIDP_STATUS_BUFFER_TOO_SMALL ) error_exit( L"collection buffer size error" );

        collections.add_collections( nodes , capabilities.NumberLinkCollectionNodes );

        delete[] nodes;
        // ---------------------------------------------

        _HIDP_BUTTON_CAPS * button_array{ nullptr };
        _HIDP_VALUE_CAPS * value_array{ nullptr };

        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberInputButtonCaps ];
        result = HidP_GetButtonCaps( HidP_Input , button_array , &capabilities.NumberInputButtonCaps , data );
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

        //if( HidD_GetInputReport( device_pointer , buffer , buffer_size ) ) {}
        //else print_error(L"\n unable to get input report" );

        //circles.resize( collections.contacts_maximum() );

        //HidD_SetNumInputBuffers( file_handle , 256 );

        /*ulong buffer_amount{0};
        HidD_GetNumInputBuffers( file_handle, &buffer_amount);
        std::wstring message = L"\nbuffer_amount: " + std::to_wstring( buffer_amount );
        OutputDebugStringW( message.data() );*/

        //D2D1_UNIT_MODE GetUnitMode();
        screen_dpi = locate::get_graphics().get_dpi();
        touchpad_resolution = collections.get_resolution();

        D2D_SIZE_F screen_size_dips = locate::get_graphics().get_size_dips();
            
        // To convert a physical pixel to a DIP, use this formula:
        // dip = ( physical pixel × 96 ) / DPI

         // screen 3840 x 2160
         // pad 1496 x 968
         // 1496 * 2.57 = 3840 
         // pad_to_screen = screen_resolution / pad_resolution

        // want to use full touchpad resolution mapped to full screen space 
        // maximum,maximum coordinate on touchpad = screen_maximum_x, screen_maximum_y

        // touchpad_resolution.minimum = x , .maximum = y
        pad_to_screen_ratio.width  = screen_size_dips.width  / touchpad_resolution.minimum;
        pad_to_screen_ratio.height = screen_size_dips.height / touchpad_resolution.maximum;

        // if( ten_finger_input )
            // else
        //contacts.resize( contact_amount );
        //contacts.resize( 1 );

        // array_itr_start = array_itr_end;
        // array_itr_end += 4;
        // array = copy( input_types.begin )
        uint input_index_begin = 0;
        uint input_index_end = 0;
        // 10 / 4 = 2.5
        // 10 / 5 = 2

        contacts[ 0 ].set_inputs( { L"q" , L"w" , L"a" , L"s" } );
        contacts[ 1 ].set_inputs( { L"e" , L"r" , L"d" , L"f" } );
        contacts[ 2 ].set_inputs( { L"t" , L"y" , L"g" , L"h" } );
        contacts[ 3 ].set_inputs( { L"u" , L"i" , L"j" , L"k" } );
        contacts[ 4 ].set_inputs( { L"o" , L"p" , L"l" , L"z" } );
        /*
        for( auto & contact : contacts )
        {
            // contact
            //split custom_types::input_types between contacts
        }*/

        debug_text.set_position_top_left( { 300, 10 } );
        debug_text.set_font_colour( D2D1::ColorF::White );
        debug_text.set_layout_size( { 500, 100 });
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

        ulong input_amount = HidP_MaxDataListLength( HidP_Input ,
                                                     reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) );

        content += L"\ninput amount\t: " + std::to_wstring( input_amount );

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

    void hid_device::update()
    {
        /*
        HANDLE read_file_handle =CreateFileFromAppW( path.c_str(),
                                                     GENERIC_READ ,//| GENERIC_WRITE ,   // access
                                                     FILE_SHARE_READ , //| FILE_SHARE_WRITE // share
                                                     0 ,// security
                                                     OPEN_EXISTING , // creation
                                                     0 , //FILE_FLAG_OVERLAPPED , //0 ,//FILE_ATTRIBUTE_NORMAL , // flags
                                                     0 );// template

        if( read_file_handle == INVALID_HANDLE_VALUE ) print_error( L"unable to open device" );

        char * buffer = new char[ capabilities.InputReportByteLength + 1 ] {};

        buffer[ 0 ]=30; // 0x1e
        int buffer_size{ 0 };
        buffer_size = sizeof buffer;
        BOOL result = HidD_GetInputReport( read_file_handle , &buffer , buffer_size );
        if( not result ) print_error( L"\nget input report error" );

        //ulong max = get_value( 0x0d , 0x55, input_report );
        long contact_amount = get_value( 0x0d , 0x54 , buffer );

        std::wstring message = L"\ncontact id: " + std::to_wstring( id );
        message += L" x: " + std::to_wstring( x );
        message += L" y: " + std::to_wstring( y );
        message += L" contact_amount: " + std::to_wstring( contact_amount );
        message += L" buffer size: " + std::to_wstring( buffer_size );
        OutputDebugStringW( message.data() );
        */

        //data[0] = \ &f00000000 report id 
                //data[1] = x 
                //data[] = 
                //data[] = 
                //data[] = 
                //https://github.com/torvalds/linux/tree/master/drivers/hid
                //https://eleccelerator.com/tutorial-about-usb-hid-report-descriptors/
                //data.clear();
    }

    void hid_device::update/*_unbufferd*/( RAWINPUT * input_report )
    {
        //contact_identifier = value_contact_identifier->get_value();
        //collections.update_input( input_report );

        float x  = static_cast< float >( get_value_unscaled( 0x01 , 0x30 , &input_report->data.hid ) ); // x
        float y  = static_cast< float >( get_value_unscaled( 0x01 , 0x31 , &input_report->data.hid ) ); // y
        float id = static_cast< float >( get_value_unscaled( 0x0d , 0x51 , &input_report->data.hid ) ); // id

        update_contact( id , x , y );

        std::wstring message = L"\nx: " + std::to_wstring( x ) += L" y: " + std::to_wstring( y );
        OutputDebugStringW( message.data() );
    }

    void hid_device::update_contact( ulong in_identifier , float in_x , float in_y )
    {
        if( in_identifier >= 0 and in_identifier < contacts.size() )
            contacts.at( in_identifier ).update( static_cast< float >( in_x ) ,
                                                 static_cast< float >( in_y ) );
    }

    void hid_device::update_buffered( RAWINPUT ** in_rawinput_array , uint in_report_amount )
    {
        float x  { 0 };
        float y  { 0 };
        float id { 0 };

        //std::wstring message = L"\n";
        

        for( uint index{ 0 }; index < in_report_amount; index++ )
        {
            collections.update_input( in_rawinput_array[ index ] );

            x  = static_cast< float >( get_value_unscaled( 0x01 , 0x30 , &in_rawinput_array[ index ]->data.hid ) ); // x
            y  = static_cast< float >( get_value_unscaled( 0x01 , 0x31 , &in_rawinput_array[ index ]->data.hid ) ); // y
            id = static_cast< float >( get_value_unscaled( 0x0d , 0x51 , &in_rawinput_array[ index ]->data.hid ) ); // id

            // 00
            // 01
            // 10
            // 11

            float screen_x = x * pad_to_screen_ratio.width;
            float screen_y = y * pad_to_screen_ratio.height;

            std::wstring message;// = L"\nx: " + std::to_wstring( x ) += L" y: " + std::to_wstring( y );
            
            //message += L"\nx: " + std::to_wstring( x ) += L" y: " + std::to_wstring( y );
            //OutputDebugStringW( message.data() );

            update_contact( id , screen_x , screen_y );

            message += L" id: " + std::to_wstring( static_cast<uint>(id) );

            debug_text.set_content( message );
        }
        //OutputDebugStringW( message.data() );
    }

    ulong hid_device::get_value_unscaled( ushort in_page , ushort in_usage , RAWHID * in_input )
    {
        ulong value{ 0ul };

        HidP_GetUsageValue( HidP_Input , // unsigned output
                            in_page ,
                            0 ,
                            in_usage ,
                            &value ,
                            reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) ,
                            reinterpret_cast< char * >( in_input->bRawData ) , //BYTE uchar to char
                            in_input->dwSizeHid * in_input->dwCount );
        return value;
    }

    long hid_device::get_value_scaled( ushort in_page , ushort in_usage , RAWINPUT in_input )
    {
        long value{ 0 };

        HidP_GetScaledUsageValue( HidP_Input , // signed output
                                  in_page ,
                                  0 ,
                                  in_usage ,
                                  &value ,
                                  reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) ,
                                  reinterpret_cast< char * >( in_input.data.hid.bRawData ) , //BYTE uchar to char
                                  in_input.data.hid.dwSizeHid * in_input.data.hid.dwCount );
        return value;
    }

    void hid_device::draw()
    {
        // 1. transparent full screen, draw contacts

        if( draw_information )
        {
            information.draw();
            collections.draw();
        }

        for( auto & contact : contacts ) contact.draw();

        debug_text.draw();
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

//collection.push_back( move( new_collection ) );//at( index ) = move( new_item );
*/


// Array field : The bit field created by an Input , 
// Output , or Feature main item which is declared as an Array.
// An array field contains the index of a Usage , not the Usage value.
// bit field  :  // Usage determines the field’s purpose.

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