#pragma once

#include "..\headers\direct_2d.h"
#include "..\headers\locate.h"
#include "..\headers\line_d2d.h"
#include "..\headers\graphics_d2d.h"

namespace hid
{
    class grid_d2d //                                                                                                                                                                                                                                                                                                                                          : public service
    {
        private:
    
            page_dips          area        {};
            dimensions         cell_amount {};
            vector< line_d2d > lines       {};

        public:

            void       initialise    ( uint in_column_amount = 10 , uint in_row_amount = 10 );
            vertex     cell_position ( uint in_column , uint in_row );
            dimensions cell_size     ();
            void       draw          ();
    };

} 