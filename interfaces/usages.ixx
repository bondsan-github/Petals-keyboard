module;

export module usages_text_module;

import std.core;

import globals;

namespace hid
{
   using namespace std;

   export class usages_text// usages ( unnamed )
   {
      public:

         wstring page( uint in_page ) const
         {
            try
            {
               return pages.at( in_page );
            }
            catch( out_of_range const & exception )
            {
               //string exception_text(exception.what() );
               //return wstring( to_wstring( in_page ) );
               return format( L"{:x} page" , in_page );//, static_cast<const char *>( exception.what() ) ); // hex string
            }
         };

         wstring usage( uint in_page , uint in_usage ) const
         {
            try
            {
               pages.at( in_page );
            }
            catch( out_of_range const & exception ) //out_of_range & error 
            {
               return format( L"{:x} usage" , in_usage ); // hex string               
            }

            try
            {
               return usages.at( in_page ).at( in_usage ).first;
            }
            catch( out_of_range const & exception )
            {
               return format( L"{:x} usage" , in_usage ); // hex string
            }
         }

         wstring type( uint in_page , int in_usage ) const
         {
            try
            {
               pages.at( in_page );
            }
            catch( out_of_range const & exception ) //out_of_range & error 
            {
               return format( L"{:x} usage" , in_usage ); // hex string               
            }

            try
            {
               return usages.at( in_page ).at( in_usage ).second;
            }
            catch( out_of_range const & exception )
            {
               return format( L"{:x} usage" , in_usage ); // hex string
            }
         }

      private: // variables

         //stringstream stream;

         vector< wstring > pages // up to 0xFFFF
         {
            L"undefined" ,               // 0x00
            L"generic desktop" ,         // 0x01
            L"simulation controls" ,     // 0x02
            L"vr controls" ,             // 0x03
            L"sport controls" ,          // 0x04
            L"game controls" ,           // 0x05
            L"generic device controls" , // 0x06
            L"keyboard/keypad" ,         // 0x07
            L"LED" ,                     // 0x08
            L"buton" ,                   // 0x09
            L"ordinal" ,                 // 0x0A
            L"telephony" ,               // 0x0B
            L"consumer" ,                // 0x0C
            L"digitisers" ,              // 0x0D ( aka digitizers ) i'm from england! :)
            L"haptics" ,                 // 0x0E
            L"physical input device" ,   // 0X0F
            // [ 0x0091 ] = L"arcade" ,  // c++20 array initialiser designator
            // [ 0x0092 ] = L"gaming device" ,
            // [ 0xFFF3 ] = L"microsoft bluetooth handsfree" , 
         };

         // hid 3.4.1
         enum class modifier_type
         { 
            undefined ,
            reserved ,
            linear_direct , // 
            linear_signed ,
            linear_distance ,
            on_off_signed,
            on_off_off,    // momentary
            on_off_static, // one shot
            named_array , 
            collection_physical ,
            collection_application ,
         };

         using _usage      = wstring;
         using _modifier   = wstring;

         using _pair       = pair< _usage , _modifier >;
         using usage_text  = vector< vector < _pair > >;

