#include "Input\HID\Button.h"

#include "Input\HID\Types.h"
#include "Input\HID\Usages.h"
#include "Input\HID\Device.h"

#include <hidusage.h>

//#include <bitset>

namespace HID
{
    Button::Button( const button_caps & capabilities )
    {
        //*this = capabilities;

        UsagePage = capabilities.UsagePage;
        ReportID = capabilities.ReportID;
        IsAlias = capabilities.IsAlias;

        BitField = capabilities.BitField;
        LinkCollection = capabilities.LinkCollection;   // A unique internal index pointer

        LinkUsage = capabilities.LinkUsage;
        LinkUsagePage = capabilities.LinkUsagePage;

        IsRange = capabilities.IsRange;
        IsStringRange = capabilities.IsStringRange;
        IsDesignatorRange = capabilities.IsDesignatorRange;
        IsAbsolute = capabilities.IsAbsolute;

        ReportCount = capabilities.ReportCount;   // Available in API version >= 2 only.

        //if( capabilities.IsRange || capabilities.IsStringRange || capabilities.IsDesignatorRange )
        Range.UsageMin = capabilities.Range.UsageMin;
        Range.UsageMax = capabilities.Range.UsageMax;
        Range.StringMin = capabilities.Range.StringMin;
        Range.StringMax = capabilities.Range.StringMax;
        Range.DesignatorMin = capabilities.Range.DesignatorMin;
        Range.DesignatorMax = capabilities.Range.DesignatorMax;
        Range.DataIndexMin = capabilities.Range.DataIndexMin;
        Range.DataIndexMax = capabilities.Range.DataIndexMax;

        //else
        NotRange.Usage = capabilities.NotRange.Usage;
        NotRange.StringIndex = capabilities.NotRange.StringIndex;
        NotRange.DesignatorIndex = capabilities.NotRange.DesignatorIndex;
        NotRange.DataIndex = capabilities.NotRange.DataIndex;
    }

    void Button::collect_info()
    {
        if( IsRange )
        {
            info += L'\n';

            for( uint button_usage = Range.UsageMin; button_usage <= Range.UsageMax; button_usage++ )
            {
                info += usage( UsagePage , button_usage );
                info += L",";
            }
        }
        else
        {
            info += L'\n' + usage( UsagePage , NotRange.Usage );
        }

        //info += IsAlias ? L"alias" : L"not aliased"; // does button have multiple usages?

        /*
        if( (BitField & 0b1) ) info += L"\nconstant"; // bit 0
        //else info += L" data ";
        if( BitField & 0b10 ) info += L"\nvariable"; // bit 1
        //else info += L" array ";
        if( BitField & 0b100 ) info += L"\nrelative";// bit 2
        //else info += L" absolute ";
        if( BitField & 0b1000 ) info += L"\nwrap";// bit 3
        //else info += L" no wrap ";
        if( BitField & 0b10000 ) info += L"\nnonlinear";// bit 4
        //else info += L" linear ";
        if( BitField & 0b100000 ) info += L"\nno preferred state";// bit 5
        //else info += L" preferred ";
        if( BitField & 0b1000000 ) info += L"\nvolatile";// bit 6
        //else info += L" non-volatile ";
        //if( BitField and 0b10000000 ) info += L" reserved ";// bit 7
        //else info += L" reserved ";
        if( BitField & 0b100000000 ) info += L"\nbuffered bytes";// bit 8
        //else info += L" bit field ";
        */

        //info += L"\nis range\t: ";
        //info += IsRange ? L"true" : L"false";
        //info += L"\nis alias\t: ";
        //info += IsAlias ? L"true" : L"false";
        //info += L"\nis string range\t: "; //HidD_GetIndexedString
        //info += IsStringRange ? L"true" : L"false";
        //info += L"\nis designator range \t: "; // physical descriptor
        //info += IsDesignatorRange ? L"true" : L"false";
        //info += L"\nis absolute: ";
        //info += IsAbsolute ? L"\nabsolute" : L"\nrelative";
        //if( ReportCount > 1 ) info += L"\n more than one report";

        info += L"\ndata index\t: " + std::to_wstring( NotRange.DataIndex );
        info += L"\nreport id\t: " + std::to_wstring( ReportID ); // converted from hex to decimal
        info += on ? L"\non" : L"\noff";
    };

    //void Button::update_information()
    //{
    //    info = on ? L"\non" : L"\noff";
    //    information.set( info );
    //}

    //void Button::update( RAWINPUT * data )
    //void Button::update( RAWHID data )
    void Button::update( vector< uchar > & data )
    {
        // HidP_GetData 
        //DataIndex 
        
        /*
        NTSTATUS HidP_GetData(
            HIDP_REPORT_TYPE     ReportType ,
            PHIDP_DATA           DataList ,
            PULONG               DataLength ,
            PHIDP_PREPARSED_DATA PreparsedData ,
            PCHAR                Report ,
            ULONG                ReportLength
        );
        */


        USAGE usages;// { nullptr }; // active buttons in page
        ulong usages_amount { 1 };
        //usages_amount[0]=1;

        /*
        // if( ! IsRange )
        HidP_GetUsages( HidP_Input , // requires complete input report and not only rawhid
                        UsagePage ,
                        LinkCollection ,
                        & usages ,
                        & usages_amount ,
                        reinterpret_cast< PHIDP_PREPARSED_DATA >( data.data() ) ,
                        reinterpret_cast< char * >( data->data.hid.bRawData ) , //BYTE uchar to char // M.S. your data types don't match up !! :(
                        data->data.hid.dwSizeHid * data->data.hid.dwCount );
        */
        if( usages == NotRange.Usage ) 
        {
            on = true;
        }
        else on = false;

        //update_information();
    }
}