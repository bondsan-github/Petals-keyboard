#include "Graphics\Mesh.hpp"
#include "Graphics\Graphics.hpp"

#define _USE_MATH_DEFINES // for M_PI
#include <math.h>

#include <DirectXMath.h>

//template< typename vertex_t >
//Mesh< vertex_t >::Mesh(  ) 

using std::array;
using DirectX::XMMatrixTranslation;
using DirectX::XMMatrixRotationRollPitchYaw;
using DirectX::XMMatrixScaling;

Mesh::Mesh()
{
    device->GetImmediateContext( & context );

    create_buffer_matrix_world();
}

Mesh::~Mesh()
{
    world_matrix_buffer.Reset();
    indices_buffer.Reset();
    vertices_buffer.Reset();
    context.Reset();
    device.Reset();
}

void Mesh::reset()
{
    position_.x = 0.0; position_.y = 0.0; position_.z = 0.0;
    rotation_.x = 0.0; rotation_.y = 0.0; rotation_.z = 0.0;
    scale_.x = 0.0; scale_.y = 0.0; scale_.z = 0.0;

    topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    world_matrix_        = XMMatrixIdentity();
    scale_matrix         = XMMatrixIdentity();
    rotation_matrix      = XMMatrixIdentity();
    translation_matrix   = XMMatrixIdentity();
    orbit_matrix         = XMMatrixIdentity();
}

// Set how vertices relate to each other
void Mesh::topology( D3D11_PRIMITIVE_TOPOLOGY const & toplogy )
{
    topology_ = toplogy;

    context->IASetPrimitiveTopology( topology_ );

    // print_debug( "\n Primitive topology bound." );
}

// Add a vertex to existing vertices
void Mesh::add_vertex( Vertex const & vertex )
{
    vertices_.push_back( vertex );

    create_buffer_vertices();
}

// Set new or replace vertices
void Mesh::vertices( vector<Vertex> const & vertices )
{
    vertices_ = vertices;

    create_buffer_vertices();
}

// Set new or replace vertices
void Mesh::indices( vector< uint > const & indices )
{
    indices_ = indices;

    create_buffer_indices();
}

// Create gpu resource for vertices
void Mesh::create_buffer_vertices()
{
    vertices_amount = static_cast< uint >( vertices_.size() );
    
    vertices_buffer_description.ByteWidth = sizeof( Vertex ) * vertices_amount;
    //vertices_buffer_description.Usage     = D3D11_USAGE_IMMUTABLE;//D3D11_USAGE_DEFAULT;
    vertices_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    //vertices_buffer_description.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ;
    //vertices_buffer_description.MiscFlags = 0;
    //vertices_buffer_description.StructureByteStride = sizeof( Vertex );
    vertices_buffer_description.StructureByteStride = 24;

    D3D11_SUBRESOURCE_DATA resource_data {};

    resource_data.pSysMem = vertices_.data();
    //resource_data.SysMemPitch;
    //resource_data.SysMemSlicePitch;

    result = device->CreateBuffer( & vertices_buffer_description ,
                                   & resource_data ,
                                   & vertices_buffer );

    if( FAILED( result ) ) error_exit( L"Unable to create vertices buffer" , result );

    set_name( vertices_buffer.Get() , L"Vertices buffer");
    print_debug("\n Vertex buffer created.");   
}

// create_buffer( enum class { vertex , index , constant , shader , stream , render , depth } , const & data ) 

// Create gpu resource for mesh indices
void Mesh::create_buffer_indices()
{
    indices_amount = static_cast< uint >( indices_.size() ); // change to ull

    indices_buffer_description.ByteWidth	  = sizeof( uint ) * indices_amount; // buffer size in bytes
    //indices_buffer_description.Usage		  = D3D11_USAGE_IMMUTABLE;//D3D11_USAGE_DEFAULT;
    indices_buffer_description.BindFlags	  = D3D11_BIND_INDEX_BUFFER;
    //indices_buffer_description.CPUAccessFlags = 0;
    //indices_buffer_description.MiscFlags      = 0;
    //indices_buffer_description.StructureByteStride = sizeof( uint );

    D3D11_SUBRESOURCE_DATA resource_data {};

    resource_data.pSysMem = indices_.data();

    result = device->CreateBuffer( & indices_buffer_description ,
                                   & resource_data , 
                                   & indices_buffer );

    if( FAILED( result ) ) error_exit( L"Unable to create indices buffer." , result );

    set_name( indices_buffer , L"Indices_buffer" );
    print_debug( "\n Indices buffer created." );
}

