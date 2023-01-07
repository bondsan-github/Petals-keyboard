#include "..\headers\hid_local_item.h"   

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include <bitset>

namespace hid
{
    hid_local_item::hid_local_item() 
    {
        OutputDebugString( L"\n hid_local_item::default constructor" );
    }
    
    hid_local_item::hid_local_item( const hid_local_item & in_copy ) 
    { 
        //OutputDebugString( L"\n hid_local_item::copy constructor" );
        
        if( this != &in_copy ) *this = in_copy;
    }
    
    hid_local_item::hid_local_item( hid_local_item && in_move ) noexcept
    {
        //OutputDebugString( L"\n hid_local_item::move constructor" );

        if( this != &in_move ) *this = std::move( in_move );
    }

    hid_local_item & hid_local_item::operator = ( const hid_local_item & assign_copy ) 
    {
        OutputDebugString( L"\n hid_local_item::assign_copy" );

        if( this != &assign_copy )
        { 
            report_index     = assign_copy.report_index;
            report_amount    = assign_copy.report_amount;
            bit_field        = assign_copy.bit_field;
            is_absolute      = assign_copy.is_absolute;
            origin_usage     = assign_copy.origin_usage;
            is_range         = assign_copy.is_range;
            usages           = assign_copy.usages;
            data_identifier  = assign_copy.data_identifier;
            data_identifiers = assign_copy.data_identifiers;
            has_strings      = assign_copy.has_strings;
            string           = assign_copy.string;
            has_designators  = assign_copy.has_designators;
            designator       = assign_copy.designator;
            designators      = assign_copy.designators;
            information      = assign_copy.information;
        }

        return *this;
    }

    hid_local_item & hid_local_item::operator = ( hid_local_item && assign_move ) noexcept
    {
        if( this != &assign_move )
        {
            report_index     = std::move( assign_move.report_index );
            report_amount    = std::move( assign_move.report_amount );
            bit_field        = std::move( assign_move.bit_field );
            is_absolute      = std::move( assign_move.is_absolute );
            origin_usage     = std::move( assign_move.origin_usage );
            is_range         = std::move( assign_move.is_range );
            usages           = std::move( assign_move.usages );
            data_identifier  = std::move( assign_move.data_identifier );
            data_identifiers = std::move( assign_move.data_identifiers );
            has_strings      = std::move( assign_move.has_strings );
            string           = std::move( assign_move.string );
            has_designators  = std::move( assign_move.has_designators );
            designator       = std::move( assign_move.designator );
            designators      = std::move( assign_move.designators );
            information      = std::move( assign_move.information );

            assign_move.reset();
        }

        return *this;
    }

    void hid_local_item::reset()
    {
        report_index     = 0;
        report_amount    = 0;
        bit_field        = 0;
        is_absolute      = false;
        origin_usage     = 0;
        is_range         = false;
        usages           = hid_range{ 0l,0l };
        data_identifier  = 0;
        data_identifiers = hid_range{ 0l,0l };
        has_strings      = false;
        string           = 0;
        has_designators  = false;
        designator       = 0;
        designators      = hid_range{ 0l,0l };

        information.reset();
    }

    hid_local_item::~hid_local_item() 
    {
        OutputDebugStringW( L"\n hid_local_item::de-constructor" );
    }

    void hid_local_item::set_information()
    {
        std::wstring text;

        //text += L"index\t: ";
        //text += std::to_wstring( get_index() );

        text += L"\npage\t: ";
        text += locate::get_usages().page( get_page() );

        text += L"\norigin usage\t: ";
        text += locate::get_usages().usage( origin_page , origin_usage );

        text += L"\norigin page\t: ";
        text += locate::get_usages().page( origin_page );

        if( is_range )
        {
            text += L"\nusages\t: ";
            
            for( long usage = usages.begin ; usage < usages.end ; usage++ )
            {
                text += L"\nusage\t: ";
                text += locate::get_usages().usage( get_page() , usage );
            }
        }
        else
        {
            text += L"\nusage\t: ";
            text += locate::get_usages().usage( get_page() , get_usage() );
        }

        text += L"\nreport\t: ";
        text += std::to_wstring( report_index );

        if( report_amount )
        {
            text += L"\nreport amount\t: ";
            text += report_amount;
        }

        if( is_absolute ) text += L"\ndata is absolute";
        else              text += L"\ndata is relative";

        if( bit_field )
        {
            text += L"\nbit field\t: ";
            //text += std::bitset< 16 >( bit_field ).to_string< wchar_t , char_traits< wchar_t > , allocator< wchar_t > >();
        }

        // switch page 

        //text += has_strings;
        //text += has_designators;

        information.set_content( text );
    };
}