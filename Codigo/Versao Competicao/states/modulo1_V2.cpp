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
#include "modulo1_V2.hpp"
#include "alinhartraseiro.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "ajustarnaslinhas.hpp"
#include "percorrerquadradoprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define VELBUSCA 20
#define QUANTIDADE_DESEJADA 6
//*****************************************************************************************************************
// Modulo1_V2
//*****************************************************************************************************************

Modulo1_V2  *Modulo1_V2::instance()
{
    static Modulo1_V2  Modulo1_V2StateInstance;
    return &Modulo1_V2StateInstance;
}

Modulo1_V2::Modulo1_V2() {}

Modulo1_V2::~Modulo1_V2() {}

void Modulo1_V2::enter(Robotino *robotino)
{
    //if(!c_Modulo1_V201) throw std::invalid_argument("Modulo1_V2 must have an owner to enter.");
    std::cout << "Entrando no Modulo1_V2...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void Modulo1_V2::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;

    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());


    if(objetivo_completo == 0){
       // robotino->adicionarCorFaltando(Robotino::AZUL);
        robotino->adicionarCorFaltando(Robotino::AZUL);
        robotino->adicionarCorFaltando(Robotino::VERMELHO);
        robotino->adicionarCorFaltando(Robotino::VERMELHO);
        robotino->adicionarCorFaltando(Robotino::AMARELO);
        robotino->adicionarCorFaltando(Robotino::AMARELO);

        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 1;
    }else if(objetivo_completo == 1){
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA1);
        robotino->definirDestino(destino.get_x()-20, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());

        objetivo_completo = 2;
    }else if(objetivo_completo == 2){
        robotino->definirParedeAlvo(999);
        robotino->setDistParede(1000);
        robotino->change_state(AndarPelaParedeAteLinha::instance());

        objetivo_completo = 3;
    }else if(objetivo_completo == 3){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 4;

    }else if(objetivo_completo == 4){

        robotino->setVelocidadeBusca(-180);
        robotino->change_state(PercorrerQuadradoProcurandoDiscos::instance());
        objetivo_completo = 5;

    }else if(objetivo_completo == 5){

        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 6;

    }else if(objetivo_completo == 6){

        std::cout << "Indo para Sul" << std::endl;
        robotino->definirParedeAlvo (Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 7;

    }else if(objetivo_completo == 7){
        robotino->definirParedeAlvo(Robotino::LESTE0);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());

        objetivo_completo = 8;
    }else if(objetivo_completo == 8){

        robotino->definirLinhaAlvo(129.5, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        robotino->setCarregando(false);
        discos_entregues++;

        objetivo_completo = 9;
    }else if(objetivo_completo == 9){

        robotino->definirDestino(robotino->odometryX()/10 - 30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());

        if(discos_entregues == QUANTIDADE_DESEJADA){
            objetivo_completo = 15;
        }else{
            objetivo_completo = 10;
        }


    }else if(objetivo_completo == 10){

        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 11;

    }else if(objetivo_completo == 11){

        robotino->definirParedeAlvo(Robotino::LESTE0);
        robotino->setDistTrasParede(20);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 12;

    }else if(objetivo_completo == 12){
        robotino->definirParedeAlvo(999);
        robotino->setDistParede(1000);
        robotino->change_state(AndarPelaParedeAteLinha::instance());

        objetivo_completo = 13;
    }else if(objetivo_completo == 13){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 14;

    }else if(objetivo_completo == 14){

        robotino->setVelocidadeBusca(180);
        robotino->change_state(PercorrerQuadradoProcurandoDiscos::instance());
        objetivo_completo = 5;

    }else if(objetivo_completo == 15){
        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());

        objetivo_completo = 16;

    }else if(objetivo_completo == 16){
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(7);
        robotino->change_state(IrParedePelaParede::instance());

        objetivo_completo = 17;
    }
    else if(objetivo_completo == 17){

        robotino->exit("Terminei");

    }
}

void Modulo1_V2::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}