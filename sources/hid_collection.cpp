#include "..\headers\hid_collection.h"

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_item.h"

namespace hid
{
    void hid_collection::operator = ( const _HIDP_LINK_COLLECTION_NODE & in_node )
    {
        LinkUsage        = in_node.LinkUsage;
        LinkUsagePage    = in_node.LinkUsagePage;
        Parent           = in_node.Parent;
        NumberOfChildren = in_node.NumberOfChildren;
        NextSibling      = in_node.NextSibling;
        FirstChild       = in_node.FirstChild;
        CollectionType   = in_node.CollectionType;  // As defined in 6.2.2.6 of HID spec
        IsAlias          = in_node.IsAlias; // This link node is an alias of the next link node.
    }

    void hid_collection::operator = ( _HIDP_LINK_COLLECTION_NODE && in_node ) noexcept
    {
        LinkUsage        = std::move( in_node.LinkUsage );
        LinkUsagePage    = std::move( in_node.LinkUsagePage );
        Parent           = std::move( in_node.Parent );
        NumberOfChildren = std::move( in_node.NumberOfChildren );
        NextSibling      = std::move( in_node.NextSibling );
        FirstChild       = std::move( in_node.FirstChild );
        CollectionType   = std::move( static_cast< ulong >( in_node.CollectionType) );  // As defined in 6.2.2.6 of HID spec
        IsAlias          = std::move( static_cast< bool >( in_node.IsAlias ) ); // This link node is an alias of the next link node.
    }

    void hid_collection::add_button( item_type in_type , hid_button & in_button )
    {
        in_button.set_information_text();

        switch( in_type )
        {
            case item_type::input:
            {
                input_buttons.push_back( in_button );
            } break;

            case item_type::output:
            {
                output_buttons.push_back( in_button );
            } break;

            case item_type::feature:
            {
                feature_buttons.push_back( in_button );
            }
        }
    }

    void hid_collection::add_value( item_type in_type , hid_value & in_value )
    {
        in_value.set_information_text();

        switch( in_type )
        {
            case item_type::input:
            {
                input_values.push_back( in_value );
            } break;

            case item_type::output:
            {
                output_values.push_back( in_value );
            } break;

            case item_type::feature:
            {
                feature_values.push_back( in_value );
            } break;
        }
    }

    void hid_collection::set_information_text()
    {
        std::wstring text;
        
        text += L"page\t: ";
        text += locate::get_usages().page( LinkUsagePage );
        text += L"\nusage\t: ";
        text += locate::get_usages().usage( LinkUsagePage , LinkUsage );
        text += L"\ncollection\t: ";
        text += locate::get_usages().collection_type( CollectionType );
        text += IsAlias ? L"\nis alias" : L"\nnot alias";

        information.set_content( text );
        information.set_layout_size( { 200.0f, 100.0f } );
        information.set_font_size( 10.0f );
        information.set_font_colour( D2D1::ColorF::Yellow );
    }

    void hid_collection::set_text_position( const vertex & in_position )
    {
        information.set_position_top_left( in_position );
    }

