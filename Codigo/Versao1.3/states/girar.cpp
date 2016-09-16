#include "girar.hpp"
#include "robotino.hpp"

//#include "rec/core_lt/Timer.h"

#include <iostream>
#include <cmath>

#define Kp 1.91
#define Ki 1
#define Kp2 0.2
#define Ki2 0.1
#define Kpx 20//75
#define Kix 10
#define refDist 9.5
#define limiar 0.5
#define limiar2 2
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
    // Fazer o controlador para o robô se manter no thetaR
    float Vx, w;
    static float erro = 0 , erro_int = 0, erro_intDist = 0, limiar3;

    if(robotino->carregandoDisco()){
        std::cout << "Phi: " << robotino->odometryPhi() << "\n";
        std::cout << "Referencia: "<< robotino->thetaR << "\n";
        std::cout << "Erro: " << erro << "\n";
        std::cout << "Dt: " << dt <<"\n";
        float erroDist = robotino->irDistance(Robotino::IR_FRONTAL) - refDist;
        std::cout << "Erro dist: " << erroDist <<"\n";

        std::cout << "Erro do sinal: " << erro << "\n";
        if(erro == 0){
            erro = robotino->odometryPhi() - robotino->thetaR;
        }
        if(erro > 0){
            if(robotino->thetaR != 0){
                erro = (robotino->odometryPhi() - robotino->thetaR*1.2);
            }else{
                erro = (robotino->odometryPhi() - (robotino->thetaR-12));
            }
        }else{
            if(robotino->thetaR != 0){
                erro = (robotino->odometryPhi() - robotino->thetaR*1.2);
            }else{
                erro = (robotino->odometryPhi() - (robotino->thetaR+12));
            }
        }
        if (erro >180 ) {
            erro -= 360;
        }else if (erro < -180){
            erro += 360;
        }

        erro_int += erro*dt;
        erro_intDist += erroDist*dt;
        w = -Kp2*erro-Ki2*erro_int;
        Vx = -Kpx*erroDist-Kix*erro_intDist;
        robotino->setVelocity(Vx,0,w);

        if (std::abs(erro) < limiar2){
                 erro = 0;
                 erro_int = 0;
                 erro_intDist = 0;
                 robotino->setOdometry(robotino->odometryX(),robotino->odometryY(),robotino->thetaR);
                 robotino->change_state(robotino->previous_state());
        }
    }else{
        std::cout << "Erro do sinal: " << erro << "\n";
        if(erro == 0){
            erro = robotino->odometryPhi() - robotino->thetaR;
        }
        if(erro > 0){
            if(robotino->thetaR != 0){
                erro = (robotino->odometryPhi() - robotino->thetaR*1.2);
            }else{
                erro = (robotino->odometryPhi() - (robotino->thetaR-12));
            }
        }else{
            if(robotino->thetaR != 0){
                erro = (robotino->odometryPhi() - robotino->thetaR*1.2);
            }else{
                erro = (robotino->odometryPhi() - (robotino->thetaR+6));
            }
        }
        if (erro >180 ) {
            erro -= 360;
        }else if (erro < -180){
            erro += 360;
        }
        erro_int += erro*dt;
        w = -Kp*erro-Ki*erro_int;
        robotino->setVelocity(0,0,w);

        std::cout << "Phi: " << robotino->odometryPhi() << "\n";
        std::cout << "Referencia: "<< robotino->thetaR << "\n";
        std::cout << "Erro: " << erro << "\n";
        std::cout << "Dt: " << dt <<"\n";
        std::cout << "Erro int: " << erro_int <<"\n";
        std::cout << "W: " << w <<"\n";


        if (std::abs(erro) < limiar){
                 erro_int = 0;
                 erro = 0;
                 robotino->setOdometry(robotino->odometryX(),robotino->odometryY(),robotino->thetaR);
                 robotino->change_state(robotino->previous_state());
        }
    }
}

void Girar::exit(Robotino *robotino) {
    std::cout << "Cheguei no thetaR...\n";
    robotino->setVelocity(0,0,0);
}