void Mesh::create_buffer_matrix_world()
{
    // Create a buffer to map to GPU for the world matrix.
    
    world_buffer_description.ByteWidth      = sizeof( XMMATRIX );
    world_buffer_description.Usage          = D3D11_USAGE_DYNAMIC;//DEFAULT;//_IMMUTABLE////_STAGING;
    world_buffer_description.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
    world_buffer_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //world_buffer_description.StructureByteStride = sizeof( XMMATRIX );
    world_buffer_description.MiscFlags      = 0;

    // world_buffer_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //   It is invalid for a D3D11_USAGE_DEFAULT Buffer Resource 
    //   to have CPUAccessFlags set when BindFlags other than 
    //   D3D11_BIND_SHADER_RESOURCE and D3D11_BIND_UNORDERED_ACCESS are set.
    

    // " D3D11_USAGE_DYNAMIC is typically used on resources with vertex data and on constant buffers.
    //   Use the ID3D11DeviceContext::Map and ID3D11DeviceContext::Unmap methods to write data to these resources. "

    // If the bind flag is D3D11_BIND_CONSTANT_BUFFER, you must set the ByteWidth value in multiples of 16, 
    // and less than or equal to D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT = 4096	

    result = device->CreateBuffer( & world_buffer_description , // buffer description
                                   nullptr , // subresource data description
                                   & world_matrix_buffer ); // ID3D11Buffer target

    if( FAILED( result ) ) error_exit( L"Unable to create world matrix buffer." , result );

    bind_constant_buffers();

    set_name( world_matrix_buffer , L"world_matrix_buffer" );
    print_debug( "\n World matrix buffer created." );
}

void Mesh::update_world_matrix()
{
    world_matrix_ = scale_matrix * rotation_matrix * translation_matrix;

    world_matrix_ = XMMatrixTranspose( world_matrix_ );

    update_world_matrix_buffer();
}

void Mesh::update_world_matrix_buffer()
{
    result = context->Map( world_matrix_buffer.Get() , 
                           0 , // sub-resource
                           D3D11_MAP_WRITE_DISCARD ,
                           0 ,
                           & mapping );

    if( FAILED( result ) ) error_exit( L"Unable to map world matrix buffer." , result );

    memcpy( mapping.pData , & world_matrix_ , sizeof( XMMATRIX ) );

    context->Unmap( world_matrix_buffer.Get() ,
                    0 ); // sub-resource
}

void Mesh::bind_constant_buffers()
{
    context->VSSetConstantBuffers( 0 , // constant buffer index // VS_BUFFER_MESH_WORLD 
                                   1 , // buffer amount
                                   world_matrix_buffer.GetAddressOf() ); // Array of constant buffers
}

void Mesh::bind_index_buffer()
{
    uint offset {};

    context->IASetIndexBuffer( indices_buffer.Get() , // pointer to ID3D11Buffer object   
                               //DXGI_FORMAT_R16_UINT , // 16 bit unsigned short
                               DXGI_FORMAT_R32_UINT , // 32 bit unsigned integer
                               offset ); // Offset (in bytes) from the start of the index buffer to the first index to use.
    // short , unsigned short = 2 bytes = 8 * 2 = 16 bits
    // long  , unsigned long  = 4 bytes = 8 * 4 = 32 bits	
}

void Mesh::bind_vertex_buffers()
{
    // Bind vertex buffer to pipeline.

    uint stride = sizeof( Vertex );
    uint offsets[1] { 0 };

    context->IASetVertexBuffers( 0 , // start slot
                                 1 , // buffer amount
                                 vertices_buffer.GetAddressOf() , // buffer
                                 & stride , // stride/s
                                 offsets ); // offset/s
}

void Mesh::world_matrix( XMMATRIX const & matrix )
{
    world_matrix_ = matrix;

    update_world_matrix();
}

