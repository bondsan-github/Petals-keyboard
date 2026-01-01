#pragma once

#include <d2d1.h>

class Size
{
    private:

        int width_{ };
        int height_{ };

    public:

        Size();
        Size( int width , int height );

        explicit operator bool() const;
        bool     operator == ( Size const & size );
        bool     operator != ( Size const & size );
        Size &   operator += ( float in_size );
        bool     operator < ( Size const & in_rectangle );
        
        // conversion
        operator D2D1_SIZE_U ();
        operator D2D1_SIZE_F ();
        operator RECT ();

        void width( int width );
        void height( int height );

        void width( float width );
        void height( float height );

        void width( long width );
        void height( long height );

        int  width() const;
        int  height() const;
};
