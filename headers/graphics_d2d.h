#pragma once

#include < windows.h >
#include < wrl.h >
#include < d2d1.h >

namespace hid
{
    using namespace std;
    using namespace D2D1;
    using namespace Microsoft::WRL;

    using factory_d2d = ID2D1Factory;
    using display     = PAINTSTRUCT;
    using colours     = ColorF;

    using window_render_target = ID2D1HwndRenderTarget;

    class graphics_d2d
    {
        private:

            ComPtr< factory_d2d >          factory_ptr  {};
            ComPtr< window_render_target > sheet_ptr    {};
            RECT                           dimensions   {};
            display                        client_area  {};
            colours                        colour_clear { 0.2f , 0.2f , 0.2f , 0.5f };
            //HRESULT                        result       { E_FAIL };

        public:

            void                   initialise();
            void                   reset();
            window_render_target * sheet();
            void                   draw();
            void                   resize();

        //void set_sheet( const ID2D1HwndRenderTarget * in_sheet )
        //sheets.emplace_back( window_ptr , size );

    }; // class graphics

} // namespace hid

 /*
         class sheet
         {
            enum class request_type { window_ptr , size };

            using window_ptr = ID2D1HwndRenderTarget *;
            using size    = D2D1_SIZE_F;

            window_ptr _sheet {};
            size    _size  {};

            public:

            sheet( window_ptr const in_sheet = {} , const size in_size = {} )
            : _sheet( in_sheet ) , _size( in_size )
            {}

            size    size()    const { return _size; }
            window_ptr window_ptr() const { return _sheet; }
         };
         */

         //vector< sheet > sheets {};