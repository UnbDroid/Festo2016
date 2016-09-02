#include "girar.hpp"
#include "robotino.hpp"
#include <iostream>
#include <cmath>

#define Kp 1.91
#define Ki 1
#define limiar 5
#define dt 0.01
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
    static float erro_int = 0;
    std::cout << "Phi: " << robotino->odometryPhi() << "\n";
    std::cout << "Referencia: "<< robotino->theta_r << "\n";
    std::cout << "Erro: " << erro << "\n";
    erro_int += erro*dt;
    w = -Kp*erro-Ki*erro_int;
    robotino->setVelocity(0,0,w);

    if (std::abs(erro) < limiar){
             erro_int = 0;
             robotino->change_state(robotino->previous_state());
    }

}

void Girar::exit(Robotino *robotino) {
    std::cout << "Cheguei no theta_r...\n";
    robotino->setVelocity(0,0,0);
}
