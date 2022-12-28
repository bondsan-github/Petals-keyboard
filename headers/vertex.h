#pragma once

#include <d2d1.h>

struct vertex
{
    vertex( D2D1_POINT_2F in_point )                : x( in_point.x ) , y( in_point.y ) { }
    vertex( float x_in = 0.0f , float y_in = 0.0f ) : x( x_in )       , y( y_in )       { }
    
    vertex & operator = ( vertex const & in_vertex ) // right variable
    {
        if( & in_vertex != this )
        {
            x = in_vertex.x;
            y = in_vertex.y;
        }

        return * this;
    }

    vertex operator + ( vertex const & in_vertex ) 
    { 
        return { x + in_vertex.x , y + in_vertex.y };
    }

    vertex operator - ( vertex const & in_vertex ) 
    {
        return { x - in_vertex.x , y - in_vertex.y };
    }

    vertex & operator += ( vertex const & in_vertex ) 
    {
        x += in_vertex.x;
        y += in_vertex.y;

        return * this;
    }

    vertex & operator -= ( vertex const & in_vertex ) 
    {
        x -= in_vertex.x; 
        y -= in_vertex.y;

        return * this;
    }

    operator D2D1_POINT_2F () 
    {
        D2D1_POINT_2F point;
        point.x = x;
        point.y = y;

        //return D2D1_POINT_2F( x , y );
        return point;
    }

    float x {};
    float y {};
};