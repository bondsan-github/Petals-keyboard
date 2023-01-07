#include "..\headers\hid_value.h"

namespace hid
{
    void hid_value::operator = ( const _HIDP_VALUE_CAPS & in_value )
    {
        UsagePage = in_value.UsagePage;
        ReportID = in_value.ReportID;
        IsAlias = in_value.IsAlias;
        BitField = in_value.BitField;
        LinkCollection = in_value.LinkCollection;
        LinkUsage = in_value.LinkUsage;
        LinkUsagePage = in_value.LinkUsagePage;
        IsRange = in_value.IsRange;
        IsStringRange = in_value.IsStringRange;
        IsDesignatorRange = in_value.IsDesignatorRange;
        IsAbsolute = in_value.IsAbsolute;
        HasNull = in_value.HasNull;
        BitSize = in_value.BitSize;
        ReportCount = in_value.ReportCount;
        UnitsExp = in_value.UnitsExp;
        Units = in_value.Units;
        LogicalMin = in_value.LogicalMin;
        LogicalMax = in_value.LogicalMax;
        PhysicalMin = in_value.PhysicalMin;
        PhysicalMax = in_value.PhysicalMax;

        Range.UsageMin = in_value.Range.UsageMin;
        Range.UsageMax = in_value.Range.UsageMax;
        Range.StringMin = in_value.Range.StringMin;
        Range.StringMax = in_value.Range.StringMax;
        Range.DesignatorMin = in_value.Range.DesignatorMin;
        Range.DesignatorMax = in_value.Range.DesignatorMax;
        Range.DataIndexMin = in_value.Range.DataIndexMin;
        Range.DataIndexMax = in_value.Range.DataIndexMax;

        NotRange.Usage = in_value.NotRange.Usage;
        NotRange.StringIndex = in_value.NotRange.StringIndex;
        NotRange.DesignatorIndex = in_value.NotRange.DesignatorIndex;
        NotRange.DataIndex = in_value.NotRange.DataIndex;
    }

    void hid_value::set_information_text()
    {
        //Resolution = ( Logical Maximum – Logical Minimum ) / ( ( Physical Maximum – Physical Minimum ) *
        //                                                      ( 10 Unit Exponent ) )
    }
}