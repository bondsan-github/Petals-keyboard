#pragma once

#pragma comment( lib, "dxguid.lib")

#include <string>
#include <wrl/client.h>
#include <d3d11.h>

#include <DirectXMath.h>

#include "Custom types.hpp"
#include "Loging.hpp"

using std::wstring;
using Microsoft::WRL::ComPtr;

using DirectX::XMVECTOR;
using DirectX::XMFLOAT4;
//using DirectX::XMFLOAT4X4;
using DirectX::XMMATRIX;
using DirectX::XMVectorSet;

enum class Projection { perspective , orthographic };

class Camera
{
	private:

		HRESULT result { E_FAIL };

		ComPtr< ID3D11Device >			device; //gpu
		ComPtr< ID3D11DeviceContext >	context;

		wstring name;

		XMVECTOR	position	= XMVectorSet( 0.0f , 0.0f , -10.0f , 0.0f );
		XMVECTOR	target		= XMVectorSet( 0.0f , 0.0f , 0.0f , 0.0f );
		XMVECTOR	up			= XMVectorSet( 0.0f , 1.0f , 0.0f , 0.0f );

		float	distance		= 0.0f;
		float	distance_min	= 0.0f;
		float	distance_max	= 0.0f;

		float	rotation_x		= 0.0f;
		float	rotation_y		= 0.0f;

		float	y_min			= 0.0f;
		float	x_min			= 0.0f;

		XMMATRIX				view_matrix {};
		XMMATRIX				projection_matrix {};

		Projection				projection_method = Projection::perspective;

		D3D11_BUFFER_DESC		buffer_description{};

		ComPtr< ID3D11Buffer >	view_matrix_buffer;
		ComPtr< ID3D11Buffer >	projection_matrix_buffer;

        D3D11_MAPPED_SUBRESOURCE mapping;

        D3D11_VIEWPORT viewport;
        uint           viewport_amount = 1u;

        //XMFLOAT4X4     matrix_projection {};
        XMMATRIX       matrix_projection {};
        XMMATRIX       projection_orthographic { 0 , 0 , 0 , 0 ,
                                                 0 , 0 , 0 , 0 ,
                                                 0 , 0 , 0 , 0 ,
                                                 0 , 0 , 0 , 1 };
    private:

        void create_buffer( D3D11_BUFFER_DESC const & description , ID3D11Buffer ** buffer );
        void update_buffer( ID3D11Resource * buffer , XMMATRIX const & matrix );
        // Copy ram buffer to GPU buffer.
        void set_vertex_shader_buffers( uint index_start , uint amount , ID3D11Buffer * const * buffer );

	public:
		
		explicit Camera();

		void initialise( wstring const & name ,
                         XMVECTOR const & position = { 0.0f , 0.0f , -100.0f , 1.0f } ,//= XMVectorSet(0.0f , 0.0f , -100.0f , 1.0f) ,
                         XMVECTOR const & target   = { 0.0f , 0.0f , 0.0f , 1.0f } );

		~Camera();	

		void set_projection( Projection projection = Projection::perspective );
		
		void set_position( XMVECTOR const & position );
		void set_target( XMVECTOR const & target );

		void set_z( float z );
		void set_delta_z( float delta_z );
        
        void update();
        //update(double time_delta);

		// set_projection_matrix( XMMATRIX )

		//void roll  
		//void pitch
		//void target( Mesh * )

		
};