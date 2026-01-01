#include "Graphics\Circle.h"

Circle::Circle()
{
}

void Circle::position( Point position )
{
    position_ = position;
}

Point Circle::position()
{
    return position_;
}