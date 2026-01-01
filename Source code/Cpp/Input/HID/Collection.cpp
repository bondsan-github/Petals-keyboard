#include "Input\HID\Collection.h"

#include "Input\HID\Globals.h"

namespace HID
{
    void Collection::operator = ( const collection_node & node )
    {
        LinkUsage        = node.LinkUsage;
        LinkUsagePage    = node.LinkUsagePage;
        Parent           = node.Parent;
        NumberOfChildren = node.NumberOfChildren;
        NextSibling      = node.NextSibling;
        FirstChild       = node.FirstChild;
        CollectionType   = node.CollectionType;  // As defined in 6.2.2.6 of HID spec
        IsAlias          = node.IsAlias; // This link node is an alias of the next link node.
    }

    //
    void Collection::operator = ( collection_node && node ) noexcept
    {
        LinkUsage        = std::move( node.LinkUsage );
        LinkUsagePage    = std::move( node.LinkUsagePage );
        Parent           = std::move( node.Parent );
        NumberOfChildren = std::move( node.NumberOfChildren );
        NextSibling      = std::move( node.NextSibling );
        FirstChild       = std::move( node.FirstChild );
        CollectionType   = std::move( static_cast< ulong >( node.CollectionType) );  // As defined in 6.2.2.6 of HID spec
        IsAlias          = std::move( static_cast< bool >( node.IsAlias ) ); // This link node is an alias of the next link node.
    }

    void Collection::add_button( Report_type type, Button & button )
    {
        button.collect_information();

        switch( type )
        {
            case Report_type::input:
            {
                input_buttons.push_back( button );
            } break;

            case Report_type::output:
            {
                output_buttons.push_back( button );
            } break;

            case Report_type::feature:
            {
                feature_buttons.push_back( button );
            }
        }
    }

    void Collection::add_value( Report_type type, Value & value )
    {
        value.collect_information();

        switch( type )
        {
            case Report_type::input:
            {
                input_values.push_back( value );
            } break;

            case Report_type::output:
            {
                output_values.push_back( value );
            } break;

            case Report_type::feature:
            {
                feature_values.push_back( value );
            } break;
        }
    }

    void Collection::collect_information()
    {
        std::wstring text;
        
        text += L"page\t: ";
        text += page( LinkUsagePage );
        text += L"\nusage\t: ";
        text += usage( LinkUsagePage , LinkUsage );
        text += L"\ncollection\t: ";
        text += type( CollectionType );
        text += IsAlias ? L"\nis alias" : L"\nnot alias";

        information.set( text );
        information.layout_size( { 200.0f, 100.0f } );
        information.size( 10.0f );
        information.colour( D2D1::ColorF::Yellow );
    }

    void Collection::position( Point const & position )
    {
        information.position( position );
    }

