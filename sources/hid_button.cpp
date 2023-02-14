#include "..\headers\hid_button.h"   

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include <bitset>

namespace hid
{
    
    hid_button::hid_button( hid_device * in_device , const _HIDP_BUTTON_CAPS & construct_button )
    {
        if( this not_eq &construct_button ) // prevents self assignment a = a;
        {
            device = in_device;
            UsagePage = construct_button.UsagePage;
            ReportID = construct_button.ReportID;
            IsAlias = construct_button.IsAlias;
            BitField = construct_button.BitField;
            LinkCollection = construct_button.LinkCollection;
            LinkUsage = construct_button.LinkUsage;
            LinkUsagePage = construct_button.LinkUsagePage;
            IsRange = construct_button.IsRange;
            IsStringRange = construct_button.IsStringRange;
            IsDesignatorRange = construct_button.IsDesignatorRange;
            IsAbsolute = construct_button.IsAbsolute;
            ReportCount = construct_button.ReportCount;

            Range.UsageMin = construct_button.Range.UsageMin;
            Range.UsageMax = construct_button.Range.UsageMax;
            Range.StringMin = construct_button.Range.StringMin;
            Range.StringMax = construct_button.Range.StringMax;
            Range.DesignatorMin = construct_button.Range.DesignatorMin;
            Range.DesignatorMax = construct_button.Range.DesignatorMax;
            Range.DataIndexMin = construct_button.Range.DataIndexMin;
            Range.DataIndexMax = construct_button.Range.DataIndexMax;

            NotRange.Usage = construct_button.NotRange.Usage;
            NotRange.StringIndex = construct_button.NotRange.StringIndex;
            NotRange.DesignatorIndex = construct_button.NotRange.DesignatorIndex;
            NotRange.DataIndex = construct_button.NotRange.DataIndex;
        }
    }
   
    void hid_button::set_information_text()
    {
        content = locate::get_usages().page( UsagePage );

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
            content += L'\n' + locate::get_usages().usage( UsagePage , NotRange.Usage );
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
        information.set_content( content );
        information.set_font_size( 10.0f );
        information.set_font_colour( D2D1::ColorF::Yellow );
        information.set_layout_size( { 200.0f, 200.0f } );
    };

    void hid_button::update_information_text()
    {
        content = on ? L"\non" : L"\noff";
        information.set_content( content );
    }

    void hid_button::update( RAWINPUT * in_raw_data )
    //void hid_button::update( RAWHID in_raw_data )
    {
        USAGE usages;// { nullptr }; // active buttons in page
        ulong usages_amount { 1 };
        //usages_amount[0]=1;

        // if( not IsRange )
        HidP_GetUsages( HidP_Input , // requires complete input report and not only rawhid
                        UsagePage ,
                        LinkCollection ,
                        &usages ,
                        &usages_amount ,
                        reinterpret_cast< PHIDP_PREPARSED_DATA >( device->get_data() ) ,
                        reinterpret_cast< char * >( in_raw_data->data.hid.bRawData ) , //BYTE uchar to char // M.S. your data types don't match up !! :(
                        in_raw_data->data.hid.dwSizeHid * in_raw_data->data.hid.dwCount );

        if( usages == NotRange.Usage ) 
        {
            on = true;
        }
        else on = false;

        //update_information_text();
        set_information_text();
    }
}