#include "Input\Input.hpp"

Input::Input( Application & application )
: application{ application }
{

}

void Input::on_key_pressed( uint windows_code )
{
    if( windows_keys.contains( windows_code ) )
    {
        notify( windows_keys.at( windows_code ) );
    }

}