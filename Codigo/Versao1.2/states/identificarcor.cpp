#include "identificarcor.hpp"
#include "robotino.hpp"
//*****************************************************************************************************************
// IdentificarCor
//*****************************************************************************************************************

IdentificarCor  *IdentificarCor::instance()
{
    static IdentificarCor  IdentificarCorStateInstance;
    return &IdentificarCorStateInstance;
}

IdentificarCor::IdentificarCor() {}

IdentificarCor::~IdentificarCor() {}

void IdentificarCor::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IdentificarCor...\n";
}

void IdentificarCor::execute(Robotino *robotino)
{

}

void IdentificarCor::exit(Robotino *robotino) {}
