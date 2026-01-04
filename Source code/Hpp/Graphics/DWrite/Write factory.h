#pragma once

#include <wrl\client.h>
#include <dwrite.h>

#include "Output\Logging.h"

class Write_factory
{
    protected:

        Microsoft::WRL::ComPtr<IDWriteFactory> factory_write {};

    public:

        Write_factory()
        {
            if( not factory_write )
            {
                DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED ,
                                        __uuidof( IDWriteFactory ) ,
                                        &factory_write );// >> result_check;
            }
        }

        ~Write_factory()
        {
            if( factory_write ) { factory_write->Release(); }
        }
};
