#include "Input\HID\Device.h"

//#include <hidpi.h>
//#include <hidsdi.h>

#include <fstream>
#include <iostream>

namespace HID
{
    Device::Device( HANDLE device )
    {
        //OutputDebugString( L"Device::parametertised constructor\n" );
        //https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/

        raw_handle = device;

        NTSTATUS result    { HIDP_STATUS_INVALID_PREPARSED_DATA };
        uint     data_size {};

        // Retrieve size of preparsed data.
        GetRawInputDeviceInfo( raw_handle, request.data, nullptr, & data_size );

        data_preparsed.resize( data_size );

        // Retrieve preparsed data.
        GetRawInputDeviceInfo( raw_handle, request.data, data_preparsed.data(), & data_size );

        result = HidP_GetCaps( reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) 
                               , & capabilities );

        page_  = capabilities.UsagePage;
        usage_ = capabilities.Usage;

        unsigned int structure_size = sizeof( RID_DEVICE_INFO );

        GetRawInputDeviceInfo( raw_handle , 
                               request.info ,
                               & rid_information , 
                               & structure_size );

        identity_.vendor  = rid_information.hid.dwVendorId;
        identity_.product = rid_information.hid.dwProductId;

        //std::wstring message;
        //message = L" vendor: " + std::to_wstring( identity.vendor );
        //message += L"  product: " + std::to_wstring( identity.product );
        //OutputDebugStringW( message.c_str() );