    void hid_collection::set_item_positions()
    {
        //RECT client_size {};
        //client_size = locate::get_windows().get_client_rectangle();
        //ulong spacer_x = ( client_size.right - client_size.left ) / ( input_buttons.size() + 1 );
        //ulong spacer_y = ( client_size.bottom - client_size.top ) / ( input_buttons.size() + 1);

        vertex position //spacer = screen_width / button_amount
        {
            information.get_right() + 20.0f, // x 
            information.get_top()    // y
        };

        // place input buttons [collection]->[in buttons]
        auto button_itr = input_buttons.begin();
        for( ; button_itr < input_buttons.end() ; button_itr++ )
        {
            button_itr->append_information_text( L"\ninput button" );

            // get previous item text right side
            if( button_itr not_eq input_buttons.begin() )
                position.x = ( button_itr - 1 )->get_text_right() + 20.0f;
            
            button_itr->set_text_position( position );
        }
        // --------------------------------------------------------------------

        // place input values [collection]->[in buttons]->[in values]
        if( input_buttons.empty() )
        {
            position = { information.get_right() + 20.0f, information.get_top() };
        }
        else
        {   // place after input buttons
            position.x = input_buttons.back().get_text_right() + 20.f;
            position.y = input_buttons.back().get_text_top();
        }

        auto value_itr = input_values.begin();
        for( ; value_itr < input_values.end() ; value_itr++ )
        {
            value_itr->append_information_text( L"\ninput value" );

             // get previous item text right side
            if( value_itr not_eq input_values.begin() )
                position.x = ( value_itr - 1 )->get_text_right() + 20.0f;

            value_itr->set_text_position( position );
        }
        // --------------------------------------------------------------------

        // place output buttons [collection]->[in buttons]->[in values]->[out buttons]
        if( input_values.empty() )
        {
            if( input_buttons.empty() )
                position = { information.get_right() + 20.0f, information.get_top() };
            else
            {   // place after input buttons
                position.x = input_buttons.back().get_text_right() + 20.f;
                position.y = input_buttons.back().get_text_top();
            }
        }
        else
        {   // place after input values
            position.x = input_values.back().get_text_right() + 20.f;
            position.y = input_values.back().get_text_top();
        }

        button_itr = output_buttons.begin();
        for( ; button_itr < output_buttons.end() ; button_itr++ )
        {
            button_itr->append_information_text( L"\noutput button" );

            if( button_itr not_eq output_buttons.begin() )
                position.x = ( button_itr - 1 )->get_text_right() + 20.0f;

            button_itr->set_text_position( position );
        }
        // --------------------------------------------------------------------

        // place output values  
        // [collection]->[in buttons]->[in values]->[out buttons]->[out values]
        if( output_buttons.empty() )
        {
            if( input_values.empty() )
            {
                if( input_buttons.empty() )
                    position = { information.get_right() + 20.0f, information.get_top() };
                else
                {
                    position.x = input_buttons.back().get_text_right() + 20.f;
                    position.y = input_buttons.back().get_text_top();
                }
            }
            else 
            {
                position.x = input_values.back().get_text_right() + 20.f;
                position.y = input_values.back().get_text_top();
            }

        }
        else
        {   // place after outputbuttons
            position.x = output_buttons.back().get_text_right() + 20.f;
            position.y = output_buttons.back().get_text_top();
        }

        value_itr = output_values.begin();
        for( ; value_itr < output_values.end() ; value_itr++ )
        {
            button_itr->append_information_text( L"\noutput value" );

            if( value_itr not_eq output_values.begin() )
                position.x = ( value_itr - 1 )->get_text_right() + 20.0f;

            value_itr->set_text_position( position );
        }
        // --------------------------------------------------------------------

        // place feature buttons
        // [collection]->[in buttons]->[in values]->[out buttons]->[out values]->[feat button]
        if( output_values.empty() )
        { 
            if( output_buttons.empty() )
            {
                if( input_values.empty() )
                {
                    if( input_buttons.empty() )
                        position ={ information.get_right() + 20.0f, information.get_top() };
                    else
                    {
                        position.x = input_buttons.back().get_text_right() + 20.f;
                        position.y = input_buttons.back().get_text_top();
                    }
                }
                else
                {
                    position.x = input_values.back().get_text_right() + 20.f;
                    position.y = input_values.back().get_text_top();
                }

            }
            else
            {
                position.x = output_buttons.back().get_text_right() + 20.f;
                position.y = output_buttons.back().get_text_top();
            }
        }
        else
        {   // place after output buttons
            position.x = output_values.back().get_text_right() + 20.f;
            position.y = output_values.back().get_text_top();
        }

        button_itr = feature_buttons.begin();
        for( ; button_itr < feature_buttons.end() ; button_itr++ )
        {
            button_itr->append_information_text( L"\nfeature button" );

            if( button_itr not_eq feature_buttons.begin() )
                position.x = ( button_itr - 1 )->get_text_right() + 20.0f;

            button_itr->set_text_position( position );
        }
        // --------------------------------------------------------------------

        // place feature values
        // [collection]->[in buttons]->[in values]->[out buttons]->[out values]->[feat buttons]->[feat values]
        if( feature_buttons.empty() )
        {
            if( output_values.empty() )
            {
                if( output_buttons.empty() )
                {
                    if( input_values.empty() )
                    {
                        if( input_buttons.empty() )
                            position ={ information.get_right() + 20.0f, information.get_top() };
                        else
                        {
                            position.x = input_buttons.back().get_text_right() + 20.f;
                            position.y = input_buttons.back().get_text_top();
                        }
                    }
                    else
                    {
                        position.x = input_values.back().get_text_right() + 20.f;
                        position.y = input_values.back().get_text_top();
                    }

                }
                else
                {
                    position.x = output_buttons.back().get_text_right() + 20.f;
                    position.y = output_buttons.back().get_text_top();
                }
            }
            else
            {   // place after outputbuttons
                position.x = output_values.back().get_text_right() + 20.f;
                position.y = output_values.back().get_text_top();
            }
        }
        else
        {   // place output buttons after output_buttons
            position.x = feature_buttons.back().get_text_right() + 20.f;
            position.y = feature_buttons.back().get_text_top();
        }

        value_itr = feature_values.begin();
        for( ; value_itr < feature_values.end() ; value_itr++ )
        {
            value_itr->append_information_text( L"\nfeature value" );

            if( value_itr not_eq feature_values.begin() )
                position.x = ( value_itr - 1 )->get_text_right() + 20.0f;

            value_itr->set_text_position( position );
        }
        // --------------------------------------------------------------------
    }

