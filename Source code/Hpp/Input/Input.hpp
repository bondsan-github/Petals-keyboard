#pragma once


#include "Source code/Hpp/Custom types.hpp"
#include "Keys.hpp"
#include "Source code/Hpp/Patterns/Observable.hpp"

#include <string>
#include <map>

class Application;

class Input : public Observable
{
    private:

        Application & application;

    public:

        Input( Application & application );

        void on_key_pressed( uint windows_code );        
};






