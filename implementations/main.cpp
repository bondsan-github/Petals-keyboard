//https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/november/windows-with-c-exploring-fonts-with-directwrite-and-modern-c
//https://learn.microsoft.com/en-us/windows/win32/directwrite/direct-write-portal

// markt precision multiple touch input controls

#pragma comment( lib , "hid.lib" )
#pragma comment( lib , "d2d1" )
#pragma comment( lib , "dwrite.lib" )

#include "..\headers\gui_microsoft.h"
#include "..\headers\graphics_d2d.h"
#include "..\headers\write_d2d.h"
#include "..\headers\hid_usages.h"
#include "..\headers\hid_devices.h"
//#include "..\headers\grid_d2d.h"

//int WINAPI wWinMain( _In_ HINSTANCE instance , _In_opt_ HINSTANCE instance_previous , _In_ LPWSTR parameters , _In_ int show_flags )
int WINAPI wWinMain( HINSTANCE instance , HINSTANCE instance_previous , LPWSTR parameters , int show_flags )
{
   // Initialize COM apartment threaded. This is the recommended way to initialize COM for the UI thread.
   //CoInitializeEx( nullptr , COINIT_APARTMENTTHREADED );
   
   hid::graphics_d2d  graphics;
   hid::write_d2d     write;
   hid::hid_usages    usages;
   hid::hid_devices   devices;
   hid::gui_microsoft window( instance , parameters , show_flags );
   window.message_loop();

   //CoUninitialize();
   
   return 0;
}

//MessageBox( 0 , L"application working" , L"precision multi touch" , MB_OK );