    void Collection::calculate_positions()
    {
        //RECT client_size {};
        //client_size = locate::get_windows().get_client_rectangle();
        //ulong spacer_x = ( client_size.right - client_size.left ) / ( input_buttons.size() + 1 );
        //ulong spacer_y = ( client_size.bottom - client_size.top ) / ( input_buttons.size() + 1);

        Point position //spacer = screen_width / button_amount
        {
            information.right() + 20.0f, // x 
            information.top()    // y
        };

        // place input buttons [collection]->[in buttons]
        auto button_itr = input_buttons.begin();

        for( ; button_itr < input_buttons.end() ; button_itr++ )
        {
            button_itr->append( L"\ninput button" );

            // get previous item text right side
            if( button_itr not_eq input_buttons.begin() )
                position.x( ( button_itr - 1 )->right() + 20.0f );
            
            button_itr->set_position( position );
        }
        // --------------------------------------------------------------------

        // place input values [collection]->[in buttons]->[in values]
        if( input_buttons.empty() )
        {
            position = { information.right() + 20.0f, information.top() };
        }
        else
        {   // place after input buttons
            position.x( input_buttons.back().right() + 20.f );
            position.y( input_buttons.back().top() );
        }

        auto value_itr = input_values.begin();

        for( ; value_itr < input_values.end() ; value_itr++ )
        {
            value_itr->append_text( L"\ninput value" );

             // get previous item text right side
            if( value_itr not_eq input_values.begin() )
                position.x( ( value_itr - 1 )->right() + 20.0f );

            value_itr->set_position( position );
        }
        // --------------------------------------------------------------------

        // place output buttons [collection]->[in buttons]->[in values]->[out buttons]
        if( input_values.empty() )
        {
            if( input_buttons.empty() )
                position = { information.right() + 20.0f, information.top() };
            else
            {   // place after input buttons
                position.x( input_buttons.back().right() + 20.f );
                position.y( input_buttons.back().top() );
            }
        }
        else
        {   // place after input values
            position.x( input_values.back().right() + 20.f );
            position.y( input_values.back().top() );
        }

        button_itr = output_buttons.begin();

        for( ; button_itr < output_buttons.end() ; button_itr++ )
        {
            button_itr->append( L"\noutput button" );

            if( button_itr not_eq output_buttons.begin() )
                position.x( ( button_itr - 1 )->right() + 20.0f );

            button_itr->set_position( position );
        }
        // --------------------------------------------------------------------

        // place output values  
        // [collection]->[in buttons]->[in values]->[out buttons]->[out values]
        if( output_buttons.empty() )
        {
            if( input_values.empty() )
            {
                if( input_buttons.empty() )
                    position = { information.right() + 20.0f, information.top() };
                else
                {
                    position.x( input_buttons.back().right() + 20.f );
                    position.y( input_buttons.back().top() );
                }
            }
            else 
            {
                position.x( input_values.back().right() + 20.f );
                position.y( input_values.back().top() );
            }

        }
        else
        {   // place after outputbuttons
            position.x( output_buttons.back().right() + 20.f );
            position.y( output_buttons.back().top() );
        }

        value_itr = output_values.begin();

        for( ; value_itr < output_values.end() ; value_itr++ )
        {
            button_itr->append_text( L"\noutput value" );

            if( value_itr not_eq output_values.begin() )
                position.x( ( value_itr - 1 )->right() + 20.0f );

            value_itr->set_position( position );
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
                        position = { information.right() + 20.0f, information.top() };
                    else
                    {
                        position.x( input_buttons.back().right() + 20.f );
                        position.y( input_buttons.back().top() );
                    }
                }
                else
                {
                    position.x( input_values.back().right() + 20.f );
                    position.y( input_values.back().top() );
                }
            }
            else
            {
                position.x( output_buttons.back().right() + 20.f );
                position.y( output_buttons.back().top() );
            }
        }
        else
        {   // place after output buttons
            position.x( output_values.back().right() + 20.f );
            position.y( output_values.back().top() );
        }

        button_itr = feature_buttons.begin();
        for( ; button_itr < feature_buttons.end() ; button_itr++ )
        {
            button_itr->append_text( L"\nfeature button" );

            if( button_itr not_eq feature_buttons.begin() )
                position.x( ( button_itr - 1 )->right() + 20.0f );

            button_itr->set_position( position );
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
                            position ={ information.right() + 20.0f, information.top() };
                        else
                        {
                            position.x( input_buttons.back().right() + 20.f );
                            position.y( input_buttons.back().top() );
                        }
                    }
                    else
                    {
                        position.x( input_values.back().right() + 20.f );
                        position.y( input_values.back().top() );
                    }
                }
                else
                {
                    position.x( output_buttons.back().right() + 20.f );
                    position.y( output_buttons.back().top() );
                }
            }
            else
            {   // place after outputbuttons
                position.x( output_values.back().right() + 20.f );
                position.y( output_values.back().top() );
            }
        }
        else
        {   // place output buttons after output_buttons
            position.x( feature_buttons.back().right() + 20.f );
            position.y( feature_buttons.back().top() );
        }

        value_itr = feature_values.begin();
        for( ; value_itr < feature_values.end() ; value_itr++ )
        {
            value_itr->append_text( L"\nfeature value" );

            if( value_itr not_eq feature_values.begin() )
                position.x( ( value_itr - 1 )->right() + 20.0f );

            value_itr->set_position( position );
        }
        // --------------------------------------------------------------------
    }

    void Collection::update( RAWINPUT * in_raw_data )
    {
        for( auto & button : input_buttons ) button.update( in_raw_data );
        for( auto & value  : input_values  ) value.update( in_raw_data );
    }

    void Collection::draw()
    {
        information.draw();

        for( auto & button : input_buttons  ) button.draw();
        for( auto & value  : input_values   ) value.draw();
        
        for( auto & button : output_buttons ) button.draw();
        for( auto & value  : output_values  ) value.draw();

        for( auto & button : feature_buttons ) button.draw();
        for( auto & value  : feature_values  ) value.draw();
    }

    Range Collection::get_range( ushort in_page ,
                                 ushort in_usage ,
                                 Report_type in_report_type ,
                                 Item_type in_item_type )
    {
        /*

        std::vector< Value >::const_iterator vector_iterator {};
        std::vector< Value >::const_iterator vector_end {};

        switch( report_type )
        {
            case Report_type::input:
            {
                vector_iterator = input_values.cbegin();
                vector_end = input_values.cend();
            } break;

            case Report_type::output:
            {
                vector_iterator = output_values.cbegin();
                vector_end = output_values.cend();
            } break;

            case Report_type::feature:
            {
                vector_iterator = feature_values.cbegin();
                vector_end = feature_values.cend();
            } break;
        }

        //if( *vector_pointer->empty() ) return { 0l , 0l };

        //range values(0,0);

        for( ; vector_iterator != vector_end ; vector_iterator++ )
        {
            if( page == vector_iterator->UsagePage and usage == vector_iterator->Range.UsageMin )
            {
                switch( item_type )
                {
                    case Item_type::logical
                        return { vector_iterator->LogicalMin , vector_iterator->LogicalMax };
                    break;

                    case Item_type::physical
                        return { vector_iterator->PhysicalMin , vector_iterator->PhysicalMax };
                    break;

                    case Item_type::usage
                        return { vector_iterator->Range.UsageMin , vector_iterator->Range.UsageMax };
                    break;

                    case Item_type::string
                        return { vector_iterator->Range.StringMin, vector_iterator->Range.StringMax };
                    break;

                    case Item_type::designator
                        return { vector_iterator->Range.DesignatorMin , vector_iterator->Range.DesignatorMax };
                    break;

                    case Item_type::data_index
                        return { vector_iterator->Range.DataIndexMin , vector_iterator->Range.DataIndexMax };
                    break;
                } // switch in_value_type

            } // if page and usage the same

        } // vector loop

        */

        return { 0 , 0 }; // vector empty
    }
    

    /*
    uint Collection::get_contact_amount()
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

    uint Collection::get_contact_identifier()
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

    uint Collection::get_x()
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

    uint Collection::get_y()
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

} // namespace HID