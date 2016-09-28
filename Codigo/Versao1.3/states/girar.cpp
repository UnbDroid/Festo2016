#include "girar.hpp"
#include "robotino.hpp"

//#include "rec/core_lt/Timer.h"

#include <iostream>
#include <cmath>
#include <unistd.h>

#define Kp 0.95//1.91 // girar sem disco
#define Ki 1
#define Kp2 0.4 //0.2 //girar com disco
#define Ki2 0.1
#define Kpx 20//75 //se aproximar quando disco foge
#define Kix 10
#define refDist 9.5
#define limiar 2
#define limiar2 2
#define dt 0.01
#define AumentoDisco 1.0
#define DiminuiDisco 1.0
#define SomaDisco 0
#define Aumento 0.90
#define Diminui 1.1
#define Soma 4

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
    if(robotino->deveGirar()){
        float Vx, w;
        static float erro = 0 , erro_int = 0, erro_intDist = 0, limiar3, fatorM = 1, fatorAdd = 0;

        if(robotino->carregandoDisco()){

            std::cout << "Phi: " << robotino->odometryPhi() << "\n";
            std::cout << "Referencia: "<< robotino->thetaR << "\n";
            std::cout << "Erro: " << erro << "\n";
            std::cout << "Dt: " << dt <<"\n";
            float erroDist = robotino->irDistance(Robotino::IR_FRONTAL) - refDist;
            std::cout << "Erro dist: " << erroDist <<"\n";

            std::cout << "Erro do sinal: " << erro << "\n";
            bool mudarDir = false;
            if(erro == 0){
                erro = robotino->odometryPhi() - robotino->thetaR;
                if (erro >180) {
                    erro -= 360;
                    mudarDir = true;
                }else if (erro <= -180){
                    erro += 360;
                    mudarDir = true;
                }
                if(erro > 0){
                    if(robotino->odometryPhi() > 0){
                        if(robotino->thetaR > 0){
                            fatorM = DiminuiDisco;
                        }else if(robotino->thetaR < 0){
                            fatorM = AumentoDisco;
                        }else{
                            fatorAdd = -SomaDisco;
                        }
                    }else if(robotino->odometryPhi() < 0){
                        if(robotino->thetaR > 0){
                            fatorM = DiminuiDisco;
                        }else if(robotino->thetaR < 0){
                            fatorM = AumentoDisco;
                        }else{
                            fatorAdd = SomaDisco;
                        }
                    }else{
                        if(robotino->thetaR > 0){
                            fatorM = AumentoDisco;
                        }else if(robotino->thetaR < 0){
                            fatorM = AumentoDisco;
                        }else{
                            fatorAdd = SomaDisco;
                        }
                    }
                }else if(erro < 0){
                    if(robotino->odometryPhi() > 0){
                        if(robotino->thetaR > 0){
                            fatorM = AumentoDisco;
                        }else if(robotino->thetaR < 0){
                            fatorM = DiminuiDisco;
                        }else{
                            fatorAdd = -SomaDisco;
                        }
                    }else if(robotino->odometryPhi() < 0){
                        if(robotino->thetaR > 0){
                            fatorM = AumentoDisco;
                        }else if(robotino->thetaR < 0){
                            fatorM = DiminuiDisco;
                        }else{
                            fatorAdd = SomaDisco;
                        }
                    }else{
                        if(robotino->thetaR > 0){
                            fatorM = AumentoDisco;
                        }else if(robotino->thetaR < 0){
                            fatorM = AumentoDisco;
                        }else{
                            fatorAdd = SomaDisco;
                        }
                    }
                }
                std::cout << "------------("<<robotino->thetaR<<")"<<robotino->odometryPhi()<<"-------------("<<erro<<")-------------------------------"<<fatorM<<"\n";
            }

            if(erro != 0){
                if(robotino->thetaR != 0){
                    erro = (robotino->odometryPhi() - robotino->thetaR*fatorM);
                }else{
                    erro = (robotino->odometryPhi() - (robotino->thetaR+fatorAdd));
                }
            }

            if(std::abs(robotino->odometryPhi() - robotino->thetaR) >= 180){
                mudarDir = true;
            }

            if (erro >180 ) {
                erro -= 360;
                mudarDir = false;
            }else if (erro <= -180){
                erro += 360;
                mudarDir = false;
            }

            if(mudarDir){
                erro *= -1;
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
                     usleep(500000);
                     robotino->setOdometry(robotino->odometryX(),robotino->odometryY(),robotino->thetaR);
                     robotino->change_state(robotino->previous_state());
                     robotino->girei();
            }
        }else{
            std::cout << "Erro do sinal: " << erro << "\n";
            bool mudarDir = false;
            if(erro == 0){
                erro = robotino->odometryPhi() - robotino->thetaR;
                if (erro >180) {
                    erro -= 360;
                    mudarDir = true;
                }else if (erro <= -180){
                    erro += 360;
                    mudarDir = true;
                }
                if(erro > 0){
                    if(robotino->odometryPhi() > 0){
                        if(robotino->thetaR > 0){
                            fatorM = Diminui;
                        }else if(robotino->thetaR < 0){
                            fatorM = Aumento;
                        }else{
                            fatorAdd = -Soma;
                        }
                    }else if(robotino->odometryPhi() < 0){
                        if(robotino->thetaR > 0){
                            fatorM = Diminui;
                        }else if(robotino->thetaR < 0){
                            fatorM = Aumento;
                        }else{
                            fatorAdd = 6;
                        }
                    }else{
                        if(robotino->thetaR > 0){
                            fatorM = Aumento;
                        }else if(robotino->thetaR < 0){
                            fatorM = Aumento;
                        }else{
                            fatorAdd = 0;
                        }
                    }
                }else if(erro < 0){
                    if(robotino->odometryPhi() > 0){
                        if(robotino->thetaR > 0){
                            fatorM = Aumento;
                        }else if(robotino->thetaR < 0){
                            fatorM = Diminui;
                        }else{
                            fatorAdd = -Soma;
                        }
                    }else if(robotino->odometryPhi() < 0){
                        if(robotino->thetaR > 0){
                            fatorM = Aumento;
                        }else if(robotino->thetaR < 0){
                            fatorM = Diminui;
                        }else{
                            fatorAdd = 6;
                        }
                    }else{
                        if(robotino->thetaR > 0){
                            fatorM = Aumento;
                        }else if(robotino->thetaR < 0){
                            fatorM = Aumento;
                        }else{
                            fatorAdd = 0;
                        }
                    }
                }
                std::cout << "------------("<<robotino->thetaR<<")"<<robotino->odometryPhi()<<"-------------("<<erro<<")-------------------------------"<<fatorM<<"\n";
            }

            if(erro != 0){
                if(robotino->thetaR != 0){
                    erro = (robotino->odometryPhi() - robotino->thetaR*fatorM);
                }else{
                    erro = (robotino->odometryPhi() - (robotino->thetaR+fatorAdd));
                }
            }

            if(std::abs(robotino->odometryPhi() - robotino->thetaR) >= 180){
                mudarDir = true;
            }

            if (erro >180 ) {
                erro -= 360;
                mudarDir = false;
            }else if (erro <= -180){
                erro += 360;
                mudarDir = false;
            }

            if(mudarDir){
                erro *= -1;
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

                     usleep(500000);
                     robotino->setOdometry(robotino->odometryX(),robotino->odometryY(),robotino->thetaR);
                     robotino->change_state(robotino->previous_state());
                     robotino->girei();
            }
        }
    }else{
        robotino->change_state(robotino->previous_state());
    }
}

void Girar::exit(Robotino *robotino) {
    std::cout << "Cheguei no thetaR...\n";
    robotino->setVelocity(0,0,0);
}
