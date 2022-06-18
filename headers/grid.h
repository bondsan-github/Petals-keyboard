#pragma once

#include < vector >

#include < d2d1.h >

#include "..\headers\globals.h"
#include "..\headers\locate.h"
#include "..\headers\line.h"

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    class grid
    {
        private:
    
            area           sheet_size  {};
            divisions      dimensions  {};
            vector< line > lines       {};

        public:

        void initialise( float in_column_amount , float in_row_amount )
        {
            dimensions.width  = in_column_amount;
            dimensions.height = in_row_amount;
            sheet_size        = locate::graphics_ptr().sheet_ptr()->GetSize(); // size in dips

            float cell_width  = sheet_size.width / dimensions.width;
            float cell_height = sheet_size.height / dimensions.height;

            for( float x {} ; x <= sheet_size.width ; x += cell_width )
                for( float y {} ; y <= sheet_size.height ; y += cell_height )
                {
                   // horizontal
                    lines.emplace_back( point{ 0 , y } , point{ sheet_size.width , y } , 1.0f );
                    // vertical
                    lines.emplace_back( point{ x , 0 } , point{ x , sheet_size.height } , 1.0f );
                }
        };

        point cell( const uint column , const uint row )
        {
            return { column * cell_size().width , row * cell_size().height };
        }

        divisions cell_size() const
        {
            return { sheet_size.width / dimensions.width ,
                     sheet_size.height / dimensions.height };
        }

        void draw()
        {
            for( auto & line : lines ) line.draw();
        }
    };

} 