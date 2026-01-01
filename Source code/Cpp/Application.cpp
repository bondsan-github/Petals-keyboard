#include "Source code/Hpp/Application.hpp"

Application::Application( )
: MSWindows( this ) , Graphics( *this )
{}

void Application::initialise( Size in_client_size )
{
    HWND window = MSWindows::initialise( in_client_size );

    {
        Graphics::initialise( window );
    }

    Timer::initialise();
    Timer::start();
     //timer.tick();
}

void Application::run()
{
    MSWindows::message_loop();
}
