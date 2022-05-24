module;

export module globals;

export import std.core;

//namespace hid
//{
   export
   {
      using uchar  = unsigned char;  //  8 bits
      using ushort = unsigned short; // 16 bits
      using uint   = unsigned int;   // 32 bits
      using ulong  = unsigned long;  //    long same as int
   };

   // Microsoft windows input types
   export enum class raw_device_type { mouse , keyboard , hid };

   const std::vector< std::wstring > raw_device_type_text{ L"mouse" , L"keyboard" , L"human interface device" , L"unknown type" };

   export template< typename type >
      void release( type ** ptr_ptr_type ) // ptr_array_type
   {
      if( ptr_ptr_type )
      {
         ( *ptr_ptr_type )->Release();
         *ptr_ptr_type = nullptr;
      }
   }
//} // namespace hid