         const usage_text usages
         {
            {  // page 0x00 undefined 
               make_pair( L"undefined" , L"undefined" )
            } ,

            {  // page 0x01 generic desktop
               make_pair( L"undefined"                     , L"undefined" ) ,
               make_pair( L"pointer"                       , L"collection physical" ) ,
               make_pair( L"mouse"                         , L"collection application" ) ,
               make_pair( L"reserved"                      , L"reserved" ) ,
               make_pair( L"joystick"                      , L"collection application" ) ,
               make_pair( L"gamepad"                       , L"collection application" ) ,
               make_pair( L"keyboard"                      , L"collection application" ) ,
               make_pair( L"keypad"                        , L"collection application" ) ,
               make_pair( L"multi-axis controller"         , L"collection application" ) ,
               make_pair( L"tablet pc system"              , L"collection application" ) ,
               make_pair( L"water cooling device"          , L"collection application" ) ,
               make_pair( L"computer chassis device"       , L"collection application" ) ,
               make_pair( L"wireless radio controls"       , L"collection application" ) ,
               make_pair( L"portable device control"       , L"collection application" ) ,
               make_pair( L"system multi-axis controller"  , L"collection application" ) ,
               make_pair( L"spatial controller"            , L"collection application" ) ,
               make_pair( L"assistive control"             , L"collection application" ) ,
               make_pair( L"device dock"                   , L"collection application" ) ,
               make_pair( L"dockable device"               , L"collection application" ) ,
               make_pair( L"call state management control" , L"collection application" ) ,

                  // 0x1F to 0x2F
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,
               make_pair( L"reserved" , L"reserved" ) ,

                  // 0x30
               make_pair( L"x"              , L"dynamic value" ) ,
               make_pair( L"y"              , L"dynamic value" ) ,
               make_pair( L"z"              , L"dynamic value" ) ,
               make_pair( L"rx"             , L"dynamic value" ) ,
               make_pair( L"ry"             , L"dynamic value" ) ,
               make_pair( L"rz"             , L"dynamic value" ) ,
               make_pair( L"slider"         , L"dynamic value" ) ,
               make_pair( L"dial"           , L"dynamic value" ) ,
               make_pair( L"wheel"          , L"dynamic value" ) ,
               make_pair( L"hat switch"     , L"dynamic value" ) ,
               make_pair( L"counted buffer" , L"collection logical" ) ,
               make_pair( L"byte count"     , L"dynamic value" ) ,
               make_pair( L"motion wakeup"  , L"one shot control / dynamic flag" ) ,
               make_pair( L"start"          , L"on/off control" ) ,
               make_pair( L"select"         , L"on/off control" ) ,
               make_pair( L"reserved"       , L"reserved" ) ,
               make_pair( L"vx"             , L"dynamic value" ) ,
               make_pair( L"vy"             , L"dynamic value" ) ,
               make_pair( L"vz"             , L"dynamic value" ) ,
               make_pair( L"vbr"            , L"dynamic value" ) ,
               make_pair( L"vbry"           , L"dynamic value" ) ,
               make_pair( L"vbrz"           , L"dynamic value" ) ,
               make_pair( L"vno"            , L"dynamic value" ) ,
               make_pair( L"feature notification"  , L"dynamic value / dynamic flag" ) ,
               make_pair( L"resolution multiplier" , L"dynamic value" ) ,
               make_pair( L"qx"             , L"dynamic value" ) ,
               make_pair( L"qy"             , L"dynamic value" ) ,
               make_pair( L"qz"             , L"dynamic value" ) ,
               make_pair( L"qw"             , L"dynamic value" ) ,
               // ... to 0xffff
            } ,
            {  // page 0x02 
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x03 
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x04
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x05
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x06
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x07
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x08
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x09 button 

               // Buttons can be defined as;
               //   + Selector ( defined by a main item with it's array flag as true )
               //      -  only one in a set ( exclusive or XOR )
               //      -  n selections of a set ( n is from a main item report count ( ? collection ) ) 
               //      -  any selection of a set ( variable flag true and report size is one , amount of selections from main report count )
               //   + On / Off    
               //      - Two buttons, On and Off
               //   + Momentary   
               //   + One - Shot  
               // depending on the context of their declaration.

               make_pair( L"no button pressed" , L"" ) ,
               make_pair( L"button 1"  , L"" ) ,
               make_pair( L"button 2"  , L"" ) ,
               make_pair( L"button 3"  , L"" ) ,
               make_pair( L"button 4"  , L"" ) ,
               make_pair( L"button 5"  , L"" ) ,
               make_pair( L"button 6"  , L"" ) ,
               make_pair( L"button 7"  , L"" ) ,
               make_pair( L"button 8"  , L"" ) ,
               make_pair( L"button 9"  , L"" ) ,
               make_pair( L"button 10" , L"" ) ,
               make_pair( L"button 11" , L"" ) ,
               make_pair( L"button 12" , L"" ) ,
               make_pair( L"button 13" , L"" ) ,
               make_pair( L"button 14" , L"" ) ,
            } ,
            {  // page 0x0A
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x0B
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x0C
               make_pair( L"" , L"" ) ,
            } ,
            {  // page 0x0D digitisers
               make_pair( L"undefined"                     , L"collection application" ) , // 0x00
               make_pair( L"digitizer"                     , L"collection application" ) , // 0x01
               make_pair( L"pen"                           , L"collection application" ) , // 0x02
               make_pair( L"light pen"                     , L"collection application" ) , // 0x03
               make_pair( L"touch screen"                  , L"collection application" ) , // 0x04
               make_pair( L"touch pad"                     , L"collection application" ) , // 0x05
               make_pair( L"whiteboard"                    , L"collection application" ) , // 0x6
               make_pair( L"coordinate measuring machine"  , L"collection application" ) , // 0x7
               make_pair( L"3d digitizer"                  , L"collection application" ) , // 0x8
               make_pair( L"stereo plotter"                , L"collection application" ) , // 0x9
               make_pair( L"articulated arm"               , L"collection application" ) , // 0xA
               make_pair( L"armature"                      , L"collection application" ) , // 0xB
               make_pair( L"multiple point digitizer"      , L"collection application" ) , // 0xC
               make_pair( L"free space wand"               , L"collection application" ) , // 0xD
               make_pair( L"device configuration"          , L"collection application" ) , // 0xE
               make_pair( L"capacitive heat map digitizer" , L"collection application" ) , // 0xF
               make_pair( L"reserved" , L"reserved" ) , // 0x10
               make_pair( L"reserved" , L"reserved" ) , // 0x11
               make_pair( L"reserved" , L"reserved" ) , // 0x12
               make_pair( L"reserved" , L"reserved" ) , // 0x13
               make_pair( L"reserved" , L"reserved" ) , // 0x14
               make_pair( L"reserved" , L"reserved" ) , // 0x15
               make_pair( L"reserved" , L"reserved" ) , // 0x16
               make_pair( L"reserved" , L"reserved" ) , // 0x17
               make_pair( L"reserved" , L"reserved" ) , // 0x18
               make_pair( L"reserved" , L"reserved" ) , // 0x19
               make_pair( L"reserved" , L"reserved" ) , // 0x1A
               make_pair( L"reserved" , L"reserved" ) , // 0x1B
               make_pair( L"reserved" , L"reserved" ) , // 0x1C
               make_pair( L"reserved" , L"reserved" ) , // 0x1D
               make_pair( L"reserved" , L"reserved" ) , // 0x1E
               make_pair( L"reserved" , L"reserved" ) , // 0x1F
               make_pair( L"stylus"            , L"collection application | collection logical" ) , // 0x20 // ? no controls = ca , additional controls = L"collection logical" ) , ?
               make_pair( L"puck"              , L"collection logical" ) , // 0x21
               make_pair( L"finger"            , L"collection logical" ) , // 0x22
               make_pair( L"device settings"   , L"collection logical" ) , // 0x23
               make_pair( L"character gesture" , L"collection logical" ) , // 0x24
               make_pair( L"reserved" , L"reserved" ) , // 0x25
               make_pair( L"reserved" , L"reserved" ) , // 0x26
               make_pair( L"reserved" , L"reserved" ) , // 0x27
               make_pair( L"reserved" , L"reserved" ) , // 0x28
               make_pair( L"reserved" , L"reserved" ) , // 0x29
               make_pair( L"reserved" , L"reserved" ) , // 0x2A
               make_pair( L"reserved" , L"reserved" ) , // 0x2B
               make_pair( L"reserved" , L"reserved" ) , // 0x2C
               make_pair( L"reserved" , L"reserved" ) , // 0x2D
               make_pair( L"reserved" , L"reserved" ) , // 0x2E
               make_pair( L"reserved" , L"reserved" ) , // 0x2F
               make_pair( L"tip pressure"         , L"dynamic value" ) ,        // 0x30
               make_pair( L"barrel pressure"      , L"dynamic value" ) ,        // 0x31
               make_pair( L"in range"             , L"momentary collection" ) , // 0x32
               make_pair( L"touch"                , L"momentary collection" ) , // 0x33
               make_pair( L"untouch"              , L"one shot control" ) ,     // 0x34
               make_pair( L"tap"                  , L"one shot control" ) ,     // 0x35
               make_pair( L"quality"              , L"dynamic value" ) ,        // 0x36
               make_pair( L"data valid"           , L"momentary collection" ) , // 0x37
               make_pair( L"transducer index"     , L"dynamic value" ) ,        // 0x
               make_pair( L"tablet function keys" , L"collection logical" ) ,   // 0x
               make_pair( L"program change keys"  , L"collection logical" ) ,   // 0x
               make_pair( L"battery strength"     , L"dynamic value" ) ,// 0x
               make_pair( L"invert" , L"momentary collection" ) , // 0x
               make_pair( L"x tilt" , L"dynamic value" ) , // 0x
               make_pair( L"y tilt" , L"dynamic value" ) , // 0x
               make_pair( L"azimuth" , L"dynamic value" ) ,  // 0x
               make_pair( L"altitude" , L"dynamic value" ) , // 0x
               make_pair( L"twist" , L"dynamic value" ) , // 0x
               make_pair( L"tip switch" , L"momentary collection" ) ,  // 0x
               make_pair( L"secondary tip switch" , L"momentary collection" ) ,  // 0x
               make_pair( L"barrel switch" , L"momentary collection" ) ,  // 0x
               make_pair( L"eraser" , L"momentary collection" ) ,  // 0x
               make_pair( L"tablet pick" , L"momentary collection" ) ,  // 0x
               make_pair( L"touch valid" , L"momentary collection" ) ,  // 0x
               make_pair( L"width" , L"dynamic value" ) , // 0x
               make_pair( L"height" , L"dynamic value" ) , // 0x
               make_pair( L"reserved" , L"reserved" ) , // 0x4A
               make_pair( L"reserved" , L"reserved" ) , // 0x4B
               make_pair( L"reserved" , L"reserved" ) , // 0x4C
               make_pair( L"reserved" , L"reserved" ) , // 0x4D
               make_pair( L"reserved" , L"reserved" ) , // 0x4E
               make_pair( L"reserved" , L"reserved" ) , // 0x4F
               make_pair( L"reserved" , L"reserved" ) , // 0x50
               make_pair( L"contact identifier" , L"dynamic value" ) , // 0x
               make_pair( L"device mode" , L"dynamic value" ) , // 0x
               make_pair( L"device identifier" , L"dynamic value or static value" ) , // 0x
               make_pair( L"contact count" , L"dynamic value" ) , // 0x
               make_pair( L"contact count maximum" , L"static value" ) , // 0x
               make_pair( L"scan time" , L"dynamic value" ) , // 0x
               make_pair( L"surface switch" , L"dynamic flag" ) , // 0x
               make_pair( L"button switch" , L"dynamic flag" ) , // 0x
               make_pair( L"pad type" , L"static flag" ) , // 0x
               make_pair( L"secondary barrel switch" , L"momentary collection" ) ,  // 0x
               make_pair( L"transducer serial number" , L"static value" ) , // 0x
               make_pair( L"preferred color" , L"dynamic value" ) , // 0x
               make_pair( L"preferred color is locked" , L"momentary collection" ) ,  // 0x
               make_pair( L"preferred line width" , L"dynamic value" ) , // 0x
               make_pair( L"preferred line width is locked" , L"momentary collection" ) ,  // 0x
               make_pair( L"latency mode" , L"dynamic flag" ) , // 0x
               make_pair( L"gesture character quality" , L"dynamic value" ) , // 0x
               make_pair( L"character gesture data length" , L"dynamic value" ) , // 0x
               make_pair( L"character gesture data" , L"dynamic value" ) , // 0x
               make_pair( L"gesture character encoding" , L"named array" ) , // 0x
               make_pair( L"utf8 character gesture encoding" , L"selector" ) , // 0x
               make_pair( L"utf16 little endian character gesture encoding" , L"selector" ) , // 0x
               make_pair( L"utf16 big endian character gesture encoding" , L"selector" ) ,    // 0x
               make_pair( L"utf32 little endian character gesture encoding" , L"selector" ) , // 0x
               make_pair( L"utf32 big endian character gesture encoding" , L"selector" ) , // 0x
               make_pair( L"capacitive heat map protocol vendor id" , L"static value" ) , // 0x
               make_pair( L"capacitive heat map protocol version" , L"static value" ) , // 0x
               make_pair( L"capacitive heat map frame data" , L"dynamic value" ) , // 0x
               make_pair( L"gesture character enable" , L"dynamic flag" ) , // 0x
               make_pair( L"transducer serial number part 2" , L"static value" ) ,                // 0x
               make_pair( L"no preferred color" , L"static value" ) ,                            // 0x
               make_pair( L"preferred line style" , L"dynamic flag" ) ,                          // 0x
               make_pair( L"preferred line style is locked" , L"momentary collection" ) ,                  // 0x
               make_pair( L"ink" , L"selector" ) ,                                            // 0x
               make_pair( L"pencil" , L"selector" ) ,                                         // 0x
               make_pair( L"highlighter" , L"selector" ) ,                                   // 0x
               make_pair( L"highlighter" , L"selector" ) ,                                   // 0x
               make_pair( L"highlighter" , L"selector" ) ,                                   // 0x
               make_pair( L"chisel marker" , L"selector" ) ,                                  // 0x
               make_pair( L"brush" , L"selector" ) ,                                         // 0x
               make_pair( L"no preference" , L"selector" ) ,                                 // 0x
               make_pair( L"reserved" , L"reserved" ) , // 0x78
               make_pair( L"reserved" , L"reserved" ) , // 0x79
               make_pair( L"reserved" , L"reserved" ) , // 0x7A
               make_pair( L"reserved" , L"reserved" ) , // 0x7B
               make_pair( L"reserved" , L"reserved" ) , // 0x7C
               make_pair( L"reserved" , L"reserved" ) , // 0x7D
               make_pair( L"reserved" , L"reserved" ) , // 0x7E
               make_pair( L"reserved" , L"reserved" ) , // 0x7F
               make_pair( L"digitizer diagnostic" , L"collection logical" ) , // 0x80
               make_pair( L"digitizer error" , L"named array" ) , // 0x81
               make_pair( L"err normal status" , L"selector" ) , // 0x82
               make_pair( L"err transducers exceeded" , L"selector" ) ,                       // 0x83
               make_pair( L"err full trans features unavailable" , L"selector" ) ,           // 0x84
               make_pair( L"err charge low" , L"selector" ) ,                                // 0x85
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x86
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x87
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x88
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x89
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8A
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8B
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8C
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8D
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8E
               make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8F
               make_pair( L"transducer software info" , L"collection logical" ) ,                      // 0x90
               make_pair( L"transducer vendor id" , L"static value" ) ,                          // 0x91
               make_pair( L"transducer product id" , L"static value" ) ,                         // 0x92
               make_pair( L"device supported protocols" , L"named array or collection logical" ) ,                     // 0x93
               make_pair( L"transducer supported protocols" , L"named array or collection logical" ) ,                // 0x94
               make_pair( L"no protocol" , L"selector" ) ,                                    // 0x95
               make_pair( L"wacom aes protocol" , L"selector" ) ,                             // 0x96
               make_pair( L"usi protocol" , L"selector" ) ,                                  // 0x97
               make_pair( L"microsoft pen protocol" , L"selector" ) ,                        // 0x98
               make_pair( L"reserved" , L"reserved" ) , // 0x99
               make_pair( L"reserved" , L"reserved" ) , // 0x9A
               make_pair( L"reserved" , L"reserved" ) , // 0x9B
               make_pair( L"reserved" , L"reserved" ) , // 0x9C
               make_pair( L"reserved" , L"reserved" ) , // 0x9D
               make_pair( L"reserved" , L"reserved" ) , // 0x9E
               make_pair( L"reserved" , L"reserved" ) , // 0x9F
               make_pair( L"supported report rates" , L"static value or collection logical" ) ,                        // 0xA0
               make_pair( L"report rate" , L"dynamic value" ) ,                                    // 0xA1
               make_pair( L"transducer connected" , L"static flag" ) ,                           // 0xA2
               make_pair( L"switch disabled" , L"selector" ) ,                               // 0xA3
               make_pair( L"switch unimplemented" , L"selector" ) ,                          // 0xA4
               make_pair( L"transducer switches" , L"selector" ) ,                           // 0xA5
               make_pair( L"reserved" , L"reserved" ) , // 0xA6 
               // to 0xFFFF                    // 0xA6 to 0xFFFF
            } ,
            {  // page 0x0E haptics
               make_pair( L"" , L"" ) ,
            } ,

         }; // string usages

   } usages ;// class usages;

} // namespace hid
