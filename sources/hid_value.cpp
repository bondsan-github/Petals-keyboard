#include "..\headers\hid_value.h"
#include "..\headers\locate.h"
#include <unordered_map>
#include "..\headers\hid_device.h"
#include "..\headers\utility.h"

namespace hid
{

    hid_value::hid_value( hid_device * const in_device , const _HIDP_VALUE_CAPS & construct_value )
    {
        //if( this not_eq &construct_value )
        //{
            device = in_device;
            value_signed = value_signed;

            UsagePage = construct_value.UsagePage;
            ReportID = construct_value.ReportID;
            IsAlias = construct_value.IsAlias;
            BitField = construct_value.BitField;
            LinkCollection = construct_value.LinkCollection;
            LinkUsage = construct_value.LinkUsage;
            LinkUsagePage = construct_value.LinkUsagePage;
            IsRange = construct_value.IsRange;
            IsStringRange = construct_value.IsStringRange;
            IsDesignatorRange = construct_value.IsDesignatorRange;
            IsAbsolute = construct_value.IsAbsolute;
            HasNull = construct_value.HasNull;
            BitSize = construct_value.BitSize;
            ReportCount = construct_value.ReportCount;
            UnitsExp = construct_value.UnitsExp;
            Units = construct_value.Units;
            LogicalMin = construct_value.LogicalMin;
            LogicalMax = construct_value.LogicalMax;
            PhysicalMin = construct_value.PhysicalMin;
            PhysicalMax = construct_value.PhysicalMax;

            Range.UsageMin = construct_value.Range.UsageMin;
            Range.UsageMax = construct_value.Range.UsageMax;
            Range.StringMin = construct_value.Range.StringMin;
            Range.StringMax = construct_value.Range.StringMax;
            Range.DesignatorMin = construct_value.Range.DesignatorMin;
            Range.DesignatorMax = construct_value.Range.DesignatorMax;
            Range.DataIndexMin = construct_value.Range.DataIndexMin;
            Range.DataIndexMax = construct_value.Range.DataIndexMax;

            NotRange.Usage = construct_value.NotRange.Usage;
            NotRange.StringIndex = construct_value.NotRange.StringIndex;
            NotRange.DesignatorIndex = construct_value.NotRange.DesignatorIndex;
            NotRange.DataIndex = construct_value.NotRange.DataIndex;

            if( UsagePage == 0x0d and NotRange.Usage == 0x51 )//contact_identifier
                locate::get_input_devices().get_device( device->get_handle() )->set_contact_identifier( this );
            else if( UsagePage == 0x01 and NotRange.Usage == 0x30 )// X
                locate::get_input_devices().get_device( device->get_handle() )->set_x( this );
        //}
    }

