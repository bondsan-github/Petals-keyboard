#pragma once

#include <vector>
#include <array>
#include <memory>
#include <wrl/client.h>
#include <limits.h> // for FLT_MAX/MIN

#include <d3d11.h>
#include <DirectXMath.h>

#include "Source code/Hpp/Custom types.hpp"
#include "Source code/Hpp/Graphics/Direct3D/Input layouts.hpp"
#include "Source code/Hpp/Graphics/DirectXMath extension.hpp"

using Microsoft::WRL::ComPtr;
using std::vector;
//using std::make_unique;
//using std::shared_ptr;

using DirectX::XMFLOAT2;
using DirectX::XMFLOAT3;
using DirectX::XMVECTOR;
using DirectX::XMMATRIX;
using DirectX::XMVectorGetX;
using DirectX::XMMatrixIdentity;
using DirectX::XMVectorGetX;
using DirectX::XMVectorGetY;
using DirectX::XMVectorGetZ;

//template< typename vertex_type >
//***********************
//using vertex = vertex_texture;
//***********************

class Mesh
{
	private:

		HRESULT                       result { E_FAIL };

		ComPtr< ID3D11Device >        device;
		ComPtr< ID3D11DeviceContext > context;
		
		vector< Vertex >              vertices_;
        //vector< vertex_type >       vertices;
		vector< uint >                indices_; 
        // ** 32 bit indices ** = DXGI_FORMAT_R32_UINT

		D3D11_PRIMITIVE_TOPOLOGY      topology_ { D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST };
        D3D11_BUFFER_DESC             vertices_buffer_description {};
		ComPtr< ID3D11Buffer >        vertices_buffer;
		uint                          vertices_amount {};

		ComPtr< ID3D11Buffer >        indices_buffer;
        D3D11_BUFFER_DESC             indices_buffer_description {};
		uint                          indices_amount {};

		XMFLOAT3                      position_ {};
		XMFLOAT3                      rotation_ {};
		XMFLOAT3                      scale_ { 1.0f, 1.0f, 1.0f };

		XMMATRIX                      world_matrix_      = XMMatrixIdentity();
		XMMATRIX                      scale_matrix       = XMMatrixIdentity();
		XMMATRIX                      rotation_matrix    = XMMatrixIdentity();
		XMMATRIX                      translation_matrix = XMMatrixIdentity();
		XMMATRIX                      orbit_matrix       = XMMatrixIdentity();

		D3D11_BUFFER_DESC             world_buffer_description {};
		//D3D11_SUBRESOURCE_DATA      subresource_data {};
		ComPtr< ID3D11Buffer >        world_matrix_buffer;
        D3D11_MAPPED_SUBRESOURCE      mapping;

		//XMFLOAT2 texture2D_dimensions { };

		void create_buffer_vertices();
		void create_buffer_indices();
		void create_buffer_matrix_world();

		// void set_diffuse_map( Microsoft::WRL::ComPtr< ID3D11ShaderResourceView > view );
		// void set_pixel_shader_resource_diffuse_map( Microsoft::WRL::ComPtr< ID3D11Texture2D > map );
        
		// void draw_indexed();

		void update_world_matrix_buffer();

		void bind_constant_buffers();
		void bind_vertex_buffers();
        // void set_input_assember_vertex_buffer( ComPtr< ID3D11Buffer > verticies );
		void bind_index_buffer();

    public:

        explicit Mesh();
        ~Mesh();

        void reset();

        void topology( D3D11_PRIMITIVE_TOPOLOGY const & toplogy );
        
        void add_vertex( Vertex const & vertex );

        void vertices( vector< Vertex > const & vertices );
        void indices( vector< uint> const & indices );

        void position( XMFLOAT3 const & position );
        //void set_position( XMVECTOR const & position );
        //void set_position( float const & x , float const & y , float const & z );
        
        //void set_x( float const x );
        //void set_y( float const y );
        //void set_z( float const z );

        XMFLOAT3 position() const;

        //XMVECTOR get_position()
        //{
        //	XMMATRIX temp_matrix = XMMatrixTranspose( world_matrix );
        //	return temp_matrix.r[ 3 ];
        //}

        void translate_x( float x );
        void translate_y( float y );
        void translate_z( float z );

        void rotation( XMFLOAT3 const & in_rotation );

        void rotate_x( float radians );
        void rotate_y( float radians );
        void rotate_z( float radians );

        //void Mesh::rotate_axis( const XMVECTOR axis , float radians ) {}

        //void rotation_z_about_point( const XMFLOAT3 & pivot , float angle_radians );
        //void rotate_point_z( const XMFLOAT3 in_pivot ,  float angle_radians , const XMFLOAT3 in_translation );

