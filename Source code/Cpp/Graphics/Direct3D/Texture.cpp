#include <array>

#include "Graphics\Texture.hpp"
#include "Locate.hpp"
#include "Graphics\Graphics.hpp"
#include "Logging.hpp"
//#include "DirectXPackedVector.h" // XMCOLOR
//#include "DirectXColors.h" // defined colours

Texture::Texture() 
{
     device = Locate::graphics().device();
     device->GetImmediateContext( & context );
}

/*
Texture::Texture( const uint & width , const uint & height , const DirectX::PackedVector::XMCOLOR & colour )
	: width( width ) , height( height )
{
    assert( width > 0u && height > 0u );

	pixels.clear();
	pixels.resize( width * height , 0u );

	//create_buffer();
}
*/

Texture::Texture( const wstring & filename )
{
    image.load( filename );

	create_buffer();
}

Texture::~Texture()
{
/*
    texture.Reset();
    shader_resource_view.Reset();
    context.Reset();
    */
}

void Texture::load( const wstring & filename )
{
    image.load( filename );

    create_buffer();
}

void Texture::create_blank( float width , float height , Colour const & colour )
{
    width_ = width;
    height_ = height;
    this->colour = colour;

    pixels.clear();
    //pixels.resize( static_cast< uint >( width_ ) * static_cast< uint >( height_ ) * bytes_per_pixel );
    pixels.resize( static_cast< uint >( width_ ) * static_cast< uint >( height_ ) * 16 );
    // float = 32 / 8 = 4 bytes , 4 * 4 = 16 bytes
    //std::fill(pixels.begin() , pixels.end(), 1.0f);
    
    std::array< float, 4 > fill_colour = colour;

    float * first = pixels.data();
    float * last  = first + pixels.size();

    while( first != last ) first = copy( begin( fill_colour ) , end( fill_colour ) , first );

    description.Width              = static_cast< uint >( width_ );
    description.Height             = static_cast< uint >( height_ );
    description.MipLevels          = 1;
    description.ArraySize          = 1;
    description.Format             = dxgi_format;
    description.SampleDesc.Count   = 1;
    description.SampleDesc.Quality = 0;
    description.Usage              = usage;
    description.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
    description.CPUAccessFlags     = 0;//D3D11_CPU_ACCESS_WRITE; // read // write to modify
    description.MiscFlags          = 0;

    data.pSysMem					= pixels.data();
    data.SysMemPitch				= static_cast< uint >( width_ ) * sizeof( Colour );
    data.SysMemSlicePitch			= data.SysMemPitch * static_cast< uint >( height_ );

    result = Locate::graphics().device()->CreateTexture2D( & description ,
                                                           & data ,	// initial data
                                                           & texture );

    if( FAILED( result ) ) error_exit( L"Unable to create texture." , result );

    view_description.Format                    = dxgi_format;
    view_description.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
    view_description.Texture2D.MostDetailedMip = 0u;	// number of mips - 1;
    view_description.Texture2D.MipLevels       = 1u;

    result = Locate::graphics().device()->CreateShaderResourceView( texture.Get() ,
                                                                    & view_description ,
                                                                    & shader_resource_view );

    if( FAILED( result ) ) error_exit( L"Unable to create shader resource view." );

    //set_debug_name();

    D3D_SET_OBJECT_NAME_W( texture , L"texture 2d" );
}

