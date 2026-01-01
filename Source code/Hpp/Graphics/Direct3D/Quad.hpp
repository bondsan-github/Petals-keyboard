#pragma once

#include "Custom types.hpp"
#include "Input layouts.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Colour.hpp"

#include <DirectXMath.h>
//#include <wrl/client.h> // unique_pointer

#include <string>

class Quad : public Mesh //<input_layout_texture>
{
	public:

		explicit Quad();
        explicit Quad( std::wstring const & filename );
        explicit Quad( float width , float height , Colour const & colour );
		
		void load_diffuse( std::wstring const & filename );
        //void create_blank( uint width , uint height , Colour const & colour );
        
		float width()  const { return diffuse.width(); }
		float height() const { return diffuse.height(); }

		XMFLOAT2 size() const { return { diffuse.width() , diffuse.height() }; }

		//void line( XMFLOAT4 points , Colour colour ) { texture->line( points , colour ); }

		void update( double time_delta );
        
		void render();
        void reset();

		Texture get_diffuse() const { return diffuse; }

	private:

		float width_{};
		float height_{};
        Colour colour_ {};

        Input_layouts input_layout;
			
		Texture diffuse;
		//vector<Texture> textures
		//enum class Texture { diffuse , normal , ... }
		
		//DX11::Rectangle border;

				// Mesh mesh;	

		//rectangle get_border() 
		//{
		//	// find min x,y,z & max x,y,z

		//	//min.x = a.x < b.x ? a.x : b.x;  

		//	border.top		= get_position().y + ( height / 2.0f );
		//	border.bottom	= get_position().y - ( height / 2.0f );
		//	border.left		= get_position().x - ( width  / 2.0f );
		//	border.right	= get_position().x + ( width  / 2.0f );

		//	return border;
		//}
};

//normals required ?

		/*
		// copy constructor
		Quad_from_image( const Quad_from_image & in_move_from )
		{
			m_p_image = std::move( in_move_from.m_p_image );
		}

		// move constructor
		Quad_from_image( Quad_from_image && in_move_from )
		{
			m_p_image = std::move( in_move_from.m_p_image );
		}

		// move assignment operator
		Quad_from_image operator = ( Quad_from_image && in_move_from )
		{
			m_p_image = std::move( in_move_from.m_p_image );
		}
		*/
