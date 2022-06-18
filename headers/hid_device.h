#pragma once

#include "..\headers\hid_raw_device.h"

#include "..\headers\text_d2d.h"

namespace hid
{
    using namespace std;

    class hid_main_item;
    //class line_d2d;

    class hid_device : public hid_raw_device
    {
        private:

            hid_attributes            attributes       { .Size = sizeof( HIDD_ATTRIBUTES ) };
            hid_attributes_extended   attributes_extra {};

            // For USB devices, the maximum string length is 126 wide characters 
            // (not including the terminating NULL character).         
            static const int string_size  { 127 };
            wchar_t          manufacturer [ string_size ]{};
            wchar_t          product      [ string_size ]{};
            wchar_t          physical     [ string_size ]{};
            //wstring::size_type string_size  { 127 };
            //wstring            manufacturer ( string_size , ' ' );

            void gather_information();

             // data
             // concurrent points
             // x,y points x 5 + 3 buttons

            text                    text_device;
            vector< hid_main_item > items            {};
            //vector< line_d2d >      lines            {};
            bool                    draw_information { true };
            wstring                 text_font        { L"Cascasia code" }; // { L"Sitka" };
            float                   text_size        { 10.0f };
            colours                 text_colour      { colours::White };
            area                    text_area        {};
            float                   column           {};
            ushort                  column_amount    {};
            float                   row              {};
            ushort                  row_amount       {};
            uint                    index            {};

        public:

                 hid_device( HANDLE in_device );
            void texts_items_main();
            void display_information();
            void draw();
            void initialise_text_device();
            void texts_items_input();

    }; // class device

} // namespace hid