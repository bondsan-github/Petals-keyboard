#pragma once

#include < windows.h >
#include < strsafe.h >

#include < vector >
#include < string >

namespace hid // human interface device
{
   using namespace std;
   //using namespace D2D1;

   using uchar  = unsigned char;  //  8 bits
   using ushort = unsigned short; // 16 bits
   using uint   = unsigned int;   // 32 bits
   using ulong  = unsigned long;  //    long same as int

   // Microsoft windows input types
   enum class raw_device_type { mouse , keyboard , hid };

   const vector< wstring > raw_device_type_text{ L"mouse" , L"keyboard" , L"human interface device" , L"unknown type" };
   
   // wchar_t ~ unsigned short
   void error( const wchar_t * title_text )
   {
       // Retrieve the system error message for the last-error code

      const uint char_amount {200};

      wchar_t message[ char_amount ] {};
      wchar_t display[ char_amount ] {};
      ulong   error_id               = GetLastError();

      FormatMessage(// FORMAT_MESSAGE_ALLOCATE_BUFFER |
                     FORMAT_MESSAGE_FROM_SYSTEM     |   //  search the system message-table resource(s) for the requested message
                     FORMAT_MESSAGE_IGNORE_INSERTS    , // later formatting
                     0 ,  // source
                     error_id ,
                     MAKELANGID( LANG_NEUTRAL , SUBLANG_DEFAULT ) ,
                     //( LPTSTR ) & message ,
                     message ,
                     char_amount ,  // amount of characters
                     0 ); // ... va_list

     // Display the error message and exit the process
      //display = LocalAlloc( LMEM_ZEROINIT , ( lstrlen( message ) + lstrlen( title_text ) + 40 ) * sizeof( wchar_t ) );

      StringCchPrintf( display ,
                       char_amount  ,
                       L"%s : error %d: %s" , title_text , error_id , message );

      MessageBox( 0 , display , L"error" , MB_OK );

      ExitProcess( error_id );
   }

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