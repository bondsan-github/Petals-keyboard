#pragma once

#include <d3d11.h>
#include <DirectXMath.h>// XM types

#include <vector>
#include <wrl/client.h> // ComPtr
#include <wincodec.h>	// WICImage
#include <memory>		// unique_ptr

#include "Custom types.hpp"
#include "WIC.hpp"
#include "Colour.hpp"

//using namespace DirectX; 
// ONLY in CPP files <- include in header will pollute global namespace

using Microsoft::WRL::ComPtr;
using DirectX::XMFLOAT4;
using std::wstring;
using std::vector;

// material
//enum class texture_type { diffuse , alpha , specular , displacement };
//template< typename pixel_format >

class Texture
{
	public:

		explicit Texture();
        //explicit Texture( const uint & width , const uint & height , const DirectX::PackedVector::XMCOLOR & colour );
		//Texture( const XMFLOAT2 in_dimensions , const XMFLOAT4 in_rgba );
		explicit Texture( const wstring & in_filename );

        ~Texture();

        void create_blank( float width , float height , Colour const & colour );
		void load( const wstring & filename );
		
		//void clear( const Colour in_colour ) {}

		//void plot( const uint & x , const uint & y , const XMUINT4 & colour );
		//void line( const  XMFLOAT4 & points , const XMUINT4 & colour );
        //void elipse( center_x, center_y, width, height, [pen] ) 

		float width()  const { return width_; } // ** get from view_description
		float height() const { return height_; }

		//void set_width( const uint & width )   { this->width = width; }
		//void set_height( const uint & height ) { this->height = height; }

		void update( double const & time_delta );
		
        //void update_pixel_shader_buffer();

		void render();

	private:
	   
		//void create_buffer( const uint & width , const uint & height , const XMUINT4 & colour );
		//void create_buffer( const void * ptr_memory , DXGI_FORMAT pixel_format ); //** vector<>
        void create_buffer();

		void set_pixel_shader_resources();

	private:

		HRESULT result { E_FAIL };

        ComPtr< ID3D11Device >        device;
		ComPtr< ID3D11DeviceContext > context;
		
		D3D11_USAGE	    usage		{ D3D11_USAGE_DEFAULT };//DYNAMIC }; // , _IMMUTABLE, _STAGING; 
		//DXGI_FORMAT     dxgi_format { DXGI_FORMAT_R16G16B16A16_FLOAT };
		DXGI_FORMAT	    dxgi_format	{ DXGI_FORMAT_B8G8R8A8_UNORM };
        //DXGI_FORMAT	    dxgi_format	{ DXGI_FORMAT_B8G8R8A8_UNORM_SRGB };
        //enum class type { diffuse };

        float           width_ {};
        float           height_ {};
        Colour          colour {};
        uint            bytes_per_pixel = 32;
		vector< float > pixels;
        //uchar		    bits_per_pixel { 4 }; // struct pixel_formats { DXGI_FORMAT ... , WIC , uchar bytespp };

		D3D11_TEXTURE2D_DESC               description {};
		D3D11_SUBRESOURCE_DATA             data {};

		D3D11_SHADER_RESOURCE_VIEW_DESC    view_description {};
		ComPtr< ID3D11ShaderResourceView > shader_resource_view{};

		ComPtr< ID3D11Texture2D >          texture {};

		WICImage                           image;

		D3D11_MAPPED_SUBRESOURCE           mapped_subresource {};
};

//Pixel( x,y, const & Pixel ) { }

/*
// copy assignment operator
WICImage operator = ( const WICImage & in_copy_from )
{
m_p_vector_image_data = std::move( in_copy_from.m_p_vector_image_data );
//						  ^
// unique_ptr< vector<uchar> > operator = ( const unique_ptr< vector<uchar> > & in_pointer ) = default_delete
}

// copy constructor
WICImage( const WICImage & in_copy_from )
{
m_p_vector_image_data = std::move( in_copy_from.m_p_vector_image_data );
}
*/

/*
class Textures
{
	public:
	//Textures();

	void load( const texture_type in_type , const wstring filename )
	{
		switch( in_type )
		{
			case texture_type::diffuse:
				break;
		}
	}

	void load( const texture_type in_type , const vector<Colour>& in_pixels )
	{
	}

	line()

	private:
	//texture_diffuse m_diffuse;
	//Texture alpha;
	//Texture m_specular;
	//Texture m_reflection;
	//Texture m_displacement;

};
*/

/*
class texture_diffuse : public Texture
{
public:
virtual void load( const wstring filename )
{
}
};
*/

/*unsigned char pixels()
{
unsigned char * pixel_array = new unsigned char[ m_width * m_height * 4 ];

for( int i = 0; i < m_width * m_height * 4; ++i )
{
pixel_array[ i ] = m_rgba[ i ].m_red;
}
}*/