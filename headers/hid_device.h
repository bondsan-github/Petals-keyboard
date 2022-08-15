#pragma once

#include "..\headers\direct_2d.h"

#include "..\headers\hid_collection.h"
#include "..\headers\hid_local_item.h"
#include "..\headers\hid_raw_device.h"

#include "..\headers\text_d2d.h"
#include "..\headers\grid_d2d.h"

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
            
            bool                    draw_information  { true              };
            wstring                 text_font         { L"Cascasia code"  }; // { L"Sitka" };
            float                   text_size         { 15.0f             };
            colours                 text_colour       { colours::White    };
            dimensions              text_boundry      { 500.0f , 500.0f   };
            float                   rectangle_margin  { 0.0f };
            float                   rectangle_width   { 1.0f              };
            colours                 rectangle_colour  { colours::DarkCyan };

            vertex const            spacer            { 15.0f, 80.0f      };
            
            uint                    index             {};
            vector< line_d2d >      lines             {};

        private:

            void gather_information          ();
            void initialise_text_collections ();
            void initialise_text_device      ();
            void initialise_text_input       ();

        public:

                 hid_device( HANDLE in_device );
            void display_information();
            void texts_items_input();
            void draw();
    };
}