#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Usages.h"

#include <vector>
#include <string>

namespace HID
{
    class Value : public value_caps, public Usages
    {
        private:
            
            ulong        value_unsigned { 0ul }; // = 0xffff'ffff
            long         value_signed { -1 };

            std::vector< std::vector< std::wstring > > units
            {
                { L"None", L"SI Linear", L"SI Rotation", L"English Linear", L"English Rotation" },
                { L"None", L"", L"", L"", L"" },
                { L"None", L"", L"", L"", L"" },
                { L"None", L"", L"", L"", L"" },
                { L"None", L"", L"", L"", L"" },
                { L"None", L"", L"", L"", L"" },
                { L"None", L"", L"", L"", L"" }
            };

            // units & 0xF = System
            std::vector<std::wstring> system
            {
                L"None", L"SI Linear", L"SI Rotation", L"English Linear", L"English Rotation"
            };

            // units & 0xF0 = Length

            std::vector< std::wstring > length
            {
                L"None", L"Centimeter", L"Radians", L"Inch", L"Degrees"
            };

            // units & 0xF00 = Mass
            std::vector< std::wstring > mass
            {
                L"None", L"Gram", L"Gram", L"Slug", L"Slug"
            };

            // units & 0xF000 = Time
            std::vector< std::wstring > time
            {
                L"None", L"Seconds", L"Seconds", L"Seconds", L"Seconds"
            };

            std::vector< std::wstring > exponent
            {
                L"^0", // 0x0
                L"^1", // 0x1
                L"^2", // 0x2
                L"^3", // 0x3
                L"^4", // 0x4
                L"^5", // 0x5
                L"^6", // 0x6
                L"^7", // 0x7
                L"^-8", // 0x8
                L"^-7", // 0x9
                L"^-6", // 0xA
                L"^-5", // 0xB
                L"^-4", // 0xC
                L"^-3", // 0xD
                L"^-2", // 0xE
                L"^-1", // 0xF
            };

        public:

            friend class Multiple_touch;

            Value( value_caps & );

            void update( RAWINPUT * raw_data );

            long value() { return value_signed; }

            Value() = default;
    };
}