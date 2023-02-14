//https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/november/windows-with-c-exploring-fonts-with-directwrite-and-modern-c
//https://learn.microsoft.com/en-us/windows/win32/directwrite/direct-write-portal

// markt precision multiple touch input controls

#pragma comment( lib , "hid.lib" )
#pragma comment( lib , "d2d1" )
#pragma comment( lib , "dwrite.lib" )

#include "..\headers\hid_multiple_touch.h"

int WINAPI wWinMain( _In_ HINSTANCE instance , _In_opt_ HINSTANCE instance_previous , _In_ LPWSTR parameters , _In_ int show_flags )
{
   HeapSetInformation( NULL , HeapEnableTerminationOnCorruption , NULL , 0 );
   // Initialize COM apartment threaded. This is the recommended way to initialize COM for the UI thread.
   HRESULT result  = CoInitializeEx( nullptr , COINIT_APARTMENTTHREADED );

   if( SUCCEEDED(result) )
   {
       using namespace hid;
       
       hid::hid_multiple_touch petals_input( instance , parameters , show_flags);
   }

   CoUninitialize();
   
   return 0;
}