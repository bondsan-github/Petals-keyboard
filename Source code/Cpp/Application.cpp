#include "Application.h"

Application::Application()
: MSWindows( this )
{ }

void Application::initialise( Size client_size )
{
    HWND window = MSWindows::initialise( client_size );

    {
        //Direct2D::initialise( window );
    }

    //Timer::initialise();
    //Timer::start();
     
}

void Application::run()
{
    MSWindows::message_loop(); // <-//timer.tick();
}
