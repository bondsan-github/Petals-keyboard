#pragma once

#include <DirectXMath.h>

namespace DirectX
{
	// 3 & 3
	XMFLOAT3 operator *  ( XMFLOAT3 in_lhs , float in_multiplier );	// make arguments references when optimising	
	XMFLOAT3 operator +  ( XMFLOAT3 in_lhs , XMFLOAT3 in_rhs );
	XMFLOAT3 & operator += ( XMFLOAT3 & in_lhs , const XMFLOAT3 & in_rhs );	// compound_assignment 
	XMFLOAT3 & operator -= ( XMFLOAT3 & in_lhs , const XMFLOAT3 & in_rhs );	// compound_assignment 
	//XMFLOAT3 operator /= ( XMFLOAT3 in_lhs , float divisor );		// dividend is divided by the divisor to get a quotient

	// return combined minimum components
	XMFLOAT3 minimum( XMFLOAT3 lhs , XMFLOAT3 rhs );

	// return combined maximum components
	XMFLOAT3 maximum( XMFLOAT3 lhs , XMFLOAT3 rhs );

	// 3 & 2
	XMFLOAT3 operator +  ( XMFLOAT3 in_lhs , XMFLOAT2 in_rhs );
	XMFLOAT3 operator *  ( XMFLOAT3 in_lhs , XMFLOAT2 in_rhs );
	XMFLOAT3 & operator += ( XMFLOAT3 & in_lhs , XMFLOAT2 & in_rhs );

	// 2 & 2
	XMFLOAT2 & operator +=  ( XMFLOAT2 & in_lhs , const XMFLOAT2 & in_rhs );
	XMFLOAT2 & operator -=  ( XMFLOAT2 & in_lhs , const XMFLOAT2 & in_rhs );
	XMFLOAT2 operator *  ( XMFLOAT2 in_lhs , XMFLOAT2 in_rhs );
}