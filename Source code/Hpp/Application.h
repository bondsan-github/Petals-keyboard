#pragma once

#include "Operating system\MSWindows.h"
//#include "Graphics\Direct2D\Direct2D.h"
//#include "Time\Timer.h"
#include "Graphics\Size.h"

//#include "Operating system\targetver.h"
//#define _WIN32_WINNT 0x0501
//#include <Windows.h>
//#include <WinUser.h>

class Application : public MSWindows//, public Direct2D, public Timer
{
    public:
        
        Application();

        void initialise( Size client_size );
        void run();

        virtual ~Application() = default;

        virtual void update( RAWINPUT input ) = 0;
        virtual void render() = 0;
};