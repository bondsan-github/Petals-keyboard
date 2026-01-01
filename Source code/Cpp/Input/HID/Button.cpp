#include "Input\HID\Button.h"

#include "Input\HID\Usages.h"
#include "Input\HID\Device.h"

#include <hidusage.h>

#include <bitset>

namespace HID
{
    Button::Button( Device & device, const button_caps & button_capabilities )
    : device( device )
    {
    }
   
    void Button::collect_information()
    {
        if( IsRange )
        {
            content += L'\n';

            for( uint button_usage = Range.UsageMin; button_usage <= Range.UsageMax; button_usage++ )
            {
                content += usage( UsagePage , button_usage );
                content += L",";
            }
        }
        else
        {
            content += L'\n' + usage( UsagePage , NotRange.Usage );
        }

        //content += IsAlias ? L"alias" : L"not aliased"; // does button have multiple usages

        /*
        if( (BitField & 0b1) ) content += L"\nconstant"; // bit 0
        //else content += L" data ";
        if( BitField & 0b10 ) content += L"\nvariable"; // bit 1
        //else content += L" array ";
        if( BitField & 0b100 ) content += L"\nrelative";// bit 2
        //else content += L" absolute ";
        if( BitField & 0b1000 ) content += L"\nwrap";// bit 3
        //else content += L" no wrap ";
        if( BitField & 0b10000 ) content += L"\nnonlinear";// bit 4
        //else content += L" linear ";
        if( BitField & 0b100000 ) content += L"\nno preferred state";// bit 5
        //else content += L" preferred ";
        if( BitField & 0b1000000 ) content += L"\nvolatile";// bit 6
        //else content += L" non-volatile ";
        //if( BitField and 0b10000000 ) content += L" reserved ";// bit 7
        //else content += L" reserved ";
        if( BitField & 0b100000000 ) content += L"\nbuffered bytes";// bit 8
        //else content += L" bit field ";
        */

        //content += L"\nis range\t: ";
        //content += IsRange ? L"true" : L"false";
        //content += L"\nis alias\t: ";
        //content += IsAlias ? L"true" : L"false";
        //content += L"\nis string range\t: "; //HidD_GetIndexedString
        //content += IsStringRange ? L"true" : L"false";
        //content += L"\nis designator range \t: "; // physical descriptor
        //content += IsDesignatorRange ? L"true" : L"false";
        //content += L"\nis absolute: ";
        //content += IsAbsolute ? L"\nabsolute" : L"\nrelative";
        //if( ReportCount > 1 ) content += L"\n more than one report";

        content += L"\ndata index\t: " + std::to_wstring( NotRange.DataIndex );
        content += L"\nreport id\t: " + std::to_wstring( ReportID ); // converted from hex to decimal
        content += on ? L"\non" : L"\noff";

        information.set( content );
        information.size( 10.0f );
        information.colour( D2D1::ColorF::Yellow );
        information.layout_size( { 200.0f, 200.0f } );
    };

    void Button::update_information()
    {
        content = on ? L"\non" : L"\noff";
        information.set( content );
    }

    void Button::update( RAWINPUT * in_raw_data )
    //void Button::update( RAWHID in_raw_data )
    {
        USAGE usages;// { nullptr }; // active buttons in page
        ulong usages_amount { 1 };
        //usages_amount[0]=1;

        // if( not IsRange )
        HidP_GetUsages( HidP_Input , // requires complete input report and not only rawhid
                        UsagePage ,
                        LinkCollection ,
                        & usages ,
                        & usages_amount ,
                        reinterpret_cast< PHIDP_PREPARSED_DATA >( device.data() ) ,
                        reinterpret_cast< char * >( in_raw_data->data.hid.bRawData ) , //BYTE uchar to char // M.S. your data types don't match up !! :(
                        in_raw_data->data.hid.dwSizeHid * in_raw_data->data.hid.dwCount );

        if( usages == NotRange.Usage ) 
        {
            on = true;
        }
        else on = false;

        update_information();
    }
}