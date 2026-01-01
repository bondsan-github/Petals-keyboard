#pragma once

#include "Graphics\Point.h"

class Circle
{
    private:

        int   radius_   {};
        Point position_ {};

    public:

        Circle();

        void  position( Point position );
        Point position();
};
