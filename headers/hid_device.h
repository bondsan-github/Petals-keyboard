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
    class hid_device : public hid_raw_device
    {
        private:

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

            wstring                  text_font         { L"Cascasia code"  }; // { L"Sitka" };
            float                    text_size         { 15.0f             };
            colours                  text_colour       { colours::White    };
            dimensions               text_boundry      { 500.0f , 500.0f   };

            float                    rectangle_margin  { 0.0f };
            float                    rectangle_width   { 1.0f              };
            colours                  rectangle_colour  { colours::DarkCyan };

            vertex const             spacer            { 15.0f, 15.0f      };
            
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

            void collect_information      ();
            void set_text_device      ();
            void set_text_collections ();
            void set_text_input       ();

        public:

                 hid_device  ( const HANDLE in_device );
                 ~hid_device ( void );

                 hid_device( const hid_device & copy );
                 hid_device( const hid_device && move ) noexcept;

                 hid_device & operator = ( const hid_device & assignment );
                 hid_device & operator = ( const hid_device && assignment_move ) noexcept;

            void display_information ();
            void texts_items_input   ();
            void draw                ();
    };
}