#include "Source code/Hpp/Graphics/WIC/WICFactory.hpp"

#include "Source code/Hpp/Output/Logging.hpp"

WICFactory::WICFactory()
{
    if( not wic_factory )
    {
        CoCreateInstance( CLSID_WICImagingFactory2 ,
                          nullptr ,
                          CLSCTX_INPROC_SERVER ,
                          IID_PPV_ARGS( & wic_factory ) ) >> result_check;
    }
}

WICFactory::~WICFactory()
{
    wic_factory.Reset();
}