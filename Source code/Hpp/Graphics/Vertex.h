#pragma once

#include <d2d1.h>

struct Vertex
{
    Vertex( D2D1_POINT_2F point ) : x( point.x ) , y( point.y ) { }
    Vertex( float x = 0.0f , float y = 0.0f ) : x( x ) , y( y ) { }
    
    Vertex & operator = ( Vertex const & in_vertex ) // right variable
    {
        if( & in_vertex != this )
        {
            x = in_vertex.x;
            y = in_vertex.y;
        }

        return * this;
    }

    Vertex operator + ( Vertex const & in_vertex ) 
    { 
        return { x + in_vertex.x , y + in_vertex.y };
    }

    Vertex operator - ( Vertex const & in_vertex ) 
    {
        return { x - in_vertex.x , y - in_vertex.y };
    }

    Vertex & operator += ( Vertex const & in_vertex ) 
    {
        x += in_vertex.x;
        y += in_vertex.y;

        return * this;
    }

    Vertex & operator -= ( Vertex const & in_vertex ) 
    {
        x -= in_vertex.x; 
        y -= in_vertex.y;

        return * this;
    }

    operator D2D1_POINT_2F () const
    {
        //D2D1_POINT_2F point {};
        //point.x = x;
        //point.y = y;

        return { x , y };
    }

    float x {};
    float y {};
};