    void hid_value::set_information_text()
    {
        content += locate::get_usages().page(UsagePage);

        if( IsRange )
        {
            content += L'\n';

            for( uint button_usage = Range.UsageMin; button_usage <= Range.UsageMax; button_usage++ )
            {
                content += locate::get_usages().usage( UsagePage , button_usage );
                content += L",";
            }
        }
        else
        {
            content += L'\n';
            content += locate::get_usages().usage( UsagePage , NotRange.Usage );
        }

        // UNsigned long 32 bits / 4 bytes, only need last 16 bits / 2 bytes
        // high nibble = [ 0000 ] 0000
        // low nibble  = 0000 [ 0000 ]
        //__int8 = microsoft , uint8_t = std:: unsigned char
        // https://stackoverflow.com/questions/6752567/casting-a-large-number-type-to-a-smaller-type

        // Let nibbles be the result of interpreting value as a sequence of 
        // eight 4 - bit signed two's complement integers starting from the low-order bits.
        /*
        If nibbles[0] is:
            0, then set globalState["unitSystem"] to "none"
            1, then set globalState["unitSystem"] to "si-linear"
            2, then set globalState["unitSystem"] to "si-rotation"
            3, then set globalState["unitSystem"] to "english-linear"
            4, then set globalState["unitSystem"] to "english-rotation"
            -1, then set globalState["unitSystem"] to "vendor-defined"
            Otherwise, set globalState["unitSystem"] to "reserved"

            Set globalState["unitFactorLengthExponent"] to nibbles[1].
            Set globalState["unitFactorMassExponent"] to nibbles[2].
            Set globalState["unitFactorTimeExponent"] to nibbles[3].
            Set globalState["unitFactorTemperatureExponent"] to nibbles[4].
            Set globalState["unitFactorCurrentExponent"] to nibbles[5].
            Set globalState["unitFactorLuminousIntensityExponent"] to nibbles[6].
        */

        //Units;
        //UnitsExp;
        // 0x11   = 0b 0001'0001 = length , centimeter , 10^-2 ( ? = 0.1mm ) 
        // 
        // 0x1001 = 0b 0001'0000  0000'0001 =       , 10^-4
        uint8_t bit_mask   = 0xFFFF;
        uint8_t last_2bytes  = Units & bit_mask; // manual casting and not implementation specific
        //uint8_t high_byte = ( last_2bytes & 0xFF00 ) >> 4;
        uint8_t low_byte =  last_2bytes & 0xFF;

        uint8_t high_nible = ( low_byte & 0xF0 ) >> 4;//; = system
        uint8_t low_nible  = low_byte & 0xF;
        
        std::unordered_map< uint8_t , std::wstring > unit_system // high_nible
        {
            { 0x0  , L"system"             } , // 0b0       , 0x0  , 0 
            { 0x1  , L"length"             } , // 0b1       , 0x1  , 1
            { 0x2  , L"mass"               } , // 0b10      , 0x2  , 2
            { 0x4  , L"time"               } , // 0b100     , 0x4  , 4
            { 0x8  , L"temperature"        } , // 0b1'000   , 0x8  , 8
            { 0x10 , L"current"            } , // 0b10'000  , 0x10 , 16
            { 0x20 , L"luminous intensity" } , // 0b100'000 , 0x20 , 32 
        };

        //https://github.com/microsoft/hidtools/blob/main/Waratah/HidSpecification/HidConstants.cs
        /*public enum UnitItemSystemKind
        {
            None = 0x00 ,
            SiLinear = 0x01 ,
            SiRotation = 0x02 ,
            EnglishLinear = 0x03 ,
            EnglishRotation = 0x04 ,
            // 0x05 - 0xE are reserved.
            Vendor = 0x0F ,
        }*/

        // 0x1 = 0b1
        // 0x2  = 0b
        // 0x3  = 0b
        // 0x4  = 0b
        // 0x5  = 0b
        // 0x6  = 0b
        // 0x7  = 0b

        if( high_nible )
        {
            content += L'\n' + unit_system.at( high_nible );
        }

        std::vector< std::vector < std::wstring > > units
        {
            {  // 0 = none
            } ,

            { // length
                { L"centimeter" } ,
                { L"radians"    } ,
                { L"inch"       } ,
                { L"degrees"    }
            } ,

            { // mass
                { L"gram" } ,
                { L"gram" } ,
                { L"slug" } ,
                { L"slug" }
            } ,

            { // time
                { L"seconds" } ,
                { L"seconds" } ,
                { L"seconds" } ,
                { L"seconds" } ,
            } ,

            { // temperature

            } ,

            { //current
            } ,

            { //luminous intensity
            }
        };

        if( low_nible and high_nible )
        {
            content += L' ' + units.at( high_nible ).at( low_nible );
        }

        using key = short; 
        //using value = short; 
        std::unordered_map< key , short > unit_exponent
        {
            { 0x1 ,  1 } ,
            { 0x2 ,  2 } ,
            { 0x3 ,  3 } ,
            { 0x4 ,  4 } ,
            { 0x5 ,  5 } ,
            { 0x6 ,  6 } ,
            { 0x7 ,  7 } ,
            { 0x8 , -8 } ,
            { 0x9 , -7 } ,
            { 0xA , -6 } ,
            { 0xB , -5 } ,
            { 0xC , -4 } ,
            { 0xD , -3 } ,
            { 0xE , -2 } ,
            { 0xF , -1 } ,
        };

        if( UnitsExp && UnitsExp <= 0xf )
            content += L'\n' + std::to_wstring(unit_exponent.find(UnitsExp)->second);

        content += L"\nlog min: " + std::to_wstring( LogicalMin ) + L" max: " + std::to_wstring( LogicalMax );
        content += L"\nphy min: " + std::to_wstring( PhysicalMin ) + L" max: " + std::to_wstring( PhysicalMax );
        
        //content += IsAlias ? L"\nalias" : L"\nnot aliased";

        /*
        if( BitField & 0b1 ) content += L"\nconstant"; // bit 0
        if( BitField & 0b10 ) content += L"\nvariable"; // bit 1
        if( BitField & 0b100 ) content += L"\nrelative";// bit 2
        if( BitField & 0b1000 ) content += L"\nwrap";// bit 3
        if( BitField & 0b10000 ) content += L"\nnonlinear";// bit 4
        if( BitField & 0b100000 ) content += L"\nno preferred state";// bit 5
        if( BitField & 0b1000000 ) content += L"\nvolatile";// bit 6
        if( BitField & 0b100000000 ) content += L"\nbuffered bytes";// bit 8
        */

        /*
        ulong usage_amount = HidP_MaxUsageListLength( // amount of buttons in report
            HidP_Input ,
            UsagePage,
            reinterpret_cast< PHIDP_PREPARSED_DATA >( device->get_data() )
        );
        content += L"\nusage amount\t: " + std::to_wstring( usage_amount );
        */

        content += IsRange ? L"\nis range" : L"\nnot range";
        content += L"\nbit size\t:" + std::to_wstring( BitSize );
        content += L"\nreport count\t:" + std::to_wstring( ReportCount );
        content += L"\ndata index\t: " + std::to_wstring( NotRange.DataIndex );
        content += L"\nreport id\t: " + std::to_wstring( ReportID );
        content += L"\nvalue\t:" + std::to_wstring( value_signed );

        information.set_content( content );
        information.set_font_size( 10.0f );
        information.set_font_colour( D2D1::ColorF::Yellow );
        information.set_layout_size( { 200.0f, 200.0f } );

        //Resolution = ( Logical Maximum – Logical Minimum ) / ( ( Physical Maximum – Physical Minimum ) *
        //                                                      ( 10 Unit Exponent ) )
    }

