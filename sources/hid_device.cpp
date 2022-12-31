#include "..\headers\hid_device.h"

#include "..\headers\utility.h"
#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

namespace hid
{
    using namespace std;

    hid_device::hid_device() 
    {
        OutputDebugString( L"\n hid_device::default constructor" );
    }

    hid_device::hid_device( hid_raw_device & raw_device )
    {
        OutputDebugString( L"\n hid_device::hid_raw_device constructor" );

        device_pointer   = raw_device.get_device_pointer();
        data_preparsed   = std::move( raw_device.get_preparsed_data() );
        capabilities     = raw_device.get_capabilities();
        page             = raw_device.get_page();
        usage            = raw_device.get_usage();
    }

    hid_device::hid_device( const hid_device & in_copy )
    {
        OutputDebugString( L"\n hid_device::copy constructor" );

        if( this != &in_copy ) *this = in_copy;
    }

    hid_device::hid_device( hid_device && in_move ) noexcept
    {
        OutputDebugString( L"\n hid_device::move constructor" );

        if( this != &in_move ) *this = std::move( in_move );
    }

    hid_device & hid_device::operator = ( const hid_device & assign_copy )
    {
        OutputDebugString( L"\n hid_device::assignment copy" );

        if( this != &assign_copy )
        {
            data_preparsed        = assign_copy.data_preparsed;
            device_pointer        = assign_copy.device_pointer;
            device_path           = assign_copy.device_path;
            path_char_amount      = assign_copy.path_char_amount;
            page                  = assign_copy.page;
            usage                 = assign_copy.usage;
            input_report          = assign_copy.input_report;
            output_report         = assign_copy.output_report;
            feature_report        = assign_copy.feature_report;
            capabilities          = assign_copy.capabilities;
            collection_amount     = assign_copy.collection_amount;
            attributes            = assign_copy.attributes;
            attributes_extra      = assign_copy.attributes_extra;
            manufacturer          = assign_copy.manufacturer;
            product               = assign_copy.product;
            physical              = assign_copy.physical;
            collection            = assign_copy.collection;
            information           = assign_copy.information;
            //lines                 = assign_copy.lines;
            input_buttons         = assign_copy.input_buttons;
            input_values          = assign_copy.input_values;
            output_buttons        = assign_copy.output_buttons;
            output_values         = assign_copy.output_values;
            button_features       = assign_copy.button_features;
            value_features        = assign_copy.value_features;
            draw_information      = assign_copy.draw_information;
            font_face             = assign_copy.font_face;
            font_size             = assign_copy.font_size;
            font_colour           = assign_copy.font_colour;
            layout_size     = assign_copy.layout_size;
            //rectangle_margin      = assign_copy.rectangle_margin;
            //rectangle_line_width  = assign_copy.rectangle_line_width;
            //rectangle_line_colour = assign_copy.rectangle_line_colour;
            information_spacing     = assign_copy.information_spacing;
        }

        return *this;
    }

    hid_device & hid_device::operator = ( hid_device && assign_move ) noexcept
    {
        OutputDebugString( L"\n hid_device::assignment move" );

        if( this != &assign_move )
        {
            data_preparsed        = std::move( assign_move.data_preparsed );
            device_pointer        = std::move( assign_move.device_pointer );
            device_path           = std::move( assign_move.device_path );
            path_char_amount      = std::move( assign_move.path_char_amount );
            page                  = std::move( assign_move.page );
            usage                 = std::move( assign_move.usage );
            input_report          = std::move( assign_move.input_report );
            output_report         = std::move( assign_move.output_report );
            feature_report        = std::move( assign_move.feature_report );
            capabilities          = std::move( assign_move.capabilities );
            collection_amount     = std::move( assign_move.collection_amount );
            attributes            = std::move( assign_move.attributes );
            attributes_extra      = std::move( assign_move.attributes_extra );
            manufacturer          = std::move( assign_move.manufacturer );
            product               = std::move( assign_move.product );
            physical              = std::move( assign_move.physical );
            collection            = std::move( assign_move.collection );
            information           = std::move( assign_move.information );
            //lines                 = std::move( assign_move.lines );
            input_buttons         = std::move( assign_move.input_buttons );
            input_values          = std::move( assign_move.input_values );
            output_buttons        = std::move( assign_move.output_buttons );
            output_values         = std::move( assign_move.output_values );
            button_features       = std::move( assign_move.button_features );
            value_features        = std::move( assign_move.value_features );
            draw_information      = std::move( assign_move.draw_information );
            font_face             = std::move( assign_move.font_face );
            font_size             = std::move( assign_move.font_size );
            font_colour           = std::move( assign_move.font_colour );
            layout_size     = std::move( assign_move.layout_size );
            //rectangle_margin      = std::move( assign_move.rectangle_margin );
            //rectangle_line_width  = std::move( assign_move.rectangle_line_width );
            //rectangle_line_colour = std::move( assign_move.rectangle_line_colour );
            information_spacing     = std::move( assign_move.information_spacing );

            assign_move.reset();
        }

        return *this;
    }

