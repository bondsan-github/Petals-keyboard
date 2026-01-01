#include "Source code/Hpp/Graphics/Direct3D/Icosahedron.hpp"

#include <vector>

Icosahedron::Icosahedron( uchar tessalation )
{
    float φ = ( 1.0f + sqrt(5.0f) ) / 2.0f; // φ - phi - golden ratio ~ 1.62 
    
    vector< Vertex_uv > vertices_ // 12 Vertices 
    {
        //   position                     u_v
        { {  0.0f,  1.0f,  φ,  0.0f } , { 0.0f, 0.0f } } ,
        { {  0.0f,  1.0f, -φ,  0.0f } , { 0.0f, 0.0f } } ,
        { {  0.0f, -1.0f,  φ,  0.0f } , { 0.0f, 0.0f } } ,
        { {  0.0f, -1.0f, -φ,  0.0f } , { 0.0f, 0.0f } } ,
        { {  1.0f,  φ,  0.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { {  1.0f, -φ,  0.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { { -1.0f,  φ,  0.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { { -1.0f, -φ,  0.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { {  φ,  0.0f,  1.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { {  φ,  0.0f, -1.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { { -φ,  0.0f,  1.0f,  0.0f } , { 0.0f, 0.0f } } ,
        { { -φ,  0.0f, -1.0f,  0.0f } , { 0.0f, 0.0f } } ,
    };

    vector< uint > indices_
    { 
        1,6,4, 4,6,0, 0,6,10, 10,6,11, 11,6,1,
        3,1,9, 9,1,4, 9,4,8,  8,4,0,   8,0,2,  2,0,10, 2,10,7, 7,10,11, 7,11,3, 3,11,1,
        5,3,9, 5,9,8, 5,8,2,  5,2,7,   5,7,3
    };

    topology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    vertices( vertices_ );
    indices( indices_ );

	/*
    tessalate(1);
    tessalate(1);
    tessalate(1);
    tessalate(1);
	*/

    //calc_normals();
}

// set index buffer
// 20 Faces
// at each vertex, 5 edges meet

//   6 6 6 6 6
//   /\/\/\/\/\ 
//  1 4 0 10 11 1
//  /\/\/\/\/\/
// 3 9 8 2 7 3
//  \/\/\/\/\/
//  5 5 5 5 5 

// (  0, ±1, ±φ )
// ( ±1, ±φ,  0 )
// ( ±φ,  0, ±1 )


