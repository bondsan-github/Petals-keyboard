// markt precision multiple touch input controls

#pragma comment( lib , "hid.lib" )
#pragma comment( lib , "d2d1" )
#pragma comment( lib , "dwrite.lib" )

#include "..\headers\multi_touch.h"

int WINAPI wWinMain( _In_ HINSTANCE hInstance , _In_opt_ HINSTANCE hPrevInstance , _In_ LPWSTR lpCmdLine , _In_ int nShowCmd )
{
   using namespace hid;

   multi_touch input;
   //main_window app_window;
   
   //MessageBox( 0 , L"application working" , L"precision multi touch" , MB_OK );

   return 0;
}