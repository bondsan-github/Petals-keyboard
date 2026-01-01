#pragma once

#include <array>

#include <DirectXMath.h>

using DirectX::XMFLOAT4;

class Colour
{
    private:
        
        float red_ {};
        float green_ {};
        float blue_ {};
        float alpha_ {};

    public:

        explicit Colour() {}
        explicit Colour( float red , float green , float blue , float alpha = 1.0f )
            : red_( red ) , green_( green ) , blue_( blue ) , alpha_( alpha )
        {
        }

        operator XMFLOAT4() const { return { red_ , green_ , blue_ , alpha_ }; }

        operator std::array< float , 4 >() const { return { red_ , green_ , blue_ , alpha_ }; }
  
        //__declspec(property(get=get_*, put=set_*)) float [component];

        float red()   const { return red_; }
        float green() const { return green_; }
        float blue()  const { return blue_; }
        float alpha() const { return alpha_; }

        float red( float value )   { red_ = value; }
        float green( float value ) { green_ = value; }
        float blue( float value )  { blue_ = value; }
        float alpha( float value ) { alpha_ = value; }
};