        //void orbit_point_z( const XMFLOAT3 & point , float angle_radians );
        //void orbit_point_z( const XMVECTOR & point , float angle_radians );

        //void rotate_origin_z( float angle_radians );
        //void rotate_world_z( float angle_radians );

        //void orbit_z( float angle_radians );

        void scale( XMFLOAT3 const & scale );
        void delta_scale( XMFLOAT3 const & scale );

        void update( double time_delta );
        void update_world_matrix();

        void     world_matrix( XMMATRIX const & world );
        XMMATRIX world_matrix() const;

        //vector< vertex_rgba_uv > get_world_vertices() const;

        // world coordinates 
        //Bounding_box get_bounding_box() const; // get_AABB

        void render();

        //std::shared_ptr<map> map( maps::diffuse )
    //protected:
        //Texture texture;
};

//Mesh_manager.add_mesh( wstring name, wstring filename );

// get_AABB
// for each vertex
//   world_vertex = vertex[i] *= world_matrix;

//vector< XMFLOAT3 > world_vertices;

////XMFLOAT3 point{};
////float x , y , z = 0; // ! ;)

////AABB bob_test {};
////
////for( auto & vertex : vertices )
////{

////	XMVECTOR vertex_world = XMVector3Transform( XMLoadFloat3( &XMFLOAT3( vertex.point.x , vertex.point.y , vertex.point.z ) ) , world_matrix );
////	
////	x = XMVectorGetX( vertex_world );
////	y = XMVectorGetY( vertex_world );
////	z = XMVectorGetZ( vertex_world );

////	debug_out( "\nvertex.x = %.2f , y = %.2f" , vertex.point.x , vertex.point.y );
////	debug_out( "   _world.x = %.2f , y = %.2f" , x , y );
////}
////
////debug_out( "\n" );

//D3D11_MAPPED_SUBRESOURCE mapped_buffer;
//result = video_device_context->Map( vertex_buffer.Get() , 0 , D3D11_MAP_READ , 0 , &mapped_buffer );
//vertex_rgba_uv * world_verticies = reinterpret_cast< vertex_rgba_uv * >( mapped_buffer.pData );
//AABB bounding_box;
//bounding_box.min.x = world_vertices			
//for( uint i = 0; i < vertices.size(); ++i )
//{
//	//temp_verticies[ i ].Pos = mWaves[ i ];
//}
//video_device_context->Unmap( vertex_buffer.Get() , 0 );

//ID3D11Buffer * staging_vertex_buffer;
//D3D11_BUFFER_DESC staging_vertex_buffer_description{};
//staging_vertex_buffer_description.ByteWidth = sizeof( XMMATRIX );
//staging_vertex_buffer_description.Usage = D3D11_USAGE_STAGING;
//staging_vertex_buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			
////D3D11_USAGE_STAGING = A resource that supports data transfer (copy) from the GPU to the CPU.
//video_device_context->CopyResource( vertex_buffer.Get() , &staging_vertex_buffer );
////Create a 2nd buffer with D3D11_USAGE_STAGING; fill the second buffer using ID3D11DeviceContext::Map , ID3D11DeviceContext::Unmap; 
////use ID3D11DeviceContext::CopyResource to copy from the staging buffer to the default buffer.

//void set_rotation( const XMFLOAT3 in_rotation ) 
//{ 
//	rotation = in_rotation; 
//	rotation_matrix = XMMatrixRotationRollPitchYaw( rotation.x , rotation.y , rotation.z );

//	update_world_matrix();
//}

//XMFLOAT3 get_centre()
//{
//XMVECTOR vertex_world{};
//XMFLOAT3 centre {};

//for( auto & vertex : vertices )
//{
//	vertex_world = XMVector3Transform( XMLoadFloat3( &XMFLOAT3( vertex.point.x , vertex.point.y , vertex.point.z ) ) , world_matrix );

//	centre.x += XMVectorGetX( vertex_world );
//	centre.y += XMVectorGetY( vertex_world );
//	centre.z += XMVectorGetZ( vertex_world );
//}

//centre.x /= vertices.size();
//centre.y /= vertices.size();
//centre.z /= vertices.size();

//return centre;
//}

/*XMVECTOR new_position {};
XMVECTOR new_scale {};
XMVECTOR new_rotation {};

XMMatrixDecompose( & new_scale , & new_rotation , & new_position , world_matrix );

x = XMVectorGetX( new_position );
y = XMVectorGetY( new_position );
z = XMVectorGetZ( new_position );*/