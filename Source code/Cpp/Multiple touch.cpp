#include "Multiple touch.h"
#include <format>
using std::format;

namespace HID
{
    Multiple_touch::Multiple_touch( HINSTANCE instance, LPWSTR parameters, int show_flags )
    {
        //OutputDebugString(L"\n Multiple_touch::Multiple_touch()");
        //initialise( instance , parameters , show_flags );
        //initialise( Client_size::fullscreen );
     
        Application::initialise( { 600, 400 } );

        std::wstring message;

        if( input_devices.empty() ) message = L"\n No multiple touch devices found";
        else
        {
            for( auto & device : input_devices )
            {

                message += format( L"\nManufacturer: {}, 0x{:X}", device.manufacturer_, device.identity_.vendor );
                message += format( L"\nProduct: {}, 0x{:X}", device.product_, device.identity_.product );
                message += format( L"\n Page: {}, 0x{:x}", page( device.capabilities.UsagePage ), device.capabilities.UsagePage );
                message += format( L"\n Usage: {}, 0x{:x}", usage( device.capabilities.UsagePage , device.capabilities.Usage ), device.capabilities.Usage );
                message += format( L"\n  Input report size = {} bytes" , device.capabilities.InputReportByteLength );
                message += format( L"\n  Ouput report size = {} bytes" , device.capabilities.OutputReportByteLength );
                message += format( L"\n  Feature report size = {} bytes" , device.capabilities.FeatureReportByteLength );

                for( auto & collection : device.collections_ )
                {
                    message += L"\nCollection";
                    message += format( L"\n  Type: {}", type( collection.CollectionType ) );
                    message += format( L"\n  Page: {}, 0x{:X}", page( collection.LinkUsagePage ), collection.LinkUsagePage );
                    message += format( L"\n  Usage: {}, 0x{:X}", usage( collection.LinkUsagePage, collection.LinkUsage ), collection.LinkUsage );

                    if( !collection.input_buttons_.empty() )
                    {
                        message += L"\n\t Input buttons";

                        for( auto & input : collection.input_buttons_ )
                        {
                            //if( input.IsRange || input.IsStringRange || input.IsDesignatorRange )
                            message += format( L"\n\t\t Page: {}, 0x{:x}", page( input.UsagePage ), input.UsagePage );
                            message += format( L"\n\t\t Usage: {}, 0x{:x}", usage( input.UsagePage, input.NotRange.Usage ), input.NotRange.Usage );
                            message += format( L"\n\t\t Report ID: {}" , input.ReportID );
                            message += format( L"\n\t\t Report amount: {}" , input.ReportCount );
                            message += format( L"\n\t\t Data ID: {}" , input.NotRange.DataIndex );
                            message += L"\n\t\t ---";
                        }
                    }

                    if( !collection.input_values_.empty() )
                    {
                        message += L"\n\t Input values";

                        for( auto & input : collection.input_values_ )
                        {
                            //if( input.IsRange || input.IsStringRange || input.IsDesignatorRange )
                            message += format( L"\n\t\t Page: {}, 0x{:x}", page( input.UsagePage ), input.UsagePage );
                            message += format( L"\n\t\t Usage: {}, 0x{:x}", usage( input.UsagePage , input.NotRange.Usage ), input.NotRange.Usage );
                            message += format( L"\n\t\t\t Logical min: {}", input.LogicalMin );
                            message += format( L"\n\t\t\t Logical max: {}", input.LogicalMax );
                            message += format( L"\n\t\t\t Physical min: {}", input.PhysicalMin );
                            message += format( L"\n\t\t\t Physical max: {}", input.PhysicalMax );
                            message += format( L"\n\t\t\t Report ID: {}" , input.ReportID );
                            message += format( L"\n\t\t\t Report amount: {}" , input.ReportCount );
                            message += format( L"\n\t\t\t Data ID: {}" , input.NotRange.DataIndex );
                            message += format( L"\n\t\t\t Bit size: {}" , input.BitSize );
                       
                            // units
                            if( input.Units )
                            {
                                message += format( L"\n\t\t\t unit: {}" , input.Units );
                        
                                unsigned long mask = 0xF; // System
                                auto value = input.Units & mask;
                                //if( value ) message += format( L"\n\t\t\t System: {}", input.system.at( value ) );

                                mask = 0xF0; // Length
                                value = ( input.Units & mask ) >> 4;
                                if( value ) message += format( L"\n\t\t\t length: {}", input.length.at( value ) );

                                mask = 0xF00; // Mass
                                value = ( input.Units & mask ) >> 8;
                                if( value ) message += format( L"\n\t\t\t mass: {}" , input.mass.at( value ) );

                                mask = 0xF000; // Time
                                value = ( input.Units & mask ) >> 12;
                                if( value ) message += format( L"\n\t\t\t time: {}" , input.time.at( value ) );
                            }

                            if( input.UnitsExp )
                            {
                                message += format( L"\n\t\t\t exponent: {}" , input.UnitsExp );
                            }
                        }
                    }

                    if( !collection.output_buttons_.empty() )
                    {
                        message += L"\n\t Output buttons";

                        for( auto & output : collection.output_buttons_ )
                        {
                            //if( output.IsRange || output.IsStringRange || output.IsDesignatorRange )
                            //message += format( L"\n\t\t Report ID: {}", output.ReportID );
                            message += format( L"\n\t\t Page: {}", page( output.UsagePage ) );
                            message += format( L"\n\t\t Usage: {}", usage( output.UsagePage , output.NotRange.Usage ) );
                            message += format( L"\n\t\t Report amount: {}" , output.ReportCount );
                            message += L"\n\t\t ---";
                        }
                    }

                    if( !collection.output_values_.empty() )
                    {
                        message += L"\n\t Output values";

                        for( auto & output : collection.output_values_ )
                        {
                            //if( output.IsRange || output.IsStringRange || output.IsDesignatorRange )
                            //message += format( L"\n\t\t Report ID: {}", output.ReportID );
                            message += format( L"\n\t\t Page: {}", page( output.UsagePage ) );
                            message += format( L"\n\t\t Usage: {}", usage( output.UsagePage , output.NotRange.Usage ) );
                            message += format( L"\n\t\t\t Logical min: {}", output.LogicalMin );
                            message += format( L"\n\t\t\t Logical max: {}", output.LogicalMax );
                            message += format( L"\n\t\t\t Physical min: {}", output.PhysicalMin );
                            message += format( L"\n\t\t\t Physical max: {}", output.PhysicalMax );
                            message += format( L"\n\t\t\t unit: {:x}" , output.Units );
                            message += format( L"\n\t\t\t Report amount: {}" , output.ReportCount );
                        
                        }
                    }

                    if( !collection.feature_buttons_.empty() )
                    {
                        message += L"\n\t Feature buttons";

                        for( auto & feature : collection.feature_buttons_ )
                        {
                            //if( feature.IsRange || feature.IsStringRange || feature.IsDesignatorRange )
                            message += format( L"\n\t\t Page: {}" , page( feature.UsagePage ) );
                            message += format( L"\n\t\t Usage: {}" , usage( feature.UsagePage , feature.NotRange.Usage ) );
                            message += format( L"\n\t Report ID: {}", feature.ReportID );
                            message += format( L"\n\t\t Report amount: {}" , feature.ReportCount );
                            message += L"\n\t\t ---";
                        }
                    }

                    if( !collection.feature_values_.empty() )
                    {
                        message += L"\n\t Feature values";

                        for( auto & feature : collection.feature_values_ )
                        {
                            //if( feature.IsRange || feature.IsStringRange || feature.IsDesignatorRange )
                            message += format( L"\n\t\t Page: {}", page( feature.UsagePage ) );
                            message += format( L"\n\t\t Usage: {}", usage( feature.UsagePage , feature.NotRange.Usage ) );
                            message += format( L"\n\t\t\t Logical min: {}", feature.LogicalMin );
                            message += format( L"\n\t\t\t Logical max: {}", feature.LogicalMax );
                            message += format( L"\n\t\t\t Physical min: {}", feature.PhysicalMin );
                            message += format( L"\n\t\t\t Physical max: {}", feature.PhysicalMax );
                            message += format( L"\n\t\t Report ID: {}" , feature.ReportID );
                            message += format( L"\n\t\t\t Report amount: {}" , feature.ReportCount );
                            // units
                        }
                    }
                }
            } // for each device

            // ** register and open device/s **
            for( auto & device : input_devices ) 
            {
                register_input_device( device.page() , device.usage() );
            }

        } // if no devices

        OutputDebugString( message.c_str() );
    }

    void Multiple_touch::update() 
    {
        Devices::update();
    }
    
    void Multiple_touch::render() {}

} // namespace hid

//https://learn.microsoft.com/en-us/windows/win32/sync/about-synchronization
//http://janaxelson.com/hidfaq.htm
//https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/using-winusb-api-to-communicate-with-a-usb-device
//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfileex

//https://www.edn.com/finger-navigation-in-hid/
// touchpad HID - mouse + keyboard
// one finger/point = context
// two finger = navigation - mouse window_ptr | context | direct touch 
// three = move window
// 
// five = keyboard
// ten finger 

/* references:
*    windows/driver samples/hid/hclient
*    www-user.tu-chemnitz.de/~heha/hsn/free.var , hidparse
*    stackoverflow.com
*    quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/
*    C++ How to program 10th edition , Deitel & Associates, Inc , ISBN-10: 0-13-444823-5 , ISBN-13: 978-0-13-444823-7
*/

// input_modifiers  ( buttons , values , features ) 
                  // output_modifiers
                  // 
                  // press over force threshold for capital letter
                  // delay after press for context 
                  // combined movement is mouse // 
                  // 
