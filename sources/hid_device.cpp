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
            initialise_text_collections();
            initialise_text_input();
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
        information.set_position( position );
        information.set_content( content );
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
        /*
        vector< hid_collection >::reference item         = collection.front();
        string                             item_content  = item.text();

        float  position_x    = item_texts.at( index ).formated_rectangle().left;
        float  position_y    = item_texts.at( index ).middle_vertices().bottom.y + spacer.y;
        vertex item_position = { position_x , position_y };

        text head_item( item_content , item_position , text_size , text_boundry , rectangle_margin );
             head_item.set_rectangle_colour( rectangle_colour );
             head_item.set_rectangle_width( rectangle_width );

        item_texts.push_back( head_item );
         
        item = collection.at( item.first );
        

        for( int index { 1 } ; index < collection.size() ; index++ )
        {
            item_content     = item.text();

            float position_x = item_texts.at( index ).formated_rectangle().left;
            float position_y = item_texts.at( index ).middle_vertices().bottom.y + spacer.y;
            
            item_position    = { position_x , position_y };

            text new_item( item_content , item_position , text_size , text_boundry , rectangle_margin );

            new_item.set_rectangle_colour( rectangle_colour );
            new_item.set_rectangle_width( rectangle_width );

            item_texts.push_back( new_item );

            item = collection.at( item.next );
        }*/

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
        
        index = 0;
        
        for( auto & button : input.buttons )
        {
            button.index = index; index++;

            string content  = button.text();
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
            //for( auto & item : item_texts ) item.draw();            
            //       lines.draw
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

        vector< node > nodes {};

        nodes.resize( collection_amount );

        HidP_GetLinkCollectionNodes( nodes.data() , &collection_amount , data );

        //items.resize( item_amount );
        ushort index {};

        for( const auto & node : nodes )
        {
            hid_collection new_item;

            new_item.index    = index;
            new_item.type     = hid_item_type { node.CollectionType };
            new_item.page     = node.LinkUsagePage;
            new_item.usage    = node.LinkUsage;
            new_item.is_alias = node.IsAlias;
            new_item.siblings = node.NumberOfChildren;

            new_item.origin   = node.Parent;
            new_item.next     = node.NextSibling;
            new_item.first    = node.FirstChild;

            index++;
            //using link = vector< item >::reference;
            /*
            if( node.Parent ) // one parent , above
               new_item.origin = & items.at( node.Parent - 1 );

            if( node.NextSibling ) // to right
               new_item.next   = & items.at( node.NextSibling - 1 );

            if( node.FirstChild ) // left-most
               new_item.first  = & items.at( node.FirstChild - 1 );
            */
            collection.push_back( new_item );//at( index ) = move( new_item );

        }

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
        HidP_GetValueCaps      ( HidP_Feature , value_features.data()  , & feature.value_amount   , data );

        for( auto & input : input_buttons )
        {
            hid_local_item new_item {};

            // type = input
            new_item.page            = input.UsagePage;

            new_item.report_index    = input.ReportID;
            new_item.report_amount   = input.ReportCount; // Available in API version >= 2 only.

            new_item.bit_field       = input.BitField;

            new_item.origin          = input.LinkCollection;
            new_item.origin_page     = input.LinkUsagePage;
            new_item.origin_usage    = input.LinkUsage;

            new_item.is_range        = input.IsRange;
            new_item.is_absolute     = input.IsAbsolute;
            new_item.is_alias        = input.IsAlias;

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
                new_item.usage        = input.NotRange.Usage;
                new_item.data         = input.NotRange.DataIndex;
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
                // physical descriptor
            }
            else
            {
                new_item.designator = input.NotRange.DesignatorIndex;
            }

            this->input.buttons.emplace_back( move( new_item ) );
        }

        for( auto & input_value : input_values )
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