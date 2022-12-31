//https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/november/windows-with-c-exploring-fonts-with-directwrite-and-modern-c
//https://learn.microsoft.com/en-us/windows/win32/directwrite/direct-write-portal

// markt precision multiple touch input controls

#pragma comment( lib , "hid.lib" )
#pragma comment( lib , "d2d1" )
#pragma comment( lib , "dwrite.lib" )

#include "..\headers\custom_types.h"
#include "..\headers\gui_microsoft.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_devices.h"
//#include "..\headers\grid_d2d.h"

int WINAPI wWinMain( _In_ HINSTANCE instance , _In_opt_ HINSTANCE instance_previous , _In_ LPWSTR parameters , _In_ int show_flags )
{
   HeapSetInformation( NULL , HeapEnableTerminationOnCorruption , NULL , 0 );

   // Initialize COM apartment threaded. This is the recommended way to initialize COM for the UI thread.
   HRESULT result  = CoInitialize( 0 );
   //HRESULT result  = CoInitializeEx( nullptr , COINIT_APARTMENTTHREADED );

   if(SUCCEEDED(result) )
   {
       hid::gui_microsoft window( instance , parameters , show_flags );
       hid::graphics_d2d  graphics;
       hid::write_d2d     write;
       hid::hid_usages    usages;
       hid::hid_devices   devices;
   
       window.message_loop();
   }
   CoUninitialize();
   
   return 0;
}