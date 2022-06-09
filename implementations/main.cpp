// markt precision multiple touch input controls

#pragma comment( lib , "hid.lib" )
#pragma comment( lib , "d2d1" )
#pragma comment( lib , "dwrite.lib" )

#include "..\headers\multi_touch.h"

int WINAPI wWinMain( _In_ HINSTANCE instance , _In_opt_ HINSTANCE instance_previous , _In_ LPWSTR parameters , _In_ int show_flags )
{
   using namespace hid;

   // Initialize COM apartment threaded. This is the recommended way to initialize COM for the UI thread.
   CoInitializeEx( nullptr , COINIT_APARTMENTTHREADED );

   //application
   int         result {};
   multi_touch input;

   input.initialise( instance , parameters , show_flags );
   result = input.begin();
   
   CoUninitialize();

   return result;
}

//MessageBox( 0 , L"application working" , L"precision multi touch" , MB_OK );