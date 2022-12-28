#pragma once

#include <vector>
#include <string>

namespace hid
{
    //using namespace std;

    using _usage      = std::wstring;
    using _modifier   = std::wstring;
    using _pair       = std::pair< _usage , _modifier >;
    using usage_text  = std::vector< std::vector < _pair > >;

    const usage_text usages
    {
       {  // page 0x00 undefined 
         std::make_pair( L"undefined" , L"undefined" )
       } ,

       {  // page 0x01 generic desktop
          std::make_pair( L"undefined"                     , L"undefined" ) ,
          std::make_pair( L"pointer"                       , L"collection physical" ) ,
          std::make_pair( L"mouse"                         , L"collection application" ) ,
          std::make_pair( L"reserved"                      , L"reserved" ) ,
          std::make_pair( L"joystick"                      , L"collection application" ) ,
          std::make_pair( L"gamepad"                       , L"collection application" ) ,
          std::make_pair( L"keyboard"                      , L"collection application" ) ,
          std::make_pair( L"keypad"                        , L"collection application" ) ,
          std::make_pair( L"multi-axis controller"         , L"collection application" ) ,
          std::make_pair( L"tablet pc system"              , L"collection application" ) ,
          std::make_pair( L"water cooling device"          , L"collection application" ) ,
          std::make_pair( L"computer chassis device"       , L"collection application" ) ,
          std::make_pair( L"wireless radio controls"       , L"collection application" ) ,
          std::make_pair( L"portable device control"       , L"collection application" ) ,
          std::make_pair( L"system multi-axis controller"  , L"collection application" ) ,
          std::make_pair( L"spatial controller"            , L"collection application" ) ,
          std::make_pair( L"assistive control"             , L"collection application" ) ,
          std::make_pair( L"device dock"                   , L"collection application" ) ,
          std::make_pair( L"dockable device"               , L"collection application" ) ,
          std::make_pair( L"call state management control" , L"collection application" ) ,

             // 0x1F to 0x2F
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,
          std::make_pair( L"reserved" , L"reserved" ) ,

             // 0x30
          std::make_pair( L"x"              , L"dynamic value" ) ,
          std::make_pair( L"y"              , L"dynamic value" ) ,
          std::make_pair( L"z"              , L"dynamic value" ) ,
          std::make_pair( L"rx"             , L"dynamic value" ) ,
          std::make_pair( L"ry"             , L"dynamic value" ) ,
          std::make_pair( L"rz"             , L"dynamic value" ) ,
          std::make_pair( L"slider"         , L"dynamic value" ) ,
          std::make_pair( L"dial"           , L"dynamic value" ) ,
          std::make_pair( L"wheel"          , L"dynamic value" ) ,
          std::make_pair( L"hat switch"     , L"dynamic value" ) ,
          std::make_pair( L"counted buffer" , L"collection logical" ) ,
          std::make_pair( L"byte count"     , L"dynamic value" ) ,
          std::make_pair( L"motion wakeup"  , L"one shot control / dynamic flag" ) ,
          std::make_pair( L"start"          , L"on/off control" ) ,
          std::make_pair( L"select"         , L"on/off control" ) ,
          std::make_pair( L"reserved"       , L"reserved" ) ,
          std::make_pair( L"vx"             , L"dynamic value" ) ,
          std::make_pair( L"vy"             , L"dynamic value" ) ,
          std::make_pair( L"vz"             , L"dynamic value" ) ,
          std::make_pair( L"vbr"            , L"dynamic value" ) ,
          std::make_pair( L"vbry"           , L"dynamic value" ) ,
          std::make_pair( L"vbrz"           , L"dynamic value" ) ,
          std::make_pair( L"vno"            , L"dynamic value" ) ,
          std::make_pair( L"feature notification"  , L"dynamic value / dynamic flag" ) ,
          std::make_pair( L"resolution multiplier" , L"dynamic value" ) ,
          std::make_pair( L"qx"             , L"dynamic value" ) ,
          std::make_pair( L"qy"             , L"dynamic value" ) ,
          std::make_pair( L"qz"             , L"dynamic value" ) ,
          std::make_pair( L"qw"             , L"dynamic value" ) ,
          // ... to 0xffff
       } ,
       {  // page 0x02 
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x03 
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x04
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x05
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x06
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x07
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x08
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x09 button 

          // Buttons can be defined as;
          //   + Selector ( defined by a main item with it's array flag as true )
          //      -  only one in a set ( exclusive or XOR )
          //      -  n selections of a set ( n is from a main item report count ( ? hid_collection ) ) 
          //      -  any selection of a set ( variable flag true and report size is one , amount of selections from main report count )
          //   + On / Off    
          //      - Two buttons, On and Off
          //   + Momentary   
          //   + One - Shot  
          // depending on the context of their declaration.

          std::make_pair( L"no button pressed" , L"" ) ,
          std::make_pair( L"button 1"  , L"" ) ,
          std::make_pair( L"button 2"  , L"" ) ,
          std::make_pair( L"button 3"  , L"" ) ,
          std::make_pair( L"button 4"  , L"" ) ,
          std::make_pair( L"button 5"  , L"" ) ,
          std::make_pair( L"button 6"  , L"" ) ,
          std::make_pair( L"button 7"  , L"" ) ,
          std::make_pair( L"button 8"  , L"" ) ,
          std::make_pair( L"button 9"  , L"" ) ,
          std::make_pair( L"button 10" , L"" ) ,
          std::make_pair( L"button 11" , L"" ) ,
          std::make_pair( L"button 12" , L"" ) ,
          std::make_pair( L"button 13" , L"" ) ,
          std::make_pair( L"button 14" , L"" ) ,
       } ,
       {  // page 0x0A
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x0B
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x0C
          std::make_pair( L"" , L"" ) ,
       } ,
       {  // page 0x0D digitisers
          std::make_pair( L"undefined"                     , L"collection application" ) , // 0x00
          std::make_pair( L"digitizer"                     , L"collection application" ) , // 0x01
          std::make_pair( L"pen"                           , L"collection application" ) , // 0x02
          std::make_pair( L"light pen"                     , L"collection application" ) , // 0x03
          std::make_pair( L"touch screen"                  , L"collection application" ) , // 0x04
          std::make_pair( L"touch pad"                     , L"collection application" ) , // 0x05
          std::make_pair( L"whiteboard"                    , L"collection application" ) , // 0x6
          std::make_pair( L"coordinate measuring machine"  , L"collection application" ) , // 0x7
          std::make_pair( L"3d digitizer"                  , L"collection application" ) , // 0x8
          std::make_pair( L"stereo plotter"                , L"collection application" ) , // 0x9
          std::make_pair( L"articulated arm"               , L"collection application" ) , // 0xA
          std::make_pair( L"armature"                      , L"collection application" ) , // 0xB
          std::make_pair( L"multiple point digitizer"      , L"collection application" ) , // 0xC
          std::make_pair( L"free space wand"               , L"collection application" ) , // 0xD
          std::make_pair( L"device configuration"          , L"collection application" ) , // 0xE
          std::make_pair( L"capacitive heat map digitizer" , L"collection application" ) , // 0xF
          std::make_pair( L"reserved" , L"reserved" ) , // 0x10
          std::make_pair( L"reserved" , L"reserved" ) , // 0x11
          std::make_pair( L"reserved" , L"reserved" ) , // 0x12
          std::make_pair( L"reserved" , L"reserved" ) , // 0x13
          std::make_pair( L"reserved" , L"reserved" ) , // 0x14
          std::make_pair( L"reserved" , L"reserved" ) , // 0x15
          std::make_pair( L"reserved" , L"reserved" ) , // 0x16
          std::make_pair( L"reserved" , L"reserved" ) , // 0x17
          std::make_pair( L"reserved" , L"reserved" ) , // 0x18
          std::make_pair( L"reserved" , L"reserved" ) , // 0x19
          std::make_pair( L"reserved" , L"reserved" ) , // 0x1A
          std::make_pair( L"reserved" , L"reserved" ) , // 0x1B
          std::make_pair( L"reserved" , L"reserved" ) , // 0x1C
          std::make_pair( L"reserved" , L"reserved" ) , // 0x1D
          std::make_pair( L"reserved" , L"reserved" ) , // 0x1E
          std::make_pair( L"reserved" , L"reserved" ) , // 0x1F
          std::make_pair( L"stylus"            , L"collection application | collection logical" ) , // 0x20 // ? no controls = ca , additional controls = L"hid_collection logical" ) , ?
          std::make_pair( L"puck"              , L"collection logical" ) , // 0x21
          std::make_pair( L"finger"            , L"collection logical" ) , // 0x22
          std::make_pair( L"device settings"   , L"collection logical" ) , // 0x23
          std::make_pair( L"character gesture" , L"collection logical" ) , // 0x24
          std::make_pair( L"reserved" , L"reserved" ) , // 0x25
          std::make_pair( L"reserved" , L"reserved" ) , // 0x26
          std::make_pair( L"reserved" , L"reserved" ) , // 0x27
          std::make_pair( L"reserved" , L"reserved" ) , // 0x28
          std::make_pair( L"reserved" , L"reserved" ) , // 0x29
          std::make_pair( L"reserved" , L"reserved" ) , // 0x2A
          std::make_pair( L"reserved" , L"reserved" ) , // 0x2B
          std::make_pair( L"reserved" , L"reserved" ) , // 0x2C
          std::make_pair( L"reserved" , L"reserved" ) , // 0x2D
          std::make_pair( L"reserved" , L"reserved" ) , // 0x2E
          std::make_pair( L"reserved" , L"reserved" ) , // 0x2F
          std::make_pair( L"tip pressure"         , L"dynamic value" ) ,        // 0x30
          std::make_pair( L"barrel pressure"      , L"dynamic value" ) ,        // 0x31
          std::make_pair( L"in range"             , L"momentary collection" ) , // 0x32
          std::make_pair( L"touch"                , L"momentary collection" ) , // 0x33
          std::make_pair( L"untouch"              , L"one shot control" ) ,     // 0x34
          std::make_pair( L"tap"                  , L"one shot control" ) ,     // 0x35
          std::make_pair( L"quality"              , L"dynamic value" ) ,        // 0x36
          std::make_pair( L"data valid"           , L"momentary collection" ) , // 0x37
          std::make_pair( L"transducer index"     , L"dynamic value" ) ,        // 0x
          std::make_pair( L"tablet function keys" , L"collection logical" ) ,   // 0x
          std::make_pair( L"program change keys"  , L"collection logical" ) ,   // 0x
          std::make_pair( L"battery strength"     , L"dynamic value" ) ,// 0x
          std::make_pair( L"invert" , L"momentary collection" ) , // 0x
          std::make_pair( L"x tilt" , L"dynamic value" ) , // 0x
          std::make_pair( L"y tilt" , L"dynamic value" ) , // 0x
          std::make_pair( L"azimuth" , L"dynamic value" ) ,  // 0x
          std::make_pair( L"altitude" , L"dynamic value" ) , // 0x
          std::make_pair( L"twist" , L"dynamic value" ) , // 0x
          std::make_pair( L"tip switch" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"secondary tip switch" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"barrel switch" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"eraser" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"tablet pick" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"touch valid" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"width" , L"dynamic value" ) , // 0x
          std::make_pair( L"height" , L"dynamic value" ) , // 0x
          std::make_pair( L"reserved" , L"reserved" ) , // 0x4A
          std::make_pair( L"reserved" , L"reserved" ) , // 0x4B
          std::make_pair( L"reserved" , L"reserved" ) , // 0x4C
          std::make_pair( L"reserved" , L"reserved" ) , // 0x4D
          std::make_pair( L"reserved" , L"reserved" ) , // 0x4E
          std::make_pair( L"reserved" , L"reserved" ) , // 0x4F
          std::make_pair( L"reserved" , L"reserved" ) , // 0x50
          std::make_pair( L"contact identifier" , L"dynamic value" ) , // 0x
          std::make_pair( L"device mode" , L"dynamic value" ) , // 0x
          std::make_pair( L"device identifier" , L"dynamic value or static value" ) , // 0x
          std::make_pair( L"contact count" , L"dynamic value" ) , // 0x
          std::make_pair( L"contact count maximum" , L"static value" ) , // 0x
          std::make_pair( L"scan time" , L"dynamic value" ) , // 0x
          std::make_pair( L"surface switch" , L"dynamic flag" ) , // 0x
          std::make_pair( L"button switch" , L"dynamic flag" ) , // 0x
          std::make_pair( L"pad type" , L"static flag" ) , // 0x
          std::make_pair( L"secondary barrel switch" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"transducer serial number" , L"static value" ) , // 0x
          std::make_pair( L"preferred color" , L"dynamic value" ) , // 0x
          std::make_pair( L"preferred color is locked" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"preferred line width" , L"dynamic value" ) , // 0x
          std::make_pair( L"preferred line width is locked" , L"momentary collection" ) ,  // 0x
          std::make_pair( L"latency mode" , L"dynamic flag" ) , // 0x
          std::make_pair( L"gesture character quality" , L"dynamic value" ) , // 0x
          std::make_pair( L"character gesture data length" , L"dynamic value" ) , // 0x
          std::make_pair( L"character gesture data" , L"dynamic value" ) , // 0x
          std::make_pair( L"gesture character encoding" , L"named array" ) , // 0x
          std::make_pair( L"utf8 character gesture encoding" , L"selector" ) , // 0x
          std::make_pair( L"utf16 little endian character gesture encoding" , L"selector" ) , // 0x
          std::make_pair( L"utf16 big endian character gesture encoding" , L"selector" ) ,    // 0x
          std::make_pair( L"utf32 little endian character gesture encoding" , L"selector" ) , // 0x
          std::make_pair( L"utf32 big endian character gesture encoding" , L"selector" ) , // 0x
          std::make_pair( L"capacitive heat map protocol vendor id" , L"static value" ) , // 0x
          std::make_pair( L"capacitive heat map protocol version" , L"static value" ) , // 0x
          std::make_pair( L"capacitive heat map frame data" , L"dynamic value" ) , // 0x
          std::make_pair( L"gesture character enable" , L"dynamic flag" ) , // 0x
          std::make_pair( L"transducer serial number part 2" , L"static value" ) ,                // 0x
          std::make_pair( L"no preferred color" , L"static value" ) ,                            // 0x
          std::make_pair( L"preferred line style" , L"dynamic flag" ) ,                          // 0x
          std::make_pair( L"preferred line style is locked" , L"momentary collection" ) ,                  // 0x
          std::make_pair( L"ink" , L"selector" ) ,                                            // 0x
          std::make_pair( L"pencil" , L"selector" ) ,                                         // 0x
          std::make_pair( L"highlighter" , L"selector" ) ,                                   // 0x
          std::make_pair( L"highlighter" , L"selector" ) ,                                   // 0x
          std::make_pair( L"highlighter" , L"selector" ) ,                                   // 0x
          std::make_pair( L"chisel marker" , L"selector" ) ,                                  // 0x
          std::make_pair( L"brush" , L"selector" ) ,                                         // 0x
          std::make_pair( L"no preference" , L"selector" ) ,                                 // 0x
          std::make_pair( L"reserved" , L"reserved" ) , // 0x78
          std::make_pair( L"reserved" , L"reserved" ) , // 0x79
          std::make_pair( L"reserved" , L"reserved" ) , // 0x7A
          std::make_pair( L"reserved" , L"reserved" ) , // 0x7B
          std::make_pair( L"reserved" , L"reserved" ) , // 0x7C
          std::make_pair( L"reserved" , L"reserved" ) , // 0x7D
          std::make_pair( L"reserved" , L"reserved" ) , // 0x7E
          std::make_pair( L"reserved" , L"reserved" ) , // 0x7F
          std::make_pair( L"digitizer diagnostic" , L"collection logical" ) , // 0x80
          std::make_pair( L"digitizer error" , L"named array" ) , // 0x81
          std::make_pair( L"err normal status" , L"selector" ) , // 0x82
          std::make_pair( L"err transducers exceeded" , L"selector" ) ,                       // 0x83
          std::make_pair( L"err full trans features unavailable" , L"selector" ) ,           // 0x84
          std::make_pair( L"err charge low" , L"selector" ) ,                                // 0x85
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x86
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x87
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x88
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x89
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8A
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8B
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8C
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8D
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8E
          std::make_pair( L"reserved" , L"reserved" ) ,                                       // 0x8F
          std::make_pair( L"transducer software info" , L"collection logical" ) ,                      // 0x90
          std::make_pair( L"transducer vendor id" , L"static value" ) ,                          // 0x91
          std::make_pair( L"transducer product id" , L"static value" ) ,                         // 0x92
          std::make_pair( L"device supported protocols" , L"named array or collection logical" ) ,                     // 0x93
          std::make_pair( L"transducer supported protocols" , L"named array or collection logical" ) ,                // 0x94
          std::make_pair( L"no protocol" , L"selector" ) ,                                    // 0x95
          std::make_pair( L"wacom aes protocol" , L"selector" ) ,                             // 0x96
          std::make_pair( L"usi protocol" , L"selector" ) ,                                  // 0x97
          std::make_pair( L"microsoft pen protocol" , L"selector" ) ,                        // 0x98
          std::make_pair( L"reserved" , L"reserved" ) , // 0x99
          std::make_pair( L"reserved" , L"reserved" ) , // 0x9A
          std::make_pair( L"reserved" , L"reserved" ) , // 0x9B
          std::make_pair( L"reserved" , L"reserved" ) , // 0x9C
          std::make_pair( L"reserved" , L"reserved" ) , // 0x9D
          std::make_pair( L"reserved" , L"reserved" ) , // 0x9E
          std::make_pair( L"reserved" , L"reserved" ) , // 0x9F
          std::make_pair( L"supported report rates" , L"static value or collection logical" ) ,                        // 0xA0
          std::make_pair( L"report rate" , L"dynamic value" ) ,                                    // 0xA1
          std::make_pair( L"transducer connected" , L"static flag" ) ,                           // 0xA2
          std::make_pair( L"switch disabled" , L"selector" ) ,                               // 0xA3
          std::make_pair( L"switch unimplemented" , L"selector" ) ,                          // 0xA4
          std::make_pair( L"transducer switches" , L"selector" ) ,                           // 0xA5
          std::make_pair( L"reserved" , L"reserved" ) , // 0xA6 
          // to 0xFFFF                    // 0xA6 to 0xFFFF
       } ,
       {  // page 0x0E haptics
          std::make_pair( L"" , L"" ) ,
       } ,

    }; // string usages

} // namespace hid
