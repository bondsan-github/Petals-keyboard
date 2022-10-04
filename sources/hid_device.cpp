#include "..\headers\hid_device.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"

namespace hid
{
    using namespace std;
    //using namespace D2D1;

    hid_device::hid_device( HANDLE in_device ) : hid_raw_device( in_device )
    {
        if( is_multi_touch() )
        {
            gather_information();

            initialise_text_device();
            //initialise_text_collections();
            //initialise_text_input();
        }
    }

    void hid_device::initialise_text_device()
    {
        string content  {};
        vertex position { 30.0f , 30.0f };

        content =  L"manufacturer\t: ";
        content += manufacturer;
        content += L"\nproduct\t\t: ";
        content += product;
        content += L"\npage\t\t: ";
        content += locate::usages()->page( page );
        content += L"\nusage\t\t: ";
        content += locate::usages()->usage( page , usage );

        /*text device(content ,
                     position ,
                     text_size ,
                     text_boundry ,
                     rectangle_margin ,
                     text_colour );*/

        information.set_content( content );
        information.set_position( position );
        information.set_rectangle_width( rectangle_width );
        information.set_rectangle_colour( rectangle_colour );

        //item_texts.push_back( move( device ) );

        // += attributes.VendorID;
        // += attributes.ProductID;
        // += attributes.VersionNumber;
        // += physical
    }

    void hid_device::initialise_text_collections()
    {
        float  position_x    = 0;
        float  position_y    = 0;
        
        vertex item_position = { position_x , position_y };
         
         // sort input.buttons[1..n] by 

        for( auto & item : collection )
        {
            item.gather_information();

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

    void hid_device::initialise_text_input()
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

    void hid_device::display_information()
    {
        draw_information = ! draw_information;  // switch
    }

    void hid_device::draw()
    {
    // 1. transparent full screen draw contacts
        if( draw_information )
        {
            information.draw();
            
            for( auto & item : collection ) item.draw();
            
            //lines.draw
        }
    }
    
    void hid_device::texts_items_input()
    {
        //for( auto & input : input.buttons )
           // write_ptr->add( input.text() );
    }

    void hid_device::gather_information()
    {
        NTSTATUS result { HIDP_STATUS_INVALID_PREPARSED_DATA };

        HidD_GetAttributes         ( file_pointer , & attributes );
        HidD_GetManufacturerString ( file_pointer , manufacturer , string_size );//manufacturer.data() , string_size );
        HidD_GetProductString      ( file_pointer , product      , string_size );
        HidD_GetPhysicalDescriptor ( file_pointer , physical     , string_size );

        //vector< node > nodes {};

        collection.resize( collection_amount );

        // memcpy to vector data pointer = copy constructor
        HidP_GetLinkCollectionNodes( collection.data() , & collection_amount , data );

        ushort index { 0 };

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

        using button_item = HIDP_BUTTON_CAPS;
        using value_item  = HIDP_VALUE_CAPS;

        vector< button_item > input_buttons   {};
        vector< value_item >  input_values    {};

        vector< button_item > output_buttons  {};
        vector< value_item >  output_values   {};

        vector< button_item > button_features {};
        vector< value_item >  value_features  {};
        
        input_buttons.resize   ( input.button_amount );
        HidP_GetButtonCaps     ( HidP_Input   , input_buttons.data()   , & input.button_amount   , data );

        input_values.resize    ( input.value_amount );
        HidP_GetValueCaps      ( HidP_Input   , input_values.data()    , & input.value_amount    , data );

        output_buttons.resize  ( output.button_amount );
        HidP_GetButtonCaps     ( HidP_Output  , output_buttons.data()  , & output.button_amount  , data);

        output_values.resize   ( output.value_amount );
        HidP_GetValueCaps      ( HidP_Output  , output_values.data()   , & output.value_amount   , data );

        button_features.resize ( feature.button_amount );
        HidP_GetButtonCaps     ( HidP_Feature , button_features.data() , & feature.button_amount , data );

        value_features.resize  ( feature.value_amount );
        HidP_GetValueCaps      ( HidP_Feature , value_features.data()  , & feature.value_amount  , data );

        for( auto & button : input_buttons )
        {
            hid_local_item new_button;

            // type = input
            new_button.page            = button.UsagePage;

            new_button.report_index    = button.ReportID;
            new_button.report_amount   = button.ReportCount; // Available in API version >= 2 only.

            new_button.bit_field       = button.BitField;

            new_button.origin          = button.LinkCollection;
            new_button.origin_page     = button.LinkUsagePage;
            new_button.origin_usage    = button.LinkUsage;

            new_button.is_range        = button.IsRange;
            new_button.is_absolute     = button.IsAbsolute;
            new_button.is_alias        = button.IsAlias;

            new_button.has_designators = button.IsDesignatorRange;
            new_button.has_strings     = button.IsStringRange;

            if( new_button.is_range )
            {
                new_button.usages.begin = button.Range.UsageMin;
                new_button.usages.end   = button.Range.UsageMax;

                new_button.datum_index.begin  = button.Range.DataIndexMin;
                new_button.datum_index.end    = button.Range.DataIndexMax;
            }
            else
            {
                new_button.usage        = button.NotRange.Usage;
                new_button.data_index   = button.NotRange.DataIndex;
            }
            
            if( new_button.has_strings )
            {
                new_button.strings.begin = button.Range.StringMin;
                new_button.strings.end   = button.Range.StringMax;
                  //HidD_GetIndexedString
            }
            else
            {
                new_button.string = button.NotRange.StringIndex;
            }

            if( new_button.has_designators )
            {
                new_button.designators.begin = button.Range.DesignatorMin;
                new_button.designators.end   = button.Range.DesignatorMax;
                // physical descriptor
            }
            else
            {
                new_button.designator = button.NotRange.DesignatorIndex;
            }

            new_button.gather_information();

            input.buttons.emplace_back( move( new_button ) );
        }

        for( auto & value : input_values )
        {
            //value new_value {};
            //input_value.BitField;
        }

        //new_item.origin = input.LinkCollection; vector<main_item>::reference
    }
}
/*
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