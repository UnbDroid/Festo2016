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
#include "modulo1.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define VELBUSCA 20
//*****************************************************************************************************************
// Modulo1
//*****************************************************************************************************************

Modulo1  *Modulo1::instance()
{
    static Modulo1  Modulo1StateInstance;
    return &Modulo1StateInstance;
}

Modulo1::Modulo1() {}

Modulo1::~Modulo1() {}

void Modulo1::enter(Robotino *robotino)
{
    //if(!c_Modulo101) throw std::invalid_argument("Modulo1 must have an owner to enter.");
    std::cout << "Entrando no Modulo1...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void Modulo1::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;

    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());


    if(objetivo_completo == 0){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->definirDestino(destino.get_x(), -destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 1;

    }else if (objetivo_completo == 1){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 2;

    }else if(objetivo_completo == 2){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));

        float erro = robotino->odometryPhi() + destino.get_theta();

        float w;

        std::cout << "ESSE ERRO AQUI: " << erro << "\n";

        if((erro > 0 && erro < 180) || (erro < -180)){
            w = -VELBUSCA;
        }
        if((erro < 0 && erro > -180) || (erro > 180)){
            w = VELBUSCA;
        }


        robotino->setVelocidadeBusca(w);
        robotino->definirCorAlvo(Robotino::VERMELHO);
        robotino->change_state(ProcurarCor::instance());
        objetivo_completo = 4;

    }else if(objetivo_completo == 4){

        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 5;

    }else if(objetivo_completo == 5){

        std::cout << "Indo para Sul" << std::endl;
        robotino->definirParedeAlvo (Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        if(robotino->irDistance(Robotino::IR_FRONTAL) > 20){
            objetivo_completo = 2;
        }else{
            objetivo_completo = 6;
        }

    }else if(objetivo_completo == 6){

        std::cout << "Indo para Leste" << std::endl;
        robotino->setDistParede(10);
        robotino->definirParedeAlvo (Robotino::LESTE0);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 7;

    }else if(objetivo_completo == 7){

        robotino->definirLinhaAlvo(149.5, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        robotino->setCarregando(false);
        discos_entregues++;
        objetivo_completo = 8;

    }else if(objetivo_completo == 8){

        if(robotino->odometryX() > 1400){
             robotino->setVelocity(-100,0,0);
        }else{
            robotino->setVelocity(0,0,0);
            if(discos_entregues == 2){
                objetivo_completo = 9;
            }else{
                robotino->setThetaR(90);
                robotino->change_state(Girar::instance());
                objetivo_completo = 0;
            }
        }

    }else if(objetivo_completo == 9){

        std::cout << "Indo para casa" << std::endl;
        robotino->setDistParede(6);
        robotino->definirParedeAlvo (Robotino::SUL90);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 10;

    }else if(objetivo_completo == 10){

        robotino->definirLinhaAlvo(-49.5, Robotino::VERTICAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 11;

    }else if(objetivo_completo == 11){
        std::cout << "Y: " << robotino->odometryY() << "\n";
        if(robotino->odometryY() < -200){
             robotino->setVelocity(100,0,0);
        }else{
            robotino->setVelocity(0,0,0);
            objetivo_completo = 12;
        }

    }else if(objetivo_completo == 12){
        robotino->exit("Terminei");
    }
    std::cout << "Discos entregues: " << discos_entregues << "\n";
    //robotino->update();
    //std::cout << test << "\n";
    std::cout << "Vendo na direita: " <<robotino->readColorSensor(Robotino::SC_DIREITO) << "\n";
    std::cout << "Vendo na esquerda: " <<robotino->readColorSensor(Robotino::SC_ESQUERDO) << "\n";
    std::cout << "Vendo no indutivo: " <<robotino->readInductiveSensor() << "\n";
    //cv::Mat img = robotino->getImage();
    //cv::Mat teste (img,cv::Rect(0,0,img.cols,img.rows - 10));
    //std::cout << img;
    //cv::imshow("Amor",img);
    //cv::waitKey(1);
    //std::cout << robotino->getImage();
}

void Modulo1::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}