    void hid_device::reset()
    {
        data_preparsed.clear();
        device_pointer    = nullptr;
        device_path       = L"no device path";
        path_char_amount  = 0;
        page              = 0;
        usage             = 0;
        collection_amount = 0;
        draw_information  = false;

        font_face   = L"Cascasia code";
        font_size   = 15.0f;
        font_colour = D2D1::ColorF::White;

        //rectangle_margin      = 0.0f;
        //rectangle_line_width  = 1.0f;
        //rectangle_line_colour = D2D1::ColorF::DarkCyan;
        layout_size     = D2D1_SIZE_F{ 200.0f, 200.0f };

        manufacturer.clear();
        product.clear();
        physical.clear();
        collection.clear();
        //lines.clear();

        input_buttons.clear();
        input_values.clear();
        output_buttons.clear();
        output_values.clear();
        button_features.clear();
        value_features.clear();

        input_report.reset();
        output_report.reset();
        feature_report.reset();
        capabilities.reset();
        attributes.reset();
        attributes_extra.reset();
        information.reset();
    }

    hid_device::~hid_device( void )
    {
        OutputDebugString( L"\n hid_device::de-constructor" );

        CloseHandle( device_pointer );
        data_preparsed.clear();
        device_pointer    = nullptr;
    }

    void hid_device::collect_information()
    {
        NTSTATUS result { HIDP_STATUS_INVALID_PREPARSED_DATA };

        /*
        page              = capabilities.UsagePage;
        usage             = capabilities.Usage;
        collection_amount = capabilities.NumberLinkCollectionNodes;

        input_report.byte_amount              = capabilities.InputReportByteLength;
        input_report.button_amount            = capabilities.NumberInputButtonCaps;
        input_report.value_amount             = capabilities.NumberInputValueCaps;
        input_report.data_identifier_amount   = capabilities.NumberInputDataIndices;

        output_report.byte_amount             = capabilities.OutputReportByteLength;
        output_report.button_amount           = capabilities.NumberOutputButtonCaps;
        output_report.value_amount            = capabilities.NumberOutputValueCaps;
        output_report.data_identifier_amount  = capabilities.NumberOutputDataIndices;

        feature_report.byte_amount            = capabilities.FeatureReportByteLength;
        feature_report.button_amount          = capabilities.NumberFeatureButtonCaps;
        feature_report.value_amount           = capabilities.NumberFeatureValueCaps;
        feature_report.data_identifier_amount = capabilities.NumberFeatureDataIndices;
        */

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

        //vector< node > nodes {};

        collection_amount = capabilities.NumberLinkCollectionNodes;
        collection.resize( collection_amount );

        PHIDP_PREPARSED_DATA data = reinterpret_cast< PHIDP_PREPARSED_DATA >( data_preparsed.data() );

        result = HidP_GetLinkCollectionNodes( collection.data() , &collection_amount , data );
        if( result == HIDP_STATUS_BUFFER_TOO_SMALL ) error_exit( L"collection buffer size error" );

        //ushort index{ 0 };

        //collection.front().information.set_position();

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

        
        //                       report type  , data destination       , data size               , source data
        input_buttons.resize( capabilities.NumberInputButtonCaps );
        result = HidP_GetButtonCaps( HidP_Input , input_buttons.data() , & capabilities.NumberInputButtonCaps , data );

        input_values.resize( input_report.value_amount );
        result = HidP_GetValueCaps( HidP_Input , input_values.data() , & input_report.value_amount , data );

        output_buttons.resize( output_report.button_amount );
        result = HidP_GetButtonCaps( HidP_Output , output_buttons.data() , & output_report.button_amount , data );

        output_values.resize( output_report.value_amount );
        result = HidP_GetValueCaps( HidP_Output , output_values.data() , & output_report.value_amount , data );

        button_features.resize( feature_report.button_amount );
        result = HidP_GetButtonCaps( HidP_Feature , button_features.data() , & feature_report.button_amount , data );

        value_features.resize( feature_report.value_amount );
        result = HidP_GetValueCaps( HidP_Feature , value_features.data() , & feature_report.value_amount , data );

        /*
        for( auto & button : input_buttons ) //input_buttons.release
        {
            hid_local_item new_button;

            // type = input
            new_button.set_page( button.UsagePage );

            new_button.set_report_index( button.ReportID ); // report identifier
            new_button.set_report_amount( button.ReportCount );

            new_button.set_bit_field( button.BitField );

            new_button.set_origin( button.LinkCollection );
            new_button.set_origin_page( button.LinkUsagePage );
            new_button.set_origin_usage( button.LinkUsage );

            new_button.set_is_range( button.IsRange );
            new_button.set_is_absolute( button.IsAbsolute );
            new_button.set_is_alias( button.IsAlias ); // does button have multiple usages

            new_button.set_has_designators( button.IsDesignatorRange );
            new_button.set_has_strings( button.IsStringRange );

            if( new_button.get_is_range() )
            {
                new_button.set_usages_begin( button.Range.UsageMin );
                new_button.set_usages_end( button.Range.UsageMax );
                
                new_button.set_data_identifiers_begin( button.Range.DataIndexMin );
                new_button.set_data_identifiers_end( button.Range.DataIndexMax );

                new_button.set_strings_range_begin( button.Range.StringMin ); //HidD_GetIndexedString
                new_button.set_strings_range_end( button.Range.StringMax );

                new_button.set_designators_range_begin( button.Range.DesignatorMin ); // physical descriptor
                new_button.set_designators_range_end( button.Range.DesignatorMax );
            }
            else
            {
                new_button.set_usage( button.NotRange.Usage );
                new_button.set_data_identifier( button.NotRange.DataIndex );
                new_button.set_string_index( button.NotRange.StringIndex );
                new_button.set_designator( button.NotRange.DesignatorIndex );
            }

            //if( new_button.get_has_strings() )
            //{} else {}
            //if( new_button.get_has_designators() )
            //{} else {}

            //new_button.gather_information(); get_information_string()

            input_report.buttons.push_back( move( new_button ) );
            //input_report.buttons.push_back( new_button );
        }
        */
        /*
        for( auto & value : input_values )
        {
            hid_global_item new_value;

            new_value.set_page( value.UsagePage );

            new_value.set_origin( value.LinkCollection );   // A unique internal index pointer
            new_value.set_origin_usage( value.LinkUsage );
            new_value.set_origin_page( value.LinkUsagePage );

            new_value.set_is_alias( value.IsAlias );
            new_value.set_is_range( value.IsRange );

            new_value.set_is_range( value.IsDesignatorRange );
            new_value.set_is_absolute( value.IsAbsolute );

            new_value.set_has_strings( value.IsStringRange );
            new_value.set_has_null( value.HasNull );

            new_value.set_bit_amount( value.BitSize );
            new_value.set_bit_field( value.BitField );

            new_value.set_report_index( value.ReportID );
            new_value.set_report_amount( value.ReportCount );

            new_value.set_unit_exponent( value.UnitsExp );
            new_value.set_unit( value.Units );

            new_value.set_logical_limit_minimum( value.LogicalMin );
            new_value.set_logical_limit_maximum( value.LogicalMax );
            new_value.set_physical_limit_minimum( value.PhysicalMin );
            new_value.set_physical_limit_maximum( value.PhysicalMax );

            if( new_value.get_is_range() )
            {
                new_value.set_usages_begin( value.Range.UsageMin );
                new_value.set_usages_end( value.Range.UsageMax );

                new_value.set_data_identifiers_begin( value.Range.DataIndexMin );
                new_value.set_data_identifiers_end( value.Range.DataIndexMax );

                new_value.set_strings_range_begin( value.Range.StringMin ); //HidD_GetIndexedString
                new_value.set_strings_range_end( value.Range.StringMax );

                new_value.set_designators_range_begin( value.Range.DesignatorMin ); // physical descriptor
                new_value.set_designators_range_end( value.Range.DesignatorMax );
            }
            else
            {
                new_value.set_usage( value.NotRange.Usage );
                new_value.set_data_identifier( value.NotRange.DataIndex );
                new_value.set_string_index( value.NotRange.StringIndex );
                new_value.set_designator( value.NotRange.DesignatorIndex );
            }

            input_report.values.push_back( move( new_value ) );
            //input_report.values.push_back( new_value );
            //new_item.origin = input.LinkCollection; vector<main_item>::reference
        }
        */

        set_text_device();
    }

