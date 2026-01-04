// Mark.T. Precision multiple touch input

#include "Multiple touch.h"

int WINAPI wWinMain( _In_ HINSTANCE instance , _In_opt_ HINSTANCE instance_previous , _In_ LPWSTR parameters , _In_ int show_flags )
{
   HeapSetInformation( NULL , HeapEnableTerminationOnCorruption , NULL , 0 );
   
   // Initialize COM apartment threaded. 
   // This is the recommended way to initialize COM for the UI thread.
   HRESULT result = CoInitializeEx( nullptr , COINIT_APARTMENTTHREADED );

   if( SUCCEEDED( result ) )
   {
       //using namespace HID;
       
       HID::Multiple_touch petals_input( instance, parameters, show_flags );
       petals_input.run();
   }

   CoUninitialize();
   
   return 0;
}