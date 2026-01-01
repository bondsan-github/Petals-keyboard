#pragma once

#include "Source code/Hpp/Custom types.hpp"
#include "Source code/Hpp/Graphics/Direct3D/Mesh.hpp"

#include <math.h>
#include <algorithm>
#include <random>

//template< typename TYPE >
//class Icosahedron : public Mesh< TYPE > 

//template< typename vertex_t >
class Icosahedron : public Mesh
{
    public:

        Icosahedron( uchar tessalation );
        //Icosahedron( uchar tessalation );

        void update( double time_delta ) {}

        void render()
        {
            Mesh::render();
        }
};