    void hid_collection::update_input( RAWINPUT * in_raw_data )
    {
        for( auto & button : input_buttons ) button.update( in_raw_data );
        for( auto & value  : input_values  ) value.update( in_raw_data );
    }

    void hid_collection::draw() const
    {
        information.draw();

        for( const auto & button : input_buttons  ) button.draw();
        for( const auto & value  : input_values   ) value.draw();
        
        for( const auto & button : output_buttons ) button.draw();
        for( const auto & value  : output_values  ) value.draw();

        for( const auto & button : feature_buttons ) button.draw();
        for( const auto & value  : feature_values  ) value.draw();
    }

    range hid_collection::get_range( const ushort & in_page ,
                                     const ushort & in_usage ,
                                     const report_type & in_report_type ,
                                     const value_type & in_value_type )
    {
        std::vector<hid_value>::const_iterator vector_iterator {};
        std::vector<hid_value>::const_iterator vector_end {};

        switch( in_report_type )
        {
            case report_type::input:
            {
                vector_iterator = input_values.cbegin();
                vector_end = input_values.cend();
            } break;

            case report_type::output:
            {
                vector_iterator = output_values.cbegin();
                vector_end = output_values.cend();
            } break;

            case report_type::feature:
            {
                vector_iterator = feature_values.cbegin();
                vector_end = feature_values.cend();
            } break;
        }

        //if( *vector_pointer->empty() ) return { 0l , 0l };

        //range values(0,0);

        for( ; vector_iterator != vector_end ; vector_iterator++ )
        {
            if( in_page == vector_iterator->UsagePage and in_usage == vector_iterator->Range.UsageMin )
            {
                switch( in_value_type )
                {
                    case value_type::logical:
                        return { vector_iterator->LogicalMin , vector_iterator->LogicalMax };
                    break;

                    case value_type::physical:
                        return { vector_iterator->PhysicalMin , vector_iterator->PhysicalMax };
                    break;

                    case value_type::usage:
                        return { vector_iterator->Range.UsageMin , vector_iterator->Range.UsageMax };
                    break;

                    case value_type::string:
                        return { vector_iterator->Range.StringMin, vector_iterator->Range.StringMax };
                    break;

                    case value_type::disignator:
                        return { vector_iterator->Range.DesignatorMin , vector_iterator->Range.DesignatorMax };
                    break;

                    case value_type::data_index:
                        return { vector_iterator->Range.DataIndexMin , vector_iterator->Range.DataIndexMax };
                    break;
                } // switch in_value_type

            } // if page and usage the same

        } // vector loop

        return { 0 , 0 }; // vector empty
    }

    /*
    uint hid_collection::get_contact_amount()
    {
        uint amount { 0 };

        for( auto & value : input_values )
        {
            if( value.UsagePage == 0x0d and value.NotRange.Usage == 0x54 )
            {
                amount = value.get_value();
                break;
            }
        }

        return amount;
    }

    uint hid_collection::get_contact_identifier()
    {
        uint identifier { 0 };

        for( auto & value : input_values )
        {
            if( value.UsagePage == 0x0d and value.NotRange.Usage == 0x51 )
            {
                identifier = value.get_value();
                break;
            }
        }

        return identifier;
    }

    uint hid_collection::get_x()
    {
        uint x { 0 };

        for( auto & value : input_values )
        {
            if( value.UsagePage == 0x01 and value.NotRange.Usage == 0x30 )
            {
                x = value.get_value();
                break;
            }
        }

        return x;
    }

    uint hid_collection::get_y()
    {
        uint y { 0 };

        for( auto & value : input_values )
        {
            if( value.UsagePage == 0x01 and value.NotRange.Usage == 0x31 )
            {
                y = value.get_value();
                break;
            }
        }

        return y;
    }
    */
}