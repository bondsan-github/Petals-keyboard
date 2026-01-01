#pragma once

#include "Operating system\MSWindows.h"
#include "Graphics\Direct2D\Direct2D.h"
#include "Time\Timer.h"
#include "Graphics\Size.h"

class Application : public MSWindows, public Direct2D, public Timer
{
    protected:
        
        //Input     input { *this };
        //Audio     audio;

    private:

    public:
        
        Application();

        void initialise( Size in_client_size = {} );
        void run();

        virtual ~Application() = default;

        virtual void update() = 0;
        virtual void render() = 0;

        // cannot call virtual functions in a constructor or destructor 
        // as any derived objects have not been constructed.
};