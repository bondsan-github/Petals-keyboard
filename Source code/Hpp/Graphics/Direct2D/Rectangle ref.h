 // class rectangle
ID2D1SolidColorBrush * brush_rectangle{};
D2D1_SIZE_F         rectangle_size{ 0.0f , 0.0f };
static inline float rectangle_line_width{ 1.0f };
float               rectangle_inner_margin{ 5.0f };
D2D1::ColorF        rectangle_line_colour{ D2D1::ColorF::Yellow };

float               rounded_rectangle_radius{ 5.0f };
D2D1_ROUNDED_RECT   rounded_rectangle{ .radiusX = rounded_rectangle_radius ,
                                                .radiusY = rounded_rectangle_radius };


void GraphicsD2D::draw_rounded_rectangle( D2D_SIZE_F in_size ,
                                          vertex     in_position_top_left ,
                                          float      in_corner_radius ,
                                          ID2D1Brush * in_brush ,
                                          float        in_line_width )
                                          //colours in_colour )
{
    //if( page and in_brush )
    //{
    vertex            position{ in_position_top_left };
    D2D1_ROUNDED_RECT rectangle{};

    rectangle.radiusX = rectangle.radiusY = in_corner_radius;

    rectangle.rect.top    = position.y;
    rectangle.rect.right  = position.x + in_size.width;
    rectangle.rect.bottom = position.y + in_size.height;
    rectangle.rect.left   = position.x;


    page->DrawRoundedRectangle( rectangle ,
                                in_brush ,
                                in_line_width ,
                                0 );
//}