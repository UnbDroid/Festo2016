#include "control.hpp"
#include "robotino.hpp"
#include "classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "irparaponto.hpp"
#include "controleposicao.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "identificarcor.hpp"
#include "procurarcor.hpp"
#include "seguircor.hpp"
#include "irparaparede.hpp"
#include "irparalinha.hpp"
#include "modulo2.hpp"
#include <unistd.h>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define VELBUSCA 20
//*****************************************************************************************************************
// Modulo2
//*****************************************************************************************************************

Modulo2  *Modulo2::instance()
{
    static Modulo2  Modulo2StateInstance;
    return &Modulo2StateInstance;
}

Modulo2::Modulo2() {}

Modulo2::~Modulo2() {}

void Modulo2::enter(Robotino *robotino)
{
    //if(!c_Modulo202) throw std::invalid_argument("Modulo2 must have an owner to enter.");
    std::cout << "Entrando no Modulo 2...\n";
    //robotino->omniDrive.setVelocity(-200, 0 , 0 );
}

void Modulo2::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;

    if(objetivo_completo == 0){
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA4);//,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        std::cout <<"Resultado"<<destino<<"\n";
        robotino->definirDestino(destino.get_x()+40, -(destino.get_y()));
        robotino->setThetaR(170);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 1;
    }

 /*   static bool viMetal = false;
    std::cout << viMetal<<"\n";
    std::cout << robotino->readInductiveSensor()<<"\n--------------\n";
    if((robotino->readInductiveSensor() > 9.9 && !viMetal) || !robotino->readInductiveSensor()){
         robotino->setVelocity(20,0,0);
    }else{
        robotino->setVelocity(0,0,0);
        viMetal = true;
    }*/
}

void Modulo2::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}