#pragma once

#include "..\headers\direct_2d.h"

#include "..\headers\hid_collection.h"
#include "..\headers\hid_local_item.h"
#include "..\headers\hid_raw_device.h"

#include "..\headers\text_d2d.h"
#include "..\headers\line_d2d.h"
#include "..\headers\hid_usages.h"
//#include "..\headers\grid_d2d.h"

#include < memory >

namespace hid
{
    class hid_device
    {
        private:

            PHIDP_PREPARSED_DATA data_preparsed { nullptr };

            HANDLE  device_pointer   { nullptr           };
            wstring device_path      { L"no device path" }; // or std::filesystem::wpath
            uint    path_char_amount { 0                 };

            ushort page{ 0 };
            ushort usage{ 0 };
            //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
            //hidp_status    status       { };

            requests request;
            report   input , output , feature;

            HIDP_CAPS capabilities {};

            ulong                collection_amount{ 0 };

            hid_attributes            attributes       { .Size = sizeof( HIDD_ATTRIBUTES ) };
            hid_attributes_extended   attributes_extra {};

            // For USB devices, the maximum string length is 126 wide characters 
            // (not including the terminating NULL character).         
            static const int          string_size  { 127 };
            wchar_t                   manufacturer [ string_size ]{};
            wchar_t                   product      [ string_size ]{};
            wchar_t                   physical     [ string_size ]{};
            //wstring::size_type      string_size  { 127 };
            //wstring                 manufacturer ( string_size , ' ' );
           
             // data
             // concurrent points
             // x,y points x 5 + 3 buttons

            //grid_d2d                grid             {};
            
            vector< hid_collection > collection       {};
            text                     information      {};
            //vector< text >          collection_texts        {};
            
            bool                     draw_information  { true              };

            wstring                  font_face         { L"Cascasia code"  }; // { L"Sitka" };
            float                    font_size         { 15.0f             };
            colours                  font_colour       { colours::White    };
            dimensions               paragraph_boundry      { 500.0f , 500.0f   };

            float                    rectangle_margin  { 0.0f };
            float                    rectangle_line_width   { 1.0f              };
            colours                  rectangle_line_colour  { colours::DarkCyan };

            vertex                   paragraph_spacing { 15.0f, 15.0f };
            
            uint                     index             {};
            vector< line_d2d >       lines             {};

            using button_item = HIDP_BUTTON_CAPS;
            using value_item  = HIDP_VALUE_CAPS;

            vector< button_item > input_buttons{};
            vector< value_item >  input_values{};

            vector< button_item > output_buttons{};
            vector< value_item >  output_values{};

            vector< button_item > button_features{};
            vector< value_item >  value_features{};

        private:

            void collect_information();
            void set_text_device();
            void set_text_collections();
            void set_text_input();

            HANDLE get_device_pointer();
            ulong get_collection_amount();
            PHIDP_PREPARSED_DATA get_data_preparsed() { return data_preparsed; }

            report get_input()   { return input; }
            report get_output()  { return output; }
            report get_feature() { return feature; }

            ushort get_page()  { return page; }
            ushort get_usage() { return usage; }

        public:

            //hid_device( void );
            ~hid_device( void );

            hid_device( hid_raw_device raw_device );

            void display_information();
            void texts_items_input();
            void draw();
    };
}