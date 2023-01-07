#pragma once

#include "..\headers\custom_types.h"

#include "..\headers\hid_globals.h"
#include "..\headers\hid_raw_device.h"
#include "..\headers\hid_collection.h"
#include "..\headers\text_d2d.h"
//#include "..\headers\line_d2d.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_button.h"   
#include "..\headers\hid_value.h"

#include <string>
//#include <unordered_map>
//#include <bitset>

/*
HAILUCK CO.,LTD=0x258A
Usb Touch=0x2016
(model T063P)
06-01:06-Whiteboard-Keyboard/Keypad Page-e0 to e7-Keyboard 
10-01:02-Pen-Button-Button 1 to 5, values=y,x,Wheel  Consumer-AC Pan
11-d5:05-Touch Pad-Button caps=Tip Switch, Touch Valid, Button 1
                  -Value caps=Contact Identifier=3, Contact Count=7, x=950, y=620 , Scan Time=units-0x1001,exp=10^-4
13-0d:0e-Device Configuration-Button caps=finger-Button Switch-Surface Switch
                             -Value caps=Finger-Device Mode
14-01:0c-Wireless Radio Controls-Wireless Radio Button
17-FF00:01-Reserved-
21-0c:01-Consumer Control-(23 controls)-Volume Decrement, Volume Increment,
*/

//https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-architecture
//https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-over-usb

//https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/introduction-to-hid-concepts
//https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/obtaining-hid-reports#obtaining-hid-reports-by-user-mode-applications
//https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/interpreting-hid-reports

namespace hid
{
    class hid_device
    {
        private:

            std::vector< std::byte > data_preparsed {};

            HANDLE       device_pointer   { nullptr           };
            std::wstring device_path      { L"no device path" }; // or std::filesystem::wpath
            uint         path_char_amount { 0                 };

            ushort page  { 0 };
            ushort usage { 0 };
            //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
            //hidp_status    status       { };

            requests request;
            report   input_report , output_report , feature_report;

            hid_capabilities          capabilities {};
            hid_attributes            attributes {};
            hid_attributes_extended   attributes_extra {};

            static const std::string::size_type string_size = 127u;
            //static const std::wstring::size_type string_size = 127u; // todo: check if wstring size works
            wchar_t manufacturer_buffer[ string_size ] {};
            wchar_t product_buffer     [ string_size ] {};
            wchar_t physical_buffer    [ string_size ] {};

            std::wstring manufacturer {};
            std::wstring product      {};
            std::wstring physical     {};
            
            ulong collection_amount { 0 };
            std::vector< hid_collection > collections {};

            text         device_information      {};
            vertex       device_text_position    { 30.0f , 30.0f };
            D2D1_SIZE_F  device_text_layout_size { 300.0f , 80.0f }; // shrink to fit?
            float        device_text_font_size   { 15.0f };
            D2D1::ColorF device_text_font_colour { D2D1::ColorF::Yellow };
            
            float        collection_text_spacer       { 60.0f };

            void set_text_input_buttons();
            
            //grid_d2d grid {};
            //std::vector< line_d2d > lines {};

            std::vector< hid_button > input_buttons;
            std::vector< hid_value >  input_values;

            std::vector< hid_button > output_buttons;
            std::vector< hid_value >  output_values;

            std::vector< hid_button > button_features;
            std::vector< hid_value >  value_features;

            bool draw_information{ true };

            std::wstring font_face         { L"Cascasia code" }; // { L"Sitka" };
            float        font_size         { 15.0f };
            D2D1::ColorF font_colour       { D2D1::ColorF::Yellow };
            
            D2D1_SIZE_F  layout_size { 200.0f , 200.0f }; // layout size

            vertex       information_spacing     { 15.0f, 15.0f }; // spacers

            //using map_key = bitset<32>
            //using map_data = std::wstring
            //map 0x0  = 0b0
            //map 0x01 = 0b01
            //map 0x02 = 0b10
            /*std::unordered_map< std::bitset<32> , std::wstring> data_types
            {
                { {0b0} , L"Data" } , // bit 0 = Data |Constant
                { {0b1} , L"Constant" } ,
                { {0b00} , L"Array" } ,
                { {0b10} , L"Array" } ,
            };*/

        private:
            
            void set_text_device();
            void set_text_collections();
            void set_text_input();

            hid_collection & get_collection( const hid_button & in_button );
            std::vector<hid_collection>::const_iterator get_collection( const hid_value & in_value ) const;

            //HANDLE get_device_pointer() const { return device_pointer; }
            //PHIDP_PREPARSED_DATA get_data_preparsed() const { return data_preparsed; }

        public:

            hid_device( const hid_raw_device & raw_device );

            void collect_information();
            void set_if_display_information(const bool in_bool);
            void texts_items_input();
            void draw();
    };
}