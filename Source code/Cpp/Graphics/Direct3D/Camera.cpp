#include <d3dcommon.h>

#include "Locate.hpp"
#include "Graphics\Camera.hpp"
#include "Graphics\Graphics.hpp"
#include "Operating system\Operating system.hpp"

using DirectX::XM_PIDIV2;
using DirectX::XM_PIDIV4;
using DirectX::XMMatrixLookAtLH;
using DirectX::XMMatrixPerspectiveFovLH;
using DirectX::XMMatrixOrthographicLH;
using DirectX::XMVectorSetZ;

Camera::Camera() 
{ }

Camera::~Camera()
{
    projection_matrix_buffer.Reset();
    view_matrix_buffer.Reset();
    context.Reset();
    device.Reset();
}

void Camera::initialise( wstring const & name , XMVECTOR const & position , XMVECTOR const & target ) 
{
    this->position = position;
    this->target = target;
    this->name = name;

    device = Locate::graphics().device();
    device->GetImmediateContext( & context );

	view_matrix = XMMatrixLookAtLH( this->position , this->target , up );
	view_matrix = XMMatrixTranspose( view_matrix );

	set_projection( Projection::perspective );
	
	buffer_description.ByteWidth           = sizeof( XMMATRIX );
	buffer_description.Usage               = D3D11_USAGE_DYNAMIC;
	buffer_description.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
	buffer_description.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
	//buffer_description.MiscFlags = 0;
    buffer_description.StructureByteStride = sizeof( XMMATRIX );

	// ************************************************************************************************
	// " D3D11_USAGE_DYNAMIC is typically used on resources with vertex data and on constant buffers.
	//   Use the ID3D11DeviceContext::Map and ID3D11DeviceContext::Unmap methods to write data to these resources. "
	// ************************************************************************************************

	// Pay attention to the size of the constant buffers, 
	// if they are not multiples of 16 you need to pad extra space on to the end
	// of them or the CreateBuffer function will fail.
	// In this case the constant buffer is 28 bytes with 4 bytes padding to make it 32.

	//----------------create_buffer world----------------//
    
	result = device->CreateBuffer( & buffer_description ,
                                   nullptr , // subresource data description
                                   & view_matrix_buffer ); // ID3D11Buffer target

    if( FAILED( result ) ) error_exit( L"Unable to create view matrix buffer." , result );


	//----------------create buffer projection---------------//
	result = device->CreateBuffer( & buffer_description ,
                                   nullptr , // subresource data description
                                   & projection_matrix_buffer ); // ID3D11Buffer target	

    if( FAILED( result ) ) error_exit( L"Unable to create projection matrix buffer." , result );

}

void Camera::set_vertex_shader_buffers( uint index_start ,
                                        uint amount ,
                                        ID3D11Buffer * const * buffer )
{
    context->VSSetConstantBuffers( index_start , // Index into the device's zero-based array to begin setting constant buffers to // VS_BUFFER_CAMERA_VIEW
                                   amount , // Number of buffers to set
                                   buffer ); // Array of constant buffers	
}

void Camera::set_projection( Projection projection )
{
    //context->RSGetViewports( & viewport_amount , & viewport );
    //Size viewport = Locate::graphics().client_size();

    RECT area {};

    GetClientRect( Locate::os().window() , & area );

    if( projection == Projection::perspective )
    {
        //projection_matrix = XMMatrixPerspectiveFovLH( XM_PIDIV2 , // Fov angle Y
        projection_matrix = XMMatrixPerspectiveFovLH( XM_PIDIV4 , // Fov angle Y
                                                      area.right / area.bottom , // aspect_ratio
                                                      0.01f , 100.0f );
                                                      //FLT_MIN , // near Z
                                                      //FLT_MAX ); // far Z
    }
    else
    {
        projection_matrix = XMMatrixOrthographicLH( area.right ,
                                                    area.bottom ,
                                                    0.01f , 100.0f );
                                                    //FLT_MIN , // near Z
                                                    //FLT_MAX ); // far Z
    }

    projection_matrix = XMMatrixTranspose( projection_matrix );
}

void Camera::update_buffer( ID3D11Resource * buffer , XMMATRIX const & matrix)
{
    result = context->Map( buffer , // resource
                           0 , // sub-resource
                           D3D11_MAP_WRITE_DISCARD , // type
                           0 , // flags
                           & mapping ); // mapped resource

    if( FAILED( result ) ) error_exit( L"Unable to map view matrix buffer." , result );

    memcpy( mapping.pData , & matrix , sizeof( XMMATRIX ) );

    context->Unmap( buffer ,
                    0u ); // sub-resource
}

void Camera::update()
{
    update_buffer( view_matrix_buffer.Get() , view_matrix );
    update_buffer( projection_matrix_buffer.Get() , projection_matrix );

    set_vertex_shader_buffers( 1 , 1 , view_matrix_buffer.GetAddressOf() );
    set_vertex_shader_buffers( 2 , 1 , projection_matrix_buffer.GetAddressOf() );
}

//void Camera::update_matrix_buffer_view(){}

void Camera::set_position( XMVECTOR const & position )
{
	this->position = position;

	view_matrix = XMMatrixLookAtLH( position , target , up );

	view_matrix = XMMatrixTranspose( view_matrix );
}

void Camera::set_z( float z )
{
	// can a position vector be derived from a view/position matrix?
	// XMMatrixDecompose
	
	position = XMVectorSetZ( position , z );

	view_matrix = XMMatrixLookAtLH( position , target , up );

	view_matrix = XMMatrixTranspose( view_matrix );
}

void Camera::set_delta_z( float delta_z )
{
}

void Camera::set_target( XMVECTOR const & target )
{
	this->target = target;

	view_matrix = XMMatrixLookAtLH( position , target , up );

	view_matrix = XMMatrixTranspose( view_matrix );
}

/*
    //----------------------update view matrix buffer()----------------------// ie a buffer ( inherits from D3DResource )
    device_context->UpdateSubresource( view_matrix_buffer.Get() , // ID3D11Resource destination
                                       0 , // zero-based index of destination subresource
                                       nullptr , // box that defines the portion of the destination subresource to copy the resource data into
                                       & view_matrix , // source data
                                       0 , // size of one row of the source data.
                                       0 ); // size of one depth slice of source data.

    //----------------------update projection_matrix_buffer----------------------// ie a buffer ( inherits from D3DResource )
    device_context->UpdateSubresource( projection_matrix_buffer.Get() ,	// ID3D11Resource destination
                                       0 , // zero-based index of destination subresource
                                       nullptr , // box portion of destination subresource to copy the resource data into
                                       & projection_matrix , // source data
                                       0 , // size of one row of the source data.
                                       0 ); // size of one depth slice of source data.
*/

