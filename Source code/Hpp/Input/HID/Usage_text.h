#pragma once

#include <vector>
#include <string>

namespace HID
{
    using usage_text = std::vector< std::vector< std::wstring > >;
    
    // map< page , vector<strings> >

    const usage_text usages
    {
       {  // page 0x00 undefined 
          L"undefined" 
       } ,

       {  // page 0x01 generic desktop
           L"undefined"                      ,// 0x00
           L"pointer"                        ,// 0x01
           L"mouse"                          ,// 0x02
           L"reserved"                       ,// 0x03
           L"joystick"                       ,// 0x04
           L"gamepad"                        ,// 0x05
           L"keyboard"                       ,// 0x06
           L"keypad"                         ,// 0x07
           L"multi-axis controller"          ,// 0x08
           L"tablet pc system"               ,// 0x09
           L"water cooling device"           ,// 0x0a
           L"computer chassis device"        ,// 0x0b
           L"wireless radio controls"        ,// 0x0c
           L"portable device control"        ,// 0x0d
           L"system multi-axis controller"   ,// 0x0e
           L"spatial controller"             ,// 0x0f
           L"assistive control"              ,// 0x10
           L"device dock"                    ,// 0x11
           L"dockable device"                ,// 0x12
           L"call state management control"  ,// 0x13

           // 0x14 to 0x2F
           L"reserved"  ,// 0x14
           L"reserved"  ,// 0x15
           L"reserved"  ,// 0x16
           L"reserved"  ,// 0x17
           L"reserved"  ,// 0x18
           L"reserved"  ,// 0x19
           L"reserved"  ,// 0x1a
           L"reserved"  ,// 0x1b
           L"reserved"  ,// 0x1c
           L"reserved"  ,// 0x1d
           L"reserved"  ,// 0x1e
           L"reserved"  ,// 0x1f
           L"reserved"  ,// 0x20
           L"reserved"  ,// 0x21
           L"reserved"  ,// 0x22
           L"reserved"  ,// 0x23
           L"reserved"  ,// 0x24
           L"reserved"  ,// 0x25
           L"reserved"  ,// 0x26
           L"reserved"  ,// 0x27
           L"reserved"  ,// 0x28
           L"reserved"  ,// 0x29
           L"reserved"  ,// 0x2a
           L"reserved"  ,// 0x2b
           L"reserved"  ,// 0x2c
           L"reserved"  ,// 0x2d
           L"reserved"  ,// 0x2e
           L"reserved"  ,// 0x2f

           // 0x30
           L"x"               ,// 0x30
           L"y"               ,// 0x
           L"z"               ,// 0x
           L"rx"              ,// 0x
           L"ry"              ,// 0x
           L"rz"              ,// 0x
           L"slider"          ,// 0x
           L"dial"            ,// 0x
           L"wheel"           ,// 0x
           L"hat switch"      ,// 0x
           L"counted buffer"  ,
           L"byte count"      ,
           L"motion wakeup"   ,
           L"start"           ,
           L"select"          ,
           L"reserved"        ,
           L"vx"              ,
           L"vy"              ,
           L"vz"              ,
           L"vbr"             ,
           L"vbry"            ,
           L"vbrz"            ,
           L"vno"             ,
           L"feature notification"   ,
           L"resolution multiplier"  ,
           L"qx"              ,
           L"qy"              ,
           L"qz"              ,
           L"qw"              ,
          // ... to 0xffff
       } ,

       {  // page 0x02 
       } ,

       {  // page 0x03 
       } ,

       {  // page 0x04
       } ,

       {  // page 0x05
       } ,

       {  // page 0x06
       } ,

       {  // page 0x07
       } ,

       {  // page 0x08
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

           L"no button pressed"  ,
           L"button 1"   ,
           L"button 2"   ,
           L"button 3"   ,
           L"button 4"   ,
           L"button 5"   ,
           L"button 6"   ,
           L"button 7"   ,
           L"button 8"   ,
           L"button 9"   ,
           L"button 10"  ,
           L"button 11"  ,
           L"button 12"  ,
           L"button 13"  ,
           L"button 14"  ,
       } ,

       {  // page 0x0A
       } ,

       {  // page 0x0B
       } ,

       {  // page 0x0C
       } ,

       {  // page 0x0D digitisers
           L"undefined"                      , // 0x00
           L"digitiser"                      , // 0x01
           L"pen"                            , // 0x02
           L"light pen"                      , // 0x03
           L"touch screen"                   , // 0x04
           L"touch pad"                      , // 0x05
           L"whiteboard"                     , // 0x6
           L"coordinate measuring machine"   , // 0x7
           L"3d digitizer"                   , // 0x8
           L"stereo plotter"                 , // 0x9
           L"articulated arm"                , // 0xA
           L"armature"                       , // 0xB
           L"multiple point digitiser"       , // 0xC
           L"free space wand"                , // 0xD
           L"device configuration"           , // 0xE
           L"capacitive heat map digitiser"  , // 0xF
           L"reserved"  , // 0x10
           L"reserved"  , // 0x11
           L"reserved"  , // 0x12
           L"reserved"  , // 0x13
           L"reserved"  , // 0x14
           L"reserved"  , // 0x15
           L"reserved"  , // 0x16
           L"reserved"  , // 0x17
           L"reserved"  , // 0x18
           L"reserved"  , // 0x19
           L"reserved"  , // 0x1A
           L"reserved"  , // 0x1B
           L"reserved"  , // 0x1C
           L"reserved"  , // 0x1D
           L"reserved"  , // 0x1E
           L"reserved"  , // 0x1F
           L"stylus"             , // 0x20 // ? no controls = ca , additional controls = L"hid_collection logical" ) , ?
           L"puck"               , // 0x21
           L"finger"             , // 0x22
           L"device settings"    , // 0x23
           L"character gesture"  , // 0x24
           L"reserved"  , // 0x25
           L"reserved"  , // 0x26
           L"reserved"  , // 0x27
           L"reserved"  , // 0x28
           L"reserved"  , // 0x29
           L"reserved"  , // 0x2A
           L"reserved"  , // 0x2B
           L"reserved"  , // 0x2C
           L"reserved"  , // 0x2D
           L"reserved"  , // 0x2E
           L"reserved"  , // 0x2F
           L"tip pressure"          ,        // 0x30
           L"barrel pressure"       ,        // 0x31
           L"in range"              , // 0x32
           L"touch"                 , // 0x33
           L"untouch"               ,     // 0x34
           L"tap"                   ,     // 0x35
           L"quality"               ,        // 0x36
           L"data valid"            , // 0x37
           L"transducer index"      ,        // 0x
           L"tablet function keys"  ,   // 0x
           L"program change keys"   ,   // 0x
           L"battery strength"      ,// 0x
           L"invert"  , // 0x
           L"x tilt"  , // 0x
           L"y tilt"  , // 0x
           L"azimuth"  ,  // 0x
           L"altitude"  , // 0x
           L"twist"  , // 0x
           L"tip switch"  ,  // 0x
           L"secondary tip switch"  ,  // 0x
           L"barrel switch"  ,  // 0x
           L"eraser"  ,  // 0x
           L"tablet pick"  ,  // 0x
           L"touch valid"  ,  // 0x
           L"width"  , // 0x
           L"height"  , // 0x
           L"reserved"  , // 0x4A
           L"reserved"  , // 0x4B
           L"reserved"  , // 0x4C
           L"reserved"  , // 0x4D
           L"reserved"  , // 0x4E
           L"reserved"  , // 0x4F
           L"reserved"  , // 0x50
           L"contact identifier"  , // 0x
           L"device mode"         , // 0x
           L"device identifier"   , // 0x
           L"contact count"       , // 0x
           L"contact count maximum"  , // 0x
           L"scan time"  , // 0x
           L"surface switch"  , // 0x
           L"button switch"  , // 0x
           L"pad type" , // 0x
           L"secondary barrel switch"  ,  // 0x
           L"transducer serial number"  , // 0x
           L"preferred color"  , // 0x
           L"preferred color is locked"  ,  // 0x
           L"preferred line width"  , // 0x
           L"preferred line width is locked"  ,  // 0x
           L"latency mode"  , // 0x
           L"gesture character quality"  , // 0x
           L"character gesture data length"  , // 0x
           L"character gesture data"  , // 0x
           L"gesture character encoding"  , // 0x
           L"utf8 character gesture encoding"  , // 0x
           L"utf16 little endian character gesture encoding"  , // 0x
           L"utf16 big endian character gesture encoding"  ,    // 0x
           L"utf32 little endian character gesture encoding"  , // 0x
           L"utf32 big endian character gesture encoding"  , // 0x
           L"capacitive heat map protocol vendor id"  , // 0x
           L"capacitive heat map protocol version"  , // 0x
           L"capacitive heat map frame data"  , // 0x
           L"gesture character enable"  , // 0x
           L"transducer serial number part 2"  ,                // 0x
           L"no preferred color"  ,                            // 0x
           L"preferred line style"  ,                          // 0x
           L"preferred line style is locked"  ,                  // 0x
           L"ink"  ,                                            // 0x
           L"pencil"  ,                                         // 0x
           L"highlighter"  ,                                   // 0x
           L"highlighter"  ,                                   // 0x
           L"highlighter"  ,                                   // 0x
           L"chisel marker"  ,                                  // 0x
           L"brush"  ,                                         // 0x
           L"no preference"  ,                                 // 0x
           L"reserved"  , // 0x78
           L"reserved"  , // 0x79
           L"reserved"  , // 0x7A
           L"reserved"  , // 0x7B
           L"reserved"  , // 0x7C
           L"reserved"  , // 0x7D
           L"reserved"  , // 0x7E
           L"reserved"  , // 0x7F
           L"digitizer diagnostic"  , // 0x80
           L"digitizer error"  , // 0x81
           L"err normal status"  , // 0x82
           L"err transducers exceeded"  ,                       // 0x83
           L"err full trans features unavailable"  ,           // 0x84
           L"err charge low"  ,                                // 0x85
           L"reserved"  ,                                       // 0x86
           L"reserved"  ,                                       // 0x87
           L"reserved"  ,                                       // 0x88
           L"reserved"  ,                                       // 0x89
           L"reserved"  ,                                       // 0x8A
           L"reserved"  ,                                       // 0x8B
           L"reserved"  ,                                       // 0x8C
           L"reserved"  ,                                       // 0x8D
           L"reserved"  ,                                       // 0x8E
           L"reserved"  ,                                       // 0x8F
           L"transducer software info"  ,                      // 0x90
           L"transducer vendor id"  ,                          // 0x91
           L"transducer product id"  ,                         // 0x92
           L"device supported protocols"  ,                     // 0x93
           L"transducer supported protocols"  ,                // 0x94
           L"no protocol"  ,                                    // 0x95
           L"wacom aes protocol"  ,                             // 0x96
           L"usi protocol"  ,                                  // 0x97
           L"microsoft pen protocol"  ,                        // 0x98
           L"reserved"  , // 0x99
           L"reserved"  , // 0x9A
           L"reserved"  , // 0x9B
           L"reserved"  , // 0x9C
           L"reserved"  , // 0x9D
           L"reserved"  , // 0x9E
           L"reserved"  , // 0x9F
           L"supported report rates"  ,                        // 0xA0
           L"report rate"  ,                                    // 0xA1
           L"transducer connected" ,                           // 0xA2
           L"switch disabled"  ,                               // 0xA3
           L"switch unimplemented"  ,                          // 0xA4
           L"transducer switches"  ,                           // 0xA5
           L"reserved"  , // 0xA6 
          // to 0xFFFF                    // 0xA6 to 0xFFFF
       } ,

       {  // page 0x0E haptics
       } ,

    }; // string usages

} // namespace hid