XMMATRIX Mesh::world_matrix() const
{
    return world_matrix_;
}

void Mesh::update( double time_delta )
{
    // if ( vertices_changed or indices_changed )

    update_world_matrix_buffer();
    //VSSetConstantBuffers();

    //update_buffer_matrix_world();
    //update_VS_buffer_matrix_world();
}

void Mesh::position( XMFLOAT3 const & position )
{
    position_ = position;

    translation_matrix = XMMatrixTranslation( position.x , position.y , position.z );

    update_world_matrix();
};

void Mesh::translate_x( float x )
{
    position_.x += x;

    translation_matrix = XMMatrixTranslation( position_.x , position_.y , position_.z );

    update_world_matrix();
}

void Mesh::translate_y( float y )
{
    position_.y += y;

    translation_matrix = XMMatrixTranslation( position_.x , position_.y , position_.z );

    update_world_matrix();
}

void Mesh::translate_z( float z )
{
    position_.y += z;

    translation_matrix = XMMatrixTranslation( position_.x , position_.y , position_.z );

    update_world_matrix();
}

// Rotate around local X axis
void Mesh::rotate_x( float radians )
{
    rotation_.x += radians;
    
    //matrix_rotation = XMMatrixRotationX( rotation.x );
    rotation_matrix = XMMatrixRotationRollPitchYaw( rotation_.x , rotation_.y , rotation_.z );

    update_world_matrix();
}

// Rotate around local X axis
void Mesh::rotate_y( float radians )
{
    // if > 2pi // unwind()
    rotation_.y += radians;

    rotation_matrix = XMMatrixRotationRollPitchYaw( rotation_.x , rotation_.y , rotation_.z );

    update_world_matrix();
}

// Rotate around local X axis
void Mesh::rotate_z( float radians )
{
    //print_debug( "\ndelta angle: %.20f" , rotation.z);

    rotation_.z += radians;

    if( rotation_.z > 2 * M_PI ) rotation_.z = 0;

    rotation_matrix = XMMatrixRotationRollPitchYaw( rotation_.x , rotation_.y , rotation_.z );

    update_world_matrix();

    //print_debug( "\ndelta angle: %.20f" , rotation.z );
}

void Mesh::scale( XMFLOAT3 const & scale )
{
    scale_ = scale;

    scale_matrix = XMMatrixScaling( scale_.x , scale_.y , scale_.z );

    //world_matrix *= XMMatrixScaling( XMVectorGetX( in_scale_x ) , XMVectorGetY( in_scale_y ) , XMVectorGetZ( in_scale_z ) )

    update_world_matrix();
}

void Mesh::delta_scale( XMFLOAT3 const & scale )
{
    scale_.x += scale.x;
    scale_.y += scale.y;
    scale_.z += scale.z;

    scale_matrix = XMMatrixScaling( scale_.x , scale_.y , scale_.z );

    update_world_matrix();
}

void Mesh::render()
{
    topology( topology_ );

    bind_vertex_buffers();
    bind_index_buffer();
    bind_constant_buffers();

    uint amount { static_cast<uint>( indices_.size() ) };
    //context->DrawIndexed( indices_.size() , // Number of index's to draw.
    context->DrawIndexed( amount , // Number of index's to draw.
                          0u , // first index read by the GPU from the index buffer
                          0u ); // A value added to each index before reading a vertex from the vertex buffer
}

// Rotate around input axis
//void Mesh::rotate_axis( XMVECTOR const axis ,  float const radians ) {}

// void Mesh::Rotation( XMFLOAT3 const & radians ) { rotation = radians; }
//void Mesh::Angle_x( float radians ) { rotation.x = radians; }
//void Mesh::Angle_y( float radians ) { rotation.y = radians; }
//void Mesh::Angle_z( float ) { rotation.z = radians; }

//void Rotation( const XMVECTOR rotation )
//{
//	rotation.x = XMVectorGetX( rotation );
//	rotation.y = XMVectorGetY( rotation );
//	rotation.z = XMVectorGetZ( rotation );
//}

//void Angle_x( const float in_rad );
//void Angle_y( const float in_rad );
//void Angle_z( const float in_rad );