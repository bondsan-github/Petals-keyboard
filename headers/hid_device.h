#pragma once

#include "..\headers\custom_types.h"

#include "..\headers\hid_globals.h"
#include "..\headers\hid_raw_device.h"
#include "..\headers\hid_collection.h"
#include "..\headers\text_d2d.h"
//#include "..\headers\line_d2d.h"
#include "..\headers\circle_d2d.h"
#include "..\headers\contact.h"
#include "..\headers\hid_collections.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_button.h"   
#include "..\headers\hid_value.h"

#include <string>
#include <array>
//#include <unordered_map>
//#include <bitset>

/*
*  SHEN ZHEN HAI LUCK ELECTRONIC TECHNOLOGY CO., LTD
* 
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

            device_identity identity {};
            HANDLE       raw_handle  { nullptr };
            HANDLE       file_handle { nullptr };
            std::wstring path        { L"no device path" }; // or std::filesystem::wpath
            uint         path_char_amount { 0 };
            
            RID_DEVICE_INFO info { .cbSize = sizeof( RID_DEVICE_INFO ) };

            ushort page  { 0 };
            ushort usage { 0 };
            //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
            //hidp_status    status       { };

            std::vector< unsigned char > data_preparsed{};

            requests request;
            report   input_report , output_report , feature_report;

            hid_capabilities          capabilities {};
            hid_attributes            attributes {};
            hid_attributes_extended   attributes_extra {};

            static const uint string_size { 127u };

            wchar_t manufacturer_buffer [ string_size ] {};
            wchar_t product_buffer      [ string_size ] {};
            wchar_t physical_buffer     [ string_size ] {};

            std::wstring manufacturer {};
            std::wstring product      {};
            std::wstring physical     {};
            
            hid_collections collections;

            text_d2d     information      {};
            vertex       text_position    { 10.0f , 10.0f };
            D2D1_SIZE_F  text_layout_size { 300.0f , 80.0f }; // shrink to fit?
            float        text_font_size   { 10.0f };
            D2D1::ColorF text_font_colour { D2D1::ColorF::Yellow };
            
            text_d2d debug_text;
            //grid_d2d grid {};
            //std::vector< line_d2d > lines {};

            bool draw_information{ true };

            std::wstring font_face         { L"Cascasia code" }; // { L"Sitka" };
            float        font_size         { 15.0f };
            D2D1::ColorF font_colour       { D2D1::ColorF::Yellow };
            
            D2D1_SIZE_F  layout_size { 200.0f , 200.0f }; // layout size

            vertex       information_spacing { 15.0f, 15.0f }; // spacers

            //hid_value * value_contact_identifier { nullptr };
            //ulong contact_identifier {0};
            //hid_value * x { nullptr };

            const static uint contact_amount { 5 };

            std::array< contact , contact_amount > contacts;

            range       touchpad_resolution {};
            D2D1_SIZE_F screen_dpi {};
            D2D1_SIZE_F pad_to_screen_ratio {};

        private:
            
            void set_text_device();
            //void set_text_collections();

        public:

            //hid_device( const HANDLE & in_device );
            hid_device( HANDLE in_device );
            ~hid_device();

            bool            is_multi_touch();
            std::wstring    get_path();
            device_identity get_identity() const { return identity; }
            HANDLE          get_handle() const { return raw_handle; }
            page_and_usage  get_page_and_usage() { return { page , usage }; }
            bool            is_same_device( const device_identity in_identity ) const { return identity == in_identity; }
            unsigned char * get_data() { return data_preparsed.data(); }
            uint            get_input_report_size() { return capabilities.InputReportByteLength; }
            
            void  update( RAWINPUT * in_report );
            void  update_buffered( RAWINPUT ** in_rawinput_array , uint in_report_amount );
            void  update();

            void  collect_information();
            void  set_if_display_information( const bool in_bool );

            float get_text_top()    const { return information.get_top(); }
            float get_text_bottom() const { return information.get_bottom(); }
            float get_text_right()  const { return information.get_right(); }
            float get_text_left()   const { return information.get_left(); }

            long get_value_scaled( ushort in_page , ushort in_usage, RAWINPUT in_input );
            ulong get_value_unscaled( ushort in_page , ushort in_usage , RAWHID * in_input );

            void update_contact( ulong in_identifier , float in_x , float in_y );

            void draw();

            //void add_x( ) {}
            //void add_contact( uint in_identifier );
            //void add_contact(  ulong in_x , ulong in_y ) //uint in_id ,
            //void set_contact_identifier( hid_value * const in_value ) { value_contact_identifier = in_value; }
            //void set_x( hid_value * const in_value ) { //x = in_value; }

            /*
            void set_contact_amount_maximum( uint in_maximum )
            {
                // if in_maximum > 0;
                //contact_amount_maximum = in_maximum;
                contacts.resize( in_maximum );
            }
            */

            
    };
}