#include "seguindoparede.hpp"
#include "robotino.hpp"
//*****************************************************************************************************************
// SeguindoParede
//*****************************************************************************************************************

SeguindoParede  *SeguindoParede::instance()
{
    static SeguindoParede  SeguindoParedeStateInstance;
    return &SeguindoParedeStateInstance;
}

SeguindoParede::SeguindoParede() {}

SeguindoParede::~SeguindoParede() {}

void SeguindoParede::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado SeguindoParede...\n";
}

void SeguindoParede::execute(Robotino *robotino)
{

}

void SeguindoParede::exit(Robotino *robotino) {}
