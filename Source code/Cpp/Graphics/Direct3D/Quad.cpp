#include "Graphics\Quad.hpp"

Quad::Quad() 
{ }

Quad::Quad( std::wstring const & filename )
{
    load_diffuse( filename );
}

void Quad::reset()
{
}

Quad::Quad( float width , float height , Colour const & colour )
: height_( height ) , width_( width ) , colour_( colour )
{
    float ½width  = width / 2.0f;
    float ½height = height / 2.0f;
    
    vector< Vertex > vertices_
    {
        { { -½width , -½height , 0.0f , 1.0f } , { 0.0f , 1.0f } } , // bottom left
        { { -½width , +½height , 0.0f , 1.0f } , { 0.0f , 0.0f } } , // top left
        { { +½width , +½height , 0.0f , 1.0f } , { 1.0f , 0.0f } } , // top right
        { { +½width , -½height , 0.0f , 1.0f } , { 1.0f , 1.0f } }   // bottom right
    };
    //vector< uint > indices_{ 0u , 1u , 2u , 0u , 2u , 3u };
    vector< uint > indices_{ 0,1,2 , 0,2,3 };

    vector< Vertex > vertices2
    {
        { { -0.5f, -0.5f, 0.0f, 1.0f }, { 0.f, 1.f } },
        { {  0.5f, -0.5f, 0.0f, 1.0f }, { 1.f, 1.f } },
        { {  0.5f,  0.5f, 0.0f, 1.0f }, { 1.f, 0.f } },
        { { -0.5f,  0.5f, 0.0f, 1.0f }, { 0.f, 0.f } },
    };

    vector< uint > indices2 { 3,1,0, 1,3,2 };

    vector< Vertex > vertices3
    {
       { {  -1.0f , -1.0f , -1.0f, 1.0f } , { 0.0f , 0.0f } },
       { {  -1.0f , +1.0f , -1.0f, 1.0f } , { 0.0f , 0.0f } },
       { {  +1.0f , +1.0f , -1.0f, 1.0f } , { 0.0f , 0.0f } },
       { {  +1.0f , -1.0f , -1.0f, 1.0f } , { 0.0f , 0.0f } }
    };

    vector< uint > indices3 { 0 , 1 , 2 ,   0 , 2 , 3  };
    
    // vector< vertex > create_quad_verticies( float width , float height , colour );

    // set_input_layout()
    topology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    vertices( vertices2 );
    indices( indices2 );

    diffuse.create_blank( width , height , colour );
}

void Quad::load_diffuse( wstring const & filename )
{
    reset();

    diffuse.load( filename );

    float ½width  = diffuse.width() / 2.0f;
    float ½height = diffuse.height() / 2.0f;

    //  /\ +y
    //  |
    //  | +z
    //  |/
    //  0-----> +x

    //  -0.5,0.5  *--* 0.5,0.5
    //            |/ |
    //  -0.5,-0.5 *--* 0.5,-0.5

    vector< Vertex > vertices_
    {
        { { -½width , -½height , 0.0f , 1.0f } , { 0.0f , 1.0f } } , // bottom left
        { { -½width , +½height , 0.0f , 1.0f } , { 0.0f , 0.0f } } , // top left
        { { +½width , +½height , 0.0f , 1.0f } , { 1.0f , 0.0f } } , // top right
        { { +½width , -½height , 0.0f , 1.0f } , { 1.0f , 1.0f } }   // bottom right
    };

    vector< uint > indices_{ 0,1,2 , 0,2,3 };

    topology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    vertices( vertices_ );
    indices( indices_ );
}

void Quad::update( double time_delta )
{
    diffuse.update( time_delta );
    Mesh::update( time_delta );
}

void Quad::render()
{
    diffuse.render();
    Mesh::render();
}

//Quad( Quad && move ) // move constructor
//{
//	m_diffuse = move( in_quad.m_diffuse );
//	in_quad.m_diffuse = nullptr;

//	m_width = in_quad.m_width;
//	m_height = in_quad.m_height;
//	m_vertex_colour = in_quad.m_vertex_colour;
//}