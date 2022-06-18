#pragma once

namespace hid // human interface device
{
   using uchar  = unsigned char;  //  8 bits
   using ushort = unsigned short; // 16 bits
   using uint   = unsigned int;   // 32 bits
   using ulong  = unsigned long;  //    long same as int

   struct                           HIDP_LINK_COLLECTION_NODE;
   using  node =                    HIDP_LINK_COLLECTION_NODE;
   struct                           HIDD_ATTRIBUTES;
   using  hid_attributes          = HIDD_ATTRIBUTES;
   struct                           HIDP_EXTENDED_ATTRIBUTES;
   using  hid_attributes_extended = HIDP_EXTENDED_ATTRIBUTES;
   // sheet window_sheet() // ( / canvas / target )
   //using com_ptr = ComPtr;
   //struct                           ID2D1Factory;
   
   //struct                           PAINTSTRUCT;
   
   //struct                           ID2D1RenderTarget;
   using  render_target           = ID2D1RenderTarget;
   //struct                           ID2D1HwndRenderTarget;
   
   // sheet window_sheet() // ( / canvas / target )
   //struct                           IDWriteFactory;
   using  ms_write_factory        = IDWriteFactory;
   //using ✎ = write;
   //struct                           IDWriteTextFormat;
   using  ms_text_format          = IDWriteTextFormat;
   //struct                           IDWriteTextLayout;
   using  ms_text_layout          = IDWriteTextLayout;
   //struct                           ID2D1SolidColorBrush;
   using  ms_brush_solid_colour   = ID2D1SolidColorBrush;
   //struct                           ID2D1StrokeStyle;
   using  ms_stroke_style         = ID2D1StrokeStyle;
   //struct                           ID2D1LinearGradientBrush;
   using  brush_gradient          = ID2D1LinearGradientBrush;
  // struct                           ID2D1RadialGradientBrush;
   using  brush_radial            = ID2D1RadialGradientBrush;
//   class                            ColorF;
   //using  colours                 = ColorF;
   //struct                           D2D_SIZE_F; 
   using  area                    = D2D_SIZE_F;
   using  dimensions              = D2D_SIZE_F;
   using  divisions               = D2D_SIZE_F;
   //struct                           DWRITE_TRIMMING;
   using  trimming                = DWRITE_TRIMMING;
   // RECT = longs
  // struct                           D2D_RECT_F;
   using  rectangle               = D2D_RECT_F;
  // struct                           D2D1_ROUNDED_RECT;
   using  rounded_rectangle       = D2D1_ROUNDED_RECT;
   using  rrect                   = rounded_rectangle;

   struct vertex
   {
       float x {};
       float y {};
   };

   struct rectangle_points_middle_edge // bounds_intersections_planes;
   {
       vertex top    {};
       vertex right  {};
       vertex bottom {};
       vertex left   {};
   };

   using rect_points_mid = rectangle_points_middle_edge;
   
   // Microsoft windows input types
   enum class raw_device_type { mouse , keyboard , hid };

   //const vector< wstring > raw_device_type_text{ L"mouse" , L"keyboard" , L"human interface device" , L"unknown type" };
   
   // wchar_t ~ unsigned short
   void error( const wchar_t * title_text );

   /*
   using write_format   = IDWriteTextFormat;
   using write_factory  = IDWriteFactory;
   using window_surface = ID2D1HwndRenderTarget;
   using size_float     = D2D1_SIZE_F;
   */

   /*
   template< typename type >
   void release( type ** ptr_ptr_type ) // ptr_array_type
   {
      if( ptr_ptr_type )
      {
         ( *ptr_ptr_type )->Release();
         *ptr_ptr_type = nullptr;
      }
      */
} // namespace hid


   //using rectangle = D2D_RECT_F;
  /*
   class drawable
   {
      ID2D1HwndRenderTarget * target {};
   };
   
   class rectangle
   {
      private:

         struct vertex
         {
            vertex( uint in_x = {} , uint in_y = {} ) : x( in_x ) , y( in_y ) {}

            float x {};
            float y {};
         };

         struct vertices
         {
            vertex a {}; // top left
            vertex b {}; // bottom right
         };

         struct dimension
         {
            float width    {};
            float height   {};
            float x_middle {};
            float y_middle {};
         };

         dimension dimensions {};
         vertices  position   {};
         vertex    center     {};

         vertex _center()
         {
            center.x = position.a.x + dimensions.x_middle;
            center.y = position.a.y + dimensions.y_middle;
         }

      public:

         rectangle() {};

         rectangle( vertex in_center ) 
         : center( in_center )
         {
             //position.a.x = in_center.x -  
         };

         rectangle( uint x1 , uint y1 , uint x2 , uint y2 )
         : position{ { x1 , y1 } , { x2 , y2 } }
         {
            dimensions.width  = x2 - x1;
            dimensions.height = y2 - y1;

            center = _center();
            
            //uint diagonal= sqrt( width^2 + height^2 );
         }
   };
   
   class rounded_rectangle : public rectangle
   {
      public :

         rounded_rectangle( radiuses )
      
      D2D1_ROUNDED_RECT rounded( ) {};//uint center_x , uint center_y )
      
         rectangle.radiusX = ;
         rectangle.radiusY = ;
   };
   

   //struct physical_text_box 
   
   */


   /*
   // enum class _class

   enum class subclass : uchar
   {
      none           = 0x00 ,
      boot_interface = 0x01 ,
      reserved_start = 0x02 ,
      reserved_end   = 0xFF
   };

   // interfaces

   struct descriptor {};

   struct device : public descriptor
   {
      //vector<type
      //class
      //subclass
      //vendor
      //product
      //version
      //
      struct configuration : public descriptor {};
   };

   struct report   : public descriptor
   {
      enum class item_type { main , global , local };
      enum class main_type { input , output , feature , collection , end_collection };

      struct item
      {
         item(uchar in_size) : size(in_size) {}
         uchar size : 2; // of data in bytes 0,1,2,3
         uchar type : 2;
         uchar tag  : 4;

      };

      struct _short : public item {};
      struct _long  : public item
      {
        _long() : item(2) {}; // _long data is two bytes
      };

      vector< item > items {};

   }; // always at least one report
   struct physical      : public device {};
   struct hid           : public device {};
   struct _interface    : public descriptor {};
   struct endpoint      : public descriptor {};
   struct string        : public descriptor {};
   */