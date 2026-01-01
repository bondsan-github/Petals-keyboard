#pragma once

#include "Graphics\Direct2D\Drawable2D.h"
#include "Custom types.h"

#include <wrl\client.h>
using Microsoft::WRL::ComPtr;

#include <d2d1.h>
#include <d2d1helper.h>

#include "Graphics\Rectangle.h"
#include "Graphics\Direct2D\Drawable2D.h"
#include "Graphics\Direct2D\Factory2D.h"

class Rectangle2D : public Rectangle , public Drawable2D , public Factory2D
{
    private:

        float        line_width_ {};
        D2D1::ColorF line_colour_ { D2D1::ColorF( 1.0 , 1.0 , 1.0 , 1.0 ) };

        ComPtr< ID2D1SolidColorBrush > brush_ {};
        ComPtr< ID2D1StrokeStyle1 >    style_ {};

    public:
     
        Rectangle2D();

        void line_width( float width ) { line_width_ = width; }
        void line_colour( D2D1::ColorF colour );
        void draw();
};