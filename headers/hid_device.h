#pragma once

#include "..\headers\custom_types.h"

#include "..\headers\hid_globals.h"
#include "..\headers\hid_raw_device.h"

#include "..\headers\text_d2d.h"
//#include "..\headers\line_d2d.h"
#include "..\headers\hid_usages.h"

#include <string>

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

            // For USB devices, the maximum string length is 126 wide characters 
            // (not including the terminating NULL character).         
            //static const ushort string_size = 127u; 
            static const std::string::size_type string_size = 127u;
            wchar_t manufacturer_buffer[ string_size ] {};
            wchar_t product_buffer     [ string_size ] {};
            wchar_t physical_buffer    [ string_size ] {};

            std::wstring manufacturer {};
            std::wstring product      {};
            std::wstring physical     {};
            
            //std::vector< hid_collection > collection {};
            ulong collection_amount { 0 };
            std::vector< HIDP_LINK_COLLECTION_NODE > collection {};
            text information {};
            //vector< text > collection_texts {};
            
            //uint index {};
            //grid_d2d grid {};
            //std::vector< line_d2d > lines {};

            //using button_capabilities = HIDP_BUTTON_CAPS;
            //using value_item  = HIDP_VALUE_CAPS;

            std::vector< HIDP_BUTTON_CAPS > input_buttons;
            std::vector< HIDP_VALUE_CAPS >  input_values;

            std::vector< HIDP_BUTTON_CAPS > output_buttons;
            std::vector< HIDP_VALUE_CAPS >  output_values;

            std::vector< HIDP_BUTTON_CAPS > button_features;
            std::vector< HIDP_VALUE_CAPS >  value_features;

            bool draw_information{ true };

            std::wstring font_face         { L"Cascasia code" }; // { L"Sitka" };
            float        font_size         { 15.0f };
            D2D1::ColorF font_colour       { D2D1::ColorF::White };
            
            D2D1_SIZE_F  layout_size { 200.0f , 200.0f }; // layout size

            //float        rectangle_margin      { 0.0f };
            //float        rectangle_line_width  { 1.0f };
            //D2D1::ColorF rectangle_line_colour { D2D1::ColorF::DarkCyan };

            vertex       information_spacing     { 15.0f, 15.0f }; // spacers

        private:
            
            void set_text_device();
            void set_text_collections();
            void set_text_input();

            //HANDLE get_device_pointer() const { return device_pointer; }
            //ulong get_collection_amount() const { return collection_amount; }
            //PHIDP_PREPARSED_DATA get_data_preparsed() const { return data_preparsed; }

            //report get_input_report()   const { return input_report; }
            //report get_output_report()  const { return output_report; }
            //report get_feature_report() const { return feature_report; }

            //ushort get_page()  const { return page; }
            //ushort get_usage() const { return usage; }

            void reset();

        public:

            hid_device();
            hid_device( hid_raw_device & raw_device );
            ~hid_device();

            hid_device( const hid_device & in_copy );
            hid_device( hid_device && in_move ) noexcept;

            hid_device & operator = ( const hid_device & assign_copy );
            hid_device & operator = ( hid_device && assign_move ) noexcept;

            void collect_information();
            void set_if_display_information(const bool in_bool);
            void texts_items_input();
            void draw();
    };
}