    void hid_device::set_text_device()
    {
        std::wstring content  {};
        vertex position { 30.0f , 30.0f };

        content =  L"manufacturer\t: ";
        content += manufacturer;
        content += L"\nproduct\t\t: ";
        content += product;
        content += L"\npage\t\t: ";
        content += locate::get_usages().page( page );
        content += L"\nusage\t\t: ";
        content += locate::get_usages().usage( page , usage );

        /*text device(content ,
                     position ,
                     text_size ,
                     text_boundry ,
                     rectangle_margin ,
                     text_colour );*/

        information.set_content( content );
        information.set_position_top_left( position );
        information.set_layout_size( D2D1_SIZE_F{ 200.0f , 200.0f } );
        //information.set_rectangle_line_colour( rectangle_line_colour );

        // += attributes.VendorID;
        // += attributes.ProductID;
        // += attributes.VersionNumber;
        // += physical
    }

    void hid_device::set_text_collections()
    {
        float  position_x    = 0.0f;
        float  position_y    = 0.0f;
        
        vertex item_position { position_x , position_y };
         
         // sort input.buttons[1..n] by 

        for( auto & item : collection )
        {
            //item.set_information();

            //position_x = information.formated_rectangle().left;
            //position_y = information.formated_rectangle().bottom + spacer.y;
            
            //item.information.set_position( { position_x , position_y } );

            //new_item.set_rectangle_colour( rectangle_colour );
            //new_item.set_rectangle_width( rectangle_width );

            //item_texts.push_back( new_item );

            //item = collection.at( item.next );
        } 

        // line from device to first main item
        //vertex a = item.mid_points( 0 ).bottom;
        //vertex b = item.mid_points( 1 ).top;
        //main_window.paint.add_line( a , b , 0.5 , colours::White );
        // items main
        
        // second item
        // column += 2;
        //item++;
        // for all other items
          //      a = text.mid_points
          //      b = write.mid_points( item->next ).top;
        //point a = *text;//&text.mid_points( text ).bottom;
        //point b = write.mid_points( 1 ).top;
        //main_window.paint.add_line( a , b , 0.5 , colours::White );
    }

    void hid_device::set_text_input()
    {
        //find( begin( items ) , end( items ) ,  )
        /*
        index = 0;
        
        for( auto & button : input.buttons )
        {
            button.index = index; index++;

            //string content  = button.text();
            vertex position {};

           // find if matching collection (page && usage)  , 
               //  align position.top with collection
               
            vector< hid_collection >::iterator item { collection.begin() };
            
            item = find_if( collection.begin() ,
                            collection.end()   ,
                            [ & button ] ( hid_collection const & collection ) 
                            { 
                                return collection.page == button.page; 
                            } );

            if( item != collection.end() )
            {
               // position = item_texts.at( item->index ).position().y
                //position.y = 
                // 
            //item_position.y = ;
            //item_position.x += 100; // main_item//item_texts.back().formated_rectangle(). + spacer;   
            }

            text button_text( content , position , text_size , text_boundry , rectangle_margin );
            //item_texts.push_back( move( button_text ) );
        }

        */
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
            information.draw();
            
            //for( auto & item : collection ) item.draw();
            
            //lines.draw
        }
    }
    
    void hid_device::texts_items_input()
    {
        //for( auto & input : input.buttons )
           // write_ptr->add( input.text() );
    }

    
}

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