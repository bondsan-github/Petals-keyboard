#pragma once

#include <d2d1.h>

#include "Graphics\Direct2D\Image.h"
#include "Time\Timer.h"

#include <list>

class Sprite : public Image , public Timer
{
    public:
    
        void update(); 

    private:
        
        double current_frame_time {};
};