        // find in collections 0x0d , 0x55 Contact Count Maximum
        // contacts.resize( contacts_maximum );
    }

    bool Device::is_multi_touch()
    {
        return ( page_ == HID_USAGE_PAGE_DIGITIZER && usage_ == HID_USAGE_DIGITIZER_TOUCH_PAD );
        // and > 1 touch input
    }

    Device::~Device()
    {
        OutputDebugString( L"\n Device::~Device()" );
        //if( device_pointer ) CloseHandle( device_pointer );
    }

    std::wstring Device::path()
    {
        // get device path character amount
        uint return_value = GetRawInputDeviceInfo( raw_handle, request.path, 0, & path_char_amount );

        path_.resize( path_char_amount );

        return_value = 0;
        // get device path // use wchar_t[] buffer instead of string if driver issue
        return_value = GetRawInputDeviceInfo( raw_handle, request.path, path_.data() , & path_char_amount );

        /*
        std::wstring debug_string = L"\n";
        debug_string += path.data();
        debug_string += L"\n";
        OutputDebugStringW( debug_string.data() ); */

        return path_;
    }

    void Device::update()
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

    void Device::update/*_unbufferd*/( RAWINPUT * input_report )
    {
        //contact_identifier = value_contact_identifier->get_value();
        //collections.update_input( input_report );

        float x  = static_cast< float >( value_unscaled( 0x01 , 0x30 , &input_report->data.hid ) ); // x
        float y  = static_cast< float >( value_unscaled( 0x01 , 0x31 , &input_report->data.hid ) ); // y
        float id = static_cast< float >( value_unscaled( 0x0d , 0x51 , &input_report->data.hid ) ); // id

        //update_contact( id , x , y );

        std::wstring message = L"\nx: " + std::to_wstring( x ) += L" y: " + std::to_wstring( y );
        OutputDebugString( message.data() );
    }

    /*void Device::update_contact( ulong in_identifier , float in_x , float in_y )
    {
        if( in_identifier >= 0 and in_identifier < contacts.size() )
            contacts.at( in_identifier ).update( static_cast< float >( in_x ) ,
                                                 static_cast< float >( in_y ) );
    }*/

    void Device::update_buffered( RAWINPUT ** rawinput_array, uint report_amount )
    {
        float x  { 0 };
        float y  { 0 };
        float id { 0 };

        //std::wstring message = L"\n";

        for( uint index{ 0 }; index < report_amount; index++ )
        {
            Collections::update( rawinput_array[ index ] );

            x  = static_cast< float >( value_unscaled( 0x01 , 0x30 , & rawinput_array[ index ]->data.hid ) ); // x
            y  = static_cast< float >( value_unscaled( 0x01 , 0x31 , & rawinput_array[ index ]->data.hid ) ); // y
            id = static_cast< float >( value_unscaled( 0x0d , 0x51 , & rawinput_array[ index ]->data.hid ) ); // id

            // 00
            // 01
            // 10
            // 11

            //float screen_x = x * pad_to_screen_ratio.width;
            //float screen_y = y * pad_to_screen_ratio.height;

            //std::wstring message;// = L"\nx: " + std::to_wstring( x ) += L" y: " + std::to_wstring( y );
            
            //message += L"\nx: " + std::to_wstring( x ) += L" y: " + std::to_wstring( y );
            //OutputDebugStringW( message.data() );

            //update_contact( id , screen_x , screen_y );

            //message += L" id: " + std::to_wstring( static_cast< uint >( id ) );
            //debug_text.set( message );
        }
        //OutputDebugStringW( message.data() );
    }

    ulong Device::value_unscaled( ushort page, ushort usage, RAWHID * input )
    {
        ulong value {};

        HidP_GetUsageValue( HidP_Input , // unsigned output
                            page ,
                            0 ,
                            usage ,
                            & value ,
                            reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) ,
                            reinterpret_cast< char * >( input->bRawData ) , //BYTE uchar to char
                            input->dwSizeHid * input->dwCount );
        return value;
    }

    long Device::value_scaled( ushort page, ushort usage, RAWINPUT input )
    {
        long value {};

        HidP_GetScaledUsageValue( HidP_Input , // signed output
                                  page ,
                                  0 ,
                                  usage ,
                                  & value ,
                                  reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) ,
                                  reinterpret_cast< char * >( input.data.hid.bRawData ) , //BYTE uchar to char
                                  input.data.hid.dwSizeHid * input.data.hid.dwCount );
        return value;
    }

    void Device::collect_information()
    {
        NTSTATUS result{ HIDP_STATUS_INVALID_PREPARSED_DATA };

        path();

        // cannot have exclusive file access
        //https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections-opened-by-windows-for-system-use

        // open i_o device for query 
        std::wstring        filename             = path_.c_str();
        ulong               desired_access       = 0; //GENERIC_READ ,//| GENERIC_WRITE
        ulong               share_mode           = FILE_SHARE_READ | FILE_SHARE_WRITE;
        SECURITY_ATTRIBUTES security_attributes{};
        ulong               creation_disposition = OPEN_EXISTING;
        ulong               flags_and_attributes = FILE_FLAG_OVERLAPPED; //FILE_ATTRIBUTE_NORMAL;
        HANDLE              template_file{};

        file_handle = CreateFileW( filename.c_str() ,
                                   desired_access ,
                                   share_mode ,
                                   &security_attributes ,
                                   creation_disposition ,
                                   flags_and_attributes ,
                                   template_file );

        if( file_handle == INVALID_HANDLE_VALUE ) error_exit( L"\n Unable to open device." );

        HidD_GetAttributes( file_handle, & attributes );
        HidD_GetManufacturerString( file_handle, manufacturer_buffer, string_size );
        HidD_GetProductString( file_handle, product_buffer, string_size );
        HidD_GetPhysicalDescriptor( file_handle, physical_buffer, string_size );

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

        //set_text_device();

        // -- collections -------------------------------------------
        ulong collection_amount = capabilities.NumberLinkCollectionNodes;

        PHIDP_PREPARSED_DATA data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() );

        HIDP_LINK_COLLECTION_NODE * nodes = new HIDP_LINK_COLLECTION_NODE[ collection_amount ];

        result = HidP_GetLinkCollectionNodes( nodes ,
                                              & collection_amount ,
                                              data );

        if( result == HIDP_STATUS_BUFFER_TOO_SMALL ) error_exit( L"Collection buffer size error." );

        add_collection( nodes, capabilities.NumberLinkCollectionNodes );

        delete[] nodes;
        // ---------------------------------------------

        _HIDP_BUTTON_CAPS * button_array{};
        _HIDP_VALUE_CAPS * value_array{};

        // Retrieve array of input buttons capabilities.
        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberInputButtonCaps ];

        result = HidP_GetButtonCaps( HidP_Input ,
                                     button_array ,
                                     &capabilities.NumberInputButtonCaps ,
                                     data );

        // Store buttons in a input collection.
        add_buttons( * this,
                     report_type::input,
                     button_array,
                     capabilities.NumberInputButtonCaps );

        delete[] button_array;

        // Retrieve array of input values capabilities.
        value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberInputValueCaps ];

        result = HidP_GetValueCaps( HidP_Input ,
                                    value_array ,
                                    & capabilities.NumberInputValueCaps ,
                                    data );

        // Store values in a input collection.
        add_values( * this,
                    report_type::input,
                    value_array,
                    capabilities.NumberInputValueCaps );

        delete[] value_array;

        // Retrieve array of output buttons capabilities.
        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberOutputButtonCaps ];

        result = HidP_GetButtonCaps( HidP_Output,
                                     button_array,
                                     & capabilities.NumberOutputButtonCaps,
                                     data );

        // Store buttons in a output collection.
        add_buttons( * this,
                     report_type::output,
                     button_array,
                     capabilities.NumberOutputButtonCaps );

        delete[] button_array;

        // Retrieve array of output values capabilities.
        value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberOutputValueCaps ];

        result = HidP_GetValueCaps( HidP_Output ,
                                    value_array ,
                                    &capabilities.NumberOutputValueCaps ,
                                    data );

        // Store values in a output collection.
        add_values( * this,
                    report_type::output,
                    value_array,
                    capabilities.NumberOutputValueCaps );

        delete[] value_array;

        // Retrieve array of feature buttons capabilities.
        button_array = new _HIDP_BUTTON_CAPS[ capabilities.NumberFeatureButtonCaps ];

        result = HidP_GetButtonCaps( HidP_Feature ,
                                     button_array ,
                                     &capabilities.NumberFeatureButtonCaps ,
                                     data );

        // Store buttons in a feature collection.
        add_buttons( * this ,
                     report_type::feature ,
                     button_array ,
                     capabilities.NumberFeatureButtonCaps );

        delete[] button_array;

        // Retrieve array of feature buttons capabilities.
        value_array = new _HIDP_VALUE_CAPS[ capabilities.NumberFeatureValueCaps ];

        result = HidP_GetValueCaps( HidP_Feature ,
                                    value_array ,
                                    &capabilities.NumberFeatureValueCaps ,
                                    data );

        // Store values in a feature collection.
        add_values( * this ,
                    report_type::feature ,
                    value_array ,
                    capabilities.NumberFeatureValueCaps );

        delete[] value_array;

        //calculate_positions( *this );

        //if( HidD_GetInputReport( device_pointer , buffer , buffer_size ) ) {}
        //else print_error(L"\n unable to get input report" );

        //HidD_SetNumInputBuffers( file_handle , 256 );

        /*ulong buffer_amount{0};
        HidD_GetNumInputBuffers( file_handle, &buffer_amount);
        std::wstring message = L"\nbuffer_amount: " + std::to_wstring( buffer_amount );
        OutputDebugStringW( message.data() );*/

        //D2D1_UNIT_MODE GetUnitMode();
        //screen_dpi = application.dpi();
        //touchpad_resolution = resolution();

        //D2D_SIZE_F screen_size_dips = application.size_dips();

        // To convert a physical pixel to a DIP, use this formula:
        // dip = ( physical pixel × 96 ) / DPI

         // screen 3840 x 2160
         // pad 1496 x 968
         // 1496 * 2.57 = 3840 
         // pad_to_screen = screen_resolution / pad_resolution

        // full touchpad resolution mapped to full screen space 

        //pad_to_screen_ratio.width  = screen_size_dips.width / touchpad_resolution.maximum;
        //pad_to_screen_ratio.height = screen_size_dips.height / touchpad_resolution.maximum;

        // if( ten_finger_input )
            // else
        //contacts.resize( contact_amount );
        //contacts.resize( 1 );

        uint input_index_begin = 0;
        uint input_index_end = 0;
        // 10 / 4 = 2.5
        // 10 / 5 = 2

        /*contacts[0].inputs({L"q" , L"w" , L"a" , L"s"});
        contacts[ 1 ].inputs( { L"e" , L"r" , L"d" , L"f" } );
        contacts[ 2 ].inputs( { L"t" , L"y" , L"g" , L"h" } );
        contacts[ 3 ].inputs( { L"u" , L"i" , L"j" , L"k" } );
        contacts[ 4 ].inputs( { L"o" , L"p" , L"l" , L"z" } );
        */
        /*
        for( auto & contact : contacts )
        {
            // contact
            //split custom_types::input_types between contacts
        }*/
    }
    
    void Device::draw()
    {
        // 1. transparent full screen, draw contacts

        //for( auto & contact : contacts ) contact.draw();
    }
} // namespace HID

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



   //void Device::set_text_device()
   //{
   //    std::wstring content;

   //    content =  L"manufacturer\t: ";
   //    content += manufacturer;
   //    content += L"\nproduct\t\t: ";
   //    content += product;
   //    content += L"\npage\t\t: ";
   //    content += Usages::get_page( page );
   //    content += L"\nusage\t\t: ";
   //    content += Usages::get_usage( page , usage );

   //    ulong input_amount = HidP_MaxDataListLength( HidP_Input ,
   //                                                 reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() ) );

   //    content += L"\ninput amount\t: " + std::to_wstring( input_amount );

   //    information.set( content );
   //    information.set_position( text_position );
   //    information.set_layout_size( text_layout_size );
   //    information.set_size( text_font_size );
   //    information.set_colour( text_font_colour );
   //    //information.set_rectangle_line_colour( rectangle_line_colour );

   //    // += attributes.VendorID;
   //    // += attributes.ProductID;
   //    // += attributes.VersionNumber;
   //    // += physical
   //}