    void hid_value::update_information_text() 
    { 
        content = L"\nvalue\t:" + std::to_wstring( value_signed );
        information.set_content( content );
    }

    //void hid_value::update( RAWIHID in_raw_data )
    void hid_value::update( RAWINPUT & in_raw_data )
    {
        // if( not IsRange )
        //NTSTATUS status = HidP_GetUsageValue( HidP_Input ,// unsigned output // // requires complete input report and not only rawhid
        HidP_GetScaledUsageValue( HidP_Input , // signed output
                                              UsagePage ,
                                              LinkCollection ,
                                              NotRange.Usage ,
                                              &value_signed ,
                                              reinterpret_cast< PHIDP_PREPARSED_DATA >( device->get_data() ) ,
                                              reinterpret_cast< char * >( in_raw_data.data.hid.bRawData ) , //BYTE uchar to char // M.S. your data types don't match up !! :(
                                              in_raw_data.data.hid.dwSizeHid * in_raw_data.data.hid.dwCount );

        //if( status != HIDP_STATUS_SUCCESS ) error_exit( L"hid_value:get_value");
        
        update_information_text();
        /*
        if( UsagePage == 0x01 and NotRange.Usage == 0x31 )// generic : Y
        {
            std::wstring message = L"\nY: " + std::to_wstring( value_unsigned );
            OutputDebugStringW( message.data() );
            
        }
        else if( UsagePage == 0x01 and NotRange.Usage == 0x30 )// X
        {
            std::wstring message = L"\nX: " + std::to_wstring( value_unsigned );
            OutputDebugStringW( message.data() );
        }
        else if( UsagePage == 0x0d and NotRange.Usage == 0x51 )//contact_identifier
        {
            std::wstring message = L"\ncontact id: " + std::to_wstring( value_unsigned );
            OutputDebugStringW( message.data() );
            //locate::get_input_devices().get_device( in_raw_data.header.hDevice )->add_contact( value_unsigned );
            set_information_text();
        }
        else if( UsagePage == 0x0d and NotRange.Usage == 0x47 )// touch valid
        {

        }
        else if( UsagePage == 0x0d and NotRange.Usage == 0x54 )// contact amount
        { 
        } 
        */

        /*
        HidP_GetUsageValueArray( HidP_Input ,
                                 UsagePage ,
                                 LinkCollection ,
                                 NotRange.Usage ,
                                 values.data() ,
                                 values_size ,
                                 reinterpret_cast< PHIDP_PREPARSED_DATA >( device->get_data() ) ,
                                 reinterpret_cast< char * >( in_raw_data.bRawData ) , //BYTE uchar to char // M.S. your data types don't match up !! :(
                                 in_raw_data.dwSizeHid * in_raw_data.dwCount );
        */
        
    }
}