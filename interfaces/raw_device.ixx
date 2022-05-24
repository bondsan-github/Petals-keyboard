module;

#include < windows.h >

export module raw_device_module;

import std.core;

import globals;
import raw_device_base_module;

namespace hid
{
   using namespace std;
   
   export class raw_device : public raw_device_base
   {
      protected:
      
         HANDLE  file_pointer {};
         wstring path         {}; // or std::filesystem::wpath

      public:

        class raw_device( HANDLE in_pointer , raw_device_type in_type )
        : raw_device_base{ in_pointer , in_type }
        {
           uint path_char_amount{};

           GetRawInputDeviceInfo( pointer , requests.path , nullptr     , & path_char_amount );

           path.resize( path_char_amount );

           GetRawInputDeviceInfo( pointer , requests.path , path.data() , & path_char_amount );  // wchar_t

           // open i_o device for query 
           file_pointer = CreateFileW( path.data() ,
                                       0 ,                                  // access
                                       FILE_SHARE_READ | FILE_SHARE_WRITE , // share
                                       0 ,                                  // security
                                       OPEN_EXISTING ,                      // creation
                                       FILE_ATTRIBUTE_NORMAL ,              // flags
                                       0 );                                 // template
        }
        
        //~raw_device()
        //{
          //if( file_pointer ) CloseHandle( file_pointer );
        //}
           
   }; // class raw_device

} // namespace hid