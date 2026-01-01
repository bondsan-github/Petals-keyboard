#pragma once

#include <string>

enum class Keys
{
    none ,
    enter ,
    space ,
    escape ,
};

class Key
{
    public:

        Key( Keys enumeration , std::wstring const name )
            : enumeration( enumeration ) ,
            name( name )
        {}

        bool operator == ( Keys enumeration )
        {
            return this->enumeration == enumeration ? true : false;
        }

        Keys operator ()() // functional operator
        {
            return this->enumeration;
        }

    private:

        Keys         enumeration {};
        std::wstring name {};
};
