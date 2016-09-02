#include "Girarstate.hpp"
#include "robotino.hpp"

#define Kp 1
#define limiar 5
//*****************************************************************************************************************
// Girar
//*****************************************************************************************************************
Girar  *Girar::instance()
{
    static Girar GirarStateInstance;
    return &GirarStateInstance;
}

Girar::Girar() {}

Girar::~Girar() {}

void Girar::enter(Robotino *robotino){
    std::cout << "Entrando no estado Girar...\n";

}

void Girar::execute(Robotino *robotino){
    // Fazer o controlador para o robô se manter no theta_r
    float w, erro = (robotino->odometryPhi() - robotino->theta_r);

    w = Kp*erro;
    robotino->setVelocity(0,0,w);

    if (erro < limiar){
             robotino->change_state(robotino->previous_state());
    }


}

void Girar::exit(Robotino *robotino) {}
