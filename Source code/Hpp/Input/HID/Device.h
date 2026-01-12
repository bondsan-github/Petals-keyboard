#pragma once

#include "Aliases.h"

#include "Input\HID\Types.h"
#include "Input\HID\Collections.h"
#include "Input\HID\Usages.h"
#include "Input\HID\Button.h"   
#include "Input\HID\Value.h"

#include "Output\Logging.h"

//#include "Contact.h"

#include <string>
#include <array>

namespace HID
{
    class Device : public HID::Collections, public HID::Usages, public Logging
    {
        private:

            Identity     identity_    {};
            HANDLE       raw_handle   {};
            HANDLE       file_handle  {};
            std::wstring path_        { L"no device path" }; // or std::filesystem::wpath
            uint         path_char_amount {};
            
            RID_DEVICE_INFO rid_information { .cbSize = sizeof( RID_DEVICE_INFO ) };

            ushort page_  {};
            ushort usage_ {};
            //NTSTATUS       hid_result   { HIDP_STATUS_NULL };
            //hidp_status    status       { };

            std::vector< uchar > data_preparsed{};

            Requests request;
            Report   input_report, output_report, feature_report;

            HIDP_CAPS                  capabilities     {};
            HIDD_ATTRIBUTES            attributes       {};
            HIDP_EXTENDED_ATTRIBUTES   attributes_extra {};

            static const uint string_size { 500u };
            ulong input_buffer_amount {};

            wchar_t manufacturer_buffer [ string_size ] {};
            wchar_t product_buffer      [ string_size ] {};
            wchar_t physical_buffer     [ string_size ] {};

            std::wstring manufacturer_ {};
            std::wstring product_      {};
            std::wstring physical_     {};
            
            //hid_value * value_contact_identifier { nullptr };
            //ulong contact_identifier {0};
            //hid_value * x { nullptr };

            //const static uint contact_amount { 5 };

            //std::array< Contact , contact_amount > contacts;

            //Range       touchpad_resolution {};
            //D2D1_SIZE_F screen_dpi {};
            //D2D1_SIZE_F pad_to_screen_ratio {};

            void connect();

        public:

            friend class Multiple_touch;

            Device( HANDLE device );
            ~Device();

            bool            is_multi_touch();
            ushort          page()     { return page_; }
            ushort          usage()    { return usage_; }
            std::wstring    path();
            Identity        identity() { return identity_; }
            HANDLE          handle()   { return raw_handle; }

            bool manufacturer( long manufacturer );
            //std::wstring    manufacturer() { return manufacturer_; }
            //std::wstring    product()      { return product_; }

            std::vector< Collection > & collections() { return collections_; }

            bool            is_same_device( const Identity & identity ) { return identity_ == identity; }
            unsigned char * data()     { return data_preparsed.data(); }
            uint            input_report_size() { return capabilities.InputReportByteLength; }
            
            void collect_information();

            void  update( RAWINPUT input );
            //void  async_read();
            //void  update_buffered( RAWINPUT ** rawinput_array, uint report_amount );

            long  value_scaled(   ushort page, ushort usage, RAWINPUT input );
            ulong value_unscaled( ushort page, ushort usage, RAWHID * input );

            //void  update_contact( ulong identifier, float x, float y );
            // update()

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
