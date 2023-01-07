#include "..\headers\hid_button.h"   

#include "..\headers\locate.h"
#include "..\headers\hid_usages.h"
#include <bitset>

namespace hid
{

    void hid_button::operator = ( const _HIDP_BUTTON_CAPS & in_button )
    {
        UsagePage = in_button.UsagePage;
        ReportID = in_button.ReportID;
        IsAlias = in_button.IsAlias;
        BitField = in_button.BitField;
        LinkCollection = in_button.LinkCollection;
        LinkUsage = in_button.LinkUsage;
        LinkUsagePage = in_button.LinkUsagePage;
        IsRange = in_button.IsRange;
        IsStringRange = in_button.IsStringRange;
        IsDesignatorRange = in_button.IsDesignatorRange;
        IsAbsolute = in_button.IsAbsolute;
        ReportCount = in_button.ReportCount;

        Range.UsageMin = in_button.Range.UsageMin;
        Range.UsageMax = in_button.Range.UsageMax;
        Range.StringMin = in_button.Range.StringMin;
        Range.StringMax = in_button.Range.StringMax;
        Range.DesignatorMin = in_button.Range.DesignatorMin;
        Range.DesignatorMax = in_button.Range.DesignatorMax;
        Range.DataIndexMin = in_button.Range.DataIndexMin;
        Range.DataIndexMax = in_button.Range.DataIndexMax;
        
        NotRange.Usage = in_button.NotRange.Usage;
        NotRange.StringIndex = in_button.NotRange.StringIndex;
        NotRange.DesignatorIndex = in_button.NotRange.DesignatorIndex;
        NotRange.DataIndex = in_button.NotRange.DataIndex;
    }

    void hid_button::set_information_text()
    {
        std::wstring content{};

        content = L"page\t: ";
        content += locate::get_usages().page( UsagePage );

        if( IsRange )
        {
            for( uint button_usage = Range.UsageMin; button_usage <= Range.UsageMax; button_usage++ )
            {
                content += L"\nusages: ";
                content += locate::get_usages().usage( UsagePage , button_usage );
            }
        }
        else
        {
            content += L"\nusage\t: ";
            content += locate::get_usages().usage( UsagePage , NotRange.Usage );
        }

        content += L"\nreport id\t: ";
        content += std::to_wstring( ReportID );

        content += L"\nis alias\t: ";
        content += IsAlias ? L"true" : L"false";

        content += L"\nbit field\t: ";
        //content += std::to_wstring( BitField ); // ushort 16bits

        /*
        if( BitField and 0b1 ) content += L" constant "; // bit 0
        //else content += L" data ";

        if( BitField and 0b10 ) content += L" variable "; // bit 1
        //else content += L" array ";

        if( BitField and 0b100 ) content += L" relative ";// bit 2
        //else content += L" absolute ";

        if( BitField and 0b1000 ) content += L" wrap ";// bit 3
        //else content += L" no wrap ";

        if( BitField and 0b10000 ) content += L" nonlinear ";// bit 4
        //else content += L" linear ";

        if( BitField and 0b100000 ) content += L" no preferred state ";// bit 5
        //else content += L" preferred ";

        if( BitField and 0b1000000 ) content += L" volatile ";// bit 6
        //else content += L" non-volatile ";

        //if( BitField and 0b10000000 ) content += L" reserved ";// bit 7
        //else content += L" reserved ";

        if( BitField and 0b100000000 ) content += L" buffered bytes ";// bit 8
        //else content += L" bit field ";
        */
        //content += L"\nis range\t: ";
        //content += IsRange ? L"true" : L"false";

        content += L"\nis alias\t: ";
        content += IsAlias ? L"true" : L"false";

        //content += L"\nis string range\t: ";
        //content += IsStringRange ? L"true" : L"false";

        //content += L"\nis designator range \t: ";
        //content += IsDesignatorRange ? L"true" : L"false";

        content += L"\nis absolute: ";
        content += IsAbsolute ? L"true" : L"false";

        information.set_content( content );
        information.set_font_size( 10.0f );
        information.set_font_colour( D2D1::ColorF::Yellow );
        information.set_layout_size( { 200.0f, 200.0f } );
    };
}