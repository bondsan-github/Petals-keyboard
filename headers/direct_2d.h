#pragma once

#include < string >
#include < vector >
#include < functional >
#include < windows.h >
#include < wrl.h >
#include < d2d1.h >
#include < dwrite.h >
#include < hidsdi.h >
#include < hidpi.h >

#include "vertex.h"

namespace hid // human interface device
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    using      uchar                   = unsigned char;  //  8 bits
    using      ushort                  = unsigned short; // 16 bits
    using      uint                    = unsigned int;   // 32 bits
    using      ulong                   = unsigned long;  //    long same as int
    using      string                  = wstring;

    using      result_win              = HRESULT;

    using      raw_device_list         = RAWINPUTDEVICELIST;
    
    using      node                    = HIDP_LINK_COLLECTION_NODE;
    using      hid_attributes          = HIDD_ATTRIBUTES;
    using      hid_attributes_extended = HIDP_EXTENDED_ATTRIBUTES;

    enum class raw_device_type         { mouse , keyboard , hid }; // Microsoft windows input types
    enum class factory_type            { force_dword = -1 , single_thread , multiple_threads };

    using      factory_d2d             = ID2D1Factory;
    using      paint_structure         = PAINTSTRUCT;
    // width , height
    using      dimensions              = D2D1_SIZE_F;
    using      colours                 = ColorF;

    using      page_window             = ID2D1HwndRenderTarget;
    using      page_window_pointer     = ComPtr< page_window >;
    using      page_plain              = ID2D1RenderTarget;
    using      page_dpi                = D2D1_SIZE_F;
    using      page_dips               = D2D1_SIZE_F;
    using      page_dimensions         = D2D1_SIZE_U;
    //using      divisions               = D2D1_SIZE_U;
    //using      cell_position           = D2D1_SIZE_U;

    using      brush_d2d               = ID2D1Brush; // base 
    using      brush_pointer           = ComPtr< brush_d2d >;
    using      brush_solid             = ID2D1SolidColorBrush;
    using      brush_solid_pointer     = ComPtr< brush_solid >;
    using      brush_opactiy           = float;
    
    using      stroke_style            = ID2D1StrokeStyle;
    using      stroke_style_pointer    = ComPtr< stroke_style >;
    using      stroke_style_properties = D2D1_STROKE_STYLE_PROPERTIES;

    enum class stroke_cap_style  { force_dword = -1 , flat  , square , round , triangle       };
    enum class stroke_line_join  { force_dword = -1 , miter , bevel  , round , miter_or_bevel };
    enum class stroke_dash_style { force_dword = -1 , solid , dash   , dot   , dash_dot       , dash_dot_dot , custom };
    //enum class style { solid , dots , dashes ,
    /*
    struct stroke_style_properties
    {
        stroke_cap_style  cap_start   {};
        stroke_cap_style  cap_dash    {};
        stroke_cap_style  cap_end     {};
        stroke_line_join  line_join   {};
        float             miter_limit {};
        stroke_dash_style dash_style  {};
        float             dash_offset {};
    };
    */

    using      write_factory           = IDWriteFactory;
    enum class write_factory_type      { shared , isolated };
    using      renderer_parameters     = IDWriteRenderingParams;

    using      font_collection         = IDWriteFontCollection;
    using      font_collection_pointer = ComPtr< font_collection >;
    using      font_family             = IDWriteFontFamily;
    using      font_collection_names   = IDWriteLocalizedStrings;
    using      font_weight             = DWRITE_FONT_WEIGHT;
    using      font_style              = DWRITE_FONT_STYLE;
    using      font_stretch            = DWRITE_FONT_STRETCH;

    using      text_format             = IDWriteTextFormat;
    using      text_format_pointer     = ComPtr< text_format >;
    using      text_layout             = IDWriteTextLayout;
    using      text_layout_pointer     = ComPtr< text_layout >;
    enum class text_style              { normal          , oblique       , italic         };
    enum class text_weight             { light     = 300 , regular = 400 , bold     = 700 };
    enum class text_stretch            { condensed = 3   , normal  = 5   , expanded = 7   };
    enum class text_options            { force_dword    = -1 , 
                                         none           =  0 ,
                                         no_snap        =  1 ,
                                         clip           =  2 ,
                                         colour_font    =  4 ,
                                         no_snap_bitmap =  8 };
    using text_metrics = DWRITE_TEXT_METRICS;
    using      text_analyser           = IDWriteTextAnalyzer;

    using      rectangle               = D2D_RECT_F;
    using      rounded_rectangle       = D2D1_ROUNDED_RECT;
    //using      dimensions              = D2D_SIZE_F;

    struct rectangle_edge_middles
    {
        vertex top    {};
        vertex right  {};
        vertex bottom {};
        vertex left   {};
    };

    struct planes
    {
        float horizontal{};
        float vertical{};
    };
}

   //const vector< wstring > raw_device_type_text{ L"mouse" , L"keyboard" , L"human interface device" , L"unknown type" };

/*
    template< typename page_type = page_for_window >
    class page
    {
        private:
            ComPtr< page_type >      page_ptr{};
    };
    */