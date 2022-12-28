#include "..\headers\hid_global_item.h"

namespace hid
{
    hid_global_item::hid_global_item() 
    {
        OutputDebugString( L"\n hid_global_item::default constructor" );
    }
    
    hid_global_item::hid_global_item( const hid_global_item & in_copy ) 
    {
        OutputDebugString( L"\n hid_global_item::copy constructor" );

        if( this != &in_copy ) *this = in_copy;
    }
    
    hid_global_item::hid_global_item( hid_global_item && in_move ) noexcept
    {
        OutputDebugString( L"\n hid_global_item::move constructor" );

        if( this != &in_move ) *this = std::move( in_move );
    }

    hid_global_item & hid_global_item::operator = ( const hid_global_item & assign_copy )
    {
        OutputDebugString( L"\n hid_global_item::assignment copy" );

        if( this != &assign_copy )
        {
            main_item     = assign_copy.main_item;
            bit_amount    = assign_copy.bit_amount;
            unit_exponent = assign_copy.unit_exponent;
            unit          = assign_copy.unit;
            has_null      = assign_copy.has_null;
            is_absolute   = assign_copy.is_absolute;
            physical      = assign_copy.physical;
            logical       = assign_copy.logical;
        }

        return *this;
    }

    hid_global_item & hid_global_item::operator = ( hid_global_item && assign_move ) noexcept
    {
        OutputDebugString( L"\n hid_global_item::assignment move" );

        if( this != &assign_move )
        {
            main_item     = std::move( assign_move.main_item );
            bit_amount    = std::move( assign_move.bit_amount );
            unit_exponent = std::move( assign_move.unit_exponent );
            unit          = std::move( assign_move.unit );
            has_null      = std::move( assign_move.has_null );
            is_absolute   = std::move( assign_move.is_absolute );
            physical      = std::move( assign_move.physical );
            logical       = std::move( assign_move.logical );

            assign_move.reset();
        }

        return *this;
    }

    void hid_global_item::reset()
    {
        main_item     = 0u;
        bit_amount    = 0u;
        unit_exponent = 0u;
        unit          = 0u;
        has_null      = false;
        is_absolute   = false;
        physical      = limits{ 0l , 0l };
        logical       = limits{ 0l , 0l };
    }
    
    hid_global_item::~hid_global_item() 
    {
        OutputDebugString( L"\n hid_global_item::de-constructor" );
    }
}