void Texture::create_buffer() 
{
    width_  = image.width();
    height_ = image.height();

    // bool use_image_dimensions
    description.Width              = ceil( width_ );
    description.Height             = ceil( height_ );
	description.MipLevels          = 1;
	description.ArraySize          = 1;
	description.Format             = dxgi_format;
	description.SampleDesc.Count   = 1;
	description.SampleDesc.Quality = 0;
	description.Usage              = usage;
	description.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
    // if( usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC )
	//description.CPUAccessFlags     = 0;//D3D11_CPU_ACCESS_WRITE;
	//description.MiscFlags          = 0;

    // 2D : You set SysMemPitch to the distance between any two adjacent pixels on different lines. 
    //		You set SysMemSlicePitch to the size of the entire 2D surface in bytes. 
    //		To access a specific pixel, you use: (const char*)pSysMem + SysMemPitch*y + (x * BytesPerPixel)

    //unsigned int array_rgba[ 100 * 100 * 4 ] = { 255u , 0u , 0u , 0u };
    //memset( array_rgba , 255 , 100 * 100 * 4 );  // 255+255+255+255

    //******************************************* C26815
	data.pSysMem					= image.pixels();
	data.SysMemPitch				= ceil( width_ ) * 4;//image.channel_count();//image.bits_per_pixel();
	//data.SysMemSlicePitch			= ceil( width_ ) * image.channel_count() * ceil( height_ );
	data.SysMemSlicePitch			= ceil( width_ ) * 4 * ceil( height_ );

    result = device->CreateTexture2D( & description ,
                                      & data ,	// initial data
                                      & texture );

	if( FAILED( result ) ) error_exit( L"Texture::create_buffer() error; CreateTexture2D" , result  );

	view_description.Format                    = dxgi_format;
	view_description.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	view_description.Texture2D.MostDetailedMip = 0u;	// number of mips - 1;
	view_description.Texture2D.MipLevels       = 1u;

    result = device->CreateShaderResourceView( texture.Get() ,
                                               & view_description ,
                                               & shader_resource_view );

	if( FAILED( result ) ) error_exit( L"Texture::create_buffer() error; CreateShaderResourceView" );

    D3D_SET_OBJECT_NAME_W( texture , L"Texture 2D" );
}

/* void Texture::plot( const uint in_x , const uint in_y , const XMFLOAT4 in_colour )
{
	if( in_x >= 0 && in_y >= 0 && in_x <= width && in_y <= height )
	{
		int index = ( in_y * width ) + in_x;

		pixels.at( index ) = in_colour;
	}
}*/

/* void Texture::line( const XMFLOAT4 in_points , const XMFLOAT4 in_colour )
{
	int x1 = in_points.x;
	int y1 = in_points.y;
	int x2 = in_points.z;
	int y2 = in_points.w;

	// Bresenham's line algorithm
	const bool steep = ( fabs( y2 - y1 ) > fabs( x2 - x1 ) );
	if( steep )
	{
		std::swap( x1 , y1 );
		std::swap( x2 , y2 );
	}

	if( x1 > x2 )
	{
		std::swap( x1 , x2 );
		std::swap( y1 , y2 );
	}

	const float dx = x2 - x1;
	const float dy = fabs( y2 - y1 );

	float error = dx / 2.0f;
	const int ystep = ( y1 < y2 ) ? 1 : -1;
	int y = y1;

	const int maxX = x2;

	for( int x = x1; x < maxX; x++ )
	{
		if( steep )
		{
			plot( y , x , in_colour );
		} else
		{
			plot( x , y , in_colour );
		}

		error -= dy;

		if( error < 0 )
		{
			y += ystep;
			error += dx;
		}
	}

	update_PS_buffer();
}
*/

void Texture::set_pixel_shader_resources()
{
    context->PSSetShaderResources( 0 , // PS resource slot
                                   1 , // count of resources
                                   shader_resource_view.GetAddressOf() );

    // void set_diffuse_map( ID3D11Texture2D & diffuse_map );
}

void Texture::update( double const & time_delta )
{
    
}

void Texture::render()
{
    set_pixel_shader_resources();
}

/*
void Texture::update_pixel_shader_buffer()//_PS_buffer()
{
    Locate::get_graphics().get_device()->GetImmediateContext( &device_context );

	device_context->Map( texture.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , & mapped_subresource );
	//D3D11_MAP_FLAG_DO_NOT_WAIT 

	uint pitch_row		= mapped_subresource.RowPitch;
	uint pitch_height	= mapped_subresource.DepthPitch;

	unsigned char * destination = reinterpret_cast< unsigned char * >( mapped_subresource.pData );
	//Colour * destination = reinterpret_cast< Colour * >( mapped_subresource.pData );

	// for each row
	for( unsigned int row = 0; row < height; ++row )
	{							
		memcpy( destination + ( row * pitch_row ) , pixels.data() + ( row * static_cast<int>(width) ) , static_cast<int>(width) * pixels.bits_per_pixel );
	}

	device_context->Unmap( texture.Get() , 0 );
}
*/