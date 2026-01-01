#include "Graphics\DirectXMath extension.hpp"

namespace DirectX
{
	// 3 & 3
	XMFLOAT3 operator * ( XMFLOAT3 in_lhs , float in_multiplier )  // make arguments references when optimising
	{
		XMFLOAT3 mulitple( 0.0f , 0.0f , 0.0f );

		mulitple.x = in_lhs.x * in_multiplier;
		mulitple.y = in_lhs.y * in_multiplier;
		mulitple.z = in_lhs.z * in_multiplier;

		return mulitple;
	}

	XMFLOAT3 operator + ( XMFLOAT3 in_lhs , XMFLOAT3 in_rhs )
	{
		// var1 + var2 + var3
		// operator + (var1 , var2 )

		XMFLOAT3 addition( 0.0f , 0.0f , 0.0f );

		addition.x = in_lhs.x + in_rhs.x;
		addition.y = in_lhs.y + in_rhs.y;
		addition.z = in_lhs.z + in_rhs.z;

		return addition;
	}

	XMFLOAT3 & operator += ( XMFLOAT3 & in_lhs , const XMFLOAT3 & in_rhs )
	{
		// lhs += rhs;
		// lhs.operator += ( rhs )
		
		in_lhs.x += in_rhs.x;
		in_lhs.y += in_rhs.y;
		in_lhs.z += in_rhs.z;

		return in_lhs;
	}

	XMFLOAT3 & operator -= ( XMFLOAT3 & in_lhs , const XMFLOAT3 & in_rhs )	// compound_assignment 
	{
		in_lhs.x -= in_rhs.x;
		in_lhs.y -= in_rhs.y;
		in_lhs.z -= in_rhs.z;

		return in_lhs;
	}

	//XMFLOAT3 operator /= ( XMFLOAT3 in_lhs , float divisor )
	//{
	//	XMFLOAT3 divide_and_assign = in_lhs;

	//	divide_and_assign.x /= divisor;
	//	divide_and_assign.y /= divisor;
	//	divide_and_assign.z /= divisor;

	//	return divide_and_assign;
	//}

	// return combined minimum components
	XMFLOAT3 minimum( XMFLOAT3 lhs , XMFLOAT3 rhs )
	{
		// if( lhs < rhs ) x = lhs else x = rhs

		XMFLOAT3 min( 0.0f , 0.0f , 0.0f );

		if( lhs.x < rhs.x ) min.x = lhs.x; else min.x = rhs.x;
		if( lhs.y < rhs.y ) min.y = lhs.y; else min.y = rhs.y;
		if( lhs.z < rhs.z ) min.z = lhs.z; else min.z = rhs.z;
		
		//min.x = lhs.x < rhs.x ? lhs.x : rhs.x; // lhs(1) , rhs(2) , x = 1 
		//min.y = lhs.y < rhs.y ? lhs.y : rhs.y; // lhs(2) , rhs(1) , x = 1 
		//min.z = lhs.z < rhs.z ? lhs.z : rhs.z;
		
		return min;
	}

	XMFLOAT3 maximum( XMFLOAT3 lhs , XMFLOAT3 rhs )
	{
		XMFLOAT3 max( 0.0f , 0.0f , 0.0f );
		// if lhs > rhs == true return lhs else return rhs
		max.x = lhs.x > rhs.x ? lhs.x : rhs.x; // lhs(1) , rhs(2) = 2
		max.y = lhs.y > rhs.y ? lhs.y : rhs.y; // lhs(2) , rhs(1) = 2 
		max.z = lhs.z > rhs.z ? lhs.z : rhs.z;

		return max;
	}

	// 3 & 2

	//XMFLOAT3 operator =  ( XMFLOAT2 in_rhs ) // 'Must be a member function' !
	//{
	//	XMFLOAT3 assign( 0 , 0 , 0 );
	//	return assign
	//}

	XMFLOAT3 operator + ( XMFLOAT3 in_lhs , XMFLOAT2 in_rhs )
	{
		XMFLOAT3 addition( 0.0f , 0.0f , 0.0f );

		addition.x = in_lhs.x + in_rhs.x;
		addition.y = in_lhs.y + in_rhs.y;
		addition.z = in_lhs.z;

		return addition;
	}

	

	XMFLOAT3 operator * ( XMFLOAT3 in_lhs , XMFLOAT2 in_rhs )
	{
		XMFLOAT3 mulitple( 0.0f , 0.0f , 0.0f );

		mulitple.x = in_lhs.x * in_rhs.x;
		mulitple.y = in_lhs.y * in_rhs.y;
		mulitple.z = 0.0f;

		return mulitple;
	}

	XMFLOAT3 & operator += ( XMFLOAT3 & in_lhs , XMFLOAT2 & in_rhs )
	{

		in_lhs.x += in_rhs.x;
		in_lhs.y += in_rhs.y;
		in_lhs.z  = in_lhs.z; // ** return lhs z **

		return in_lhs;
	}

	// 2 & 2
	XMFLOAT2 & operator += ( XMFLOAT2 & in_lhs , const XMFLOAT2 & in_rhs )
	{
		in_lhs.x += in_rhs.x;
		in_lhs.y += in_rhs.y;

		return in_lhs;
	}

	XMFLOAT2 & operator -= ( XMFLOAT2 & in_lhs , const XMFLOAT2 & in_rhs )
	{
		in_lhs.x -= in_rhs.x;
		in_lhs.y -= in_rhs.y;

		return in_lhs;
	}

	XMFLOAT2 operator * ( XMFLOAT2 in_lhs , XMFLOAT2 in_rhs )
	{
		XMFLOAT2 mulitple( 0.0f , 0.0f );

		mulitple.x = in_lhs.x * in_rhs.x;
		mulitple.y = in_lhs.y * in_rhs.y;

		return mulitple;
	}
}