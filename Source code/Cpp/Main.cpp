// Mark.T. Precision multiple touch input controls

#include "Multiple touch.hpp"

int WINAPI wWinMain( _In_ HINSTANCE instance , _In_opt_ HINSTANCE instance_previous , _In_ LPWSTR parameters , _In_ int show_flags )
{

// Source - https://stackoverflow.com/a
// Posted by Dave Van Wagner, modified by community. See post 'Timeline' for change history
// Retrieved 2025-12-31, License - CC BY-SA 3.0

    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );

   HeapSetInformation( NULL , HeapEnableTerminationOnCorruption , NULL , 0 );
   
   // Initialize COM apartment threaded. 
   // This is the recommended way to initialize COM for the UI thread.
   HRESULT result  = CoInitializeEx( nullptr , COINIT_APARTMENTTHREADED );

   if( SUCCEEDED( result ) )
   {
       Multiple_touch petals_input( instance , parameters , show_flags );
       petals_input.run();
   }

   CoUninitialize();
   
   return 0;
}