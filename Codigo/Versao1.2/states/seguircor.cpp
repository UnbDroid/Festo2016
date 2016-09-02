#include "basestate.hpp"
#include "robotino.hpp"
//*****************************************************************************************************************
// Base
//*****************************************************************************************************************

Base  *Base::instance()
{
    static Base  BaseStateInstance;
    return &BaseStateInstance;
}

Base::Base() {}

Base::~Base() {}

void Base::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Base...\n";
}

void Base::execute(Robotino *robotino)
{

}

void Base::exit(Robotino *robotino) {}
