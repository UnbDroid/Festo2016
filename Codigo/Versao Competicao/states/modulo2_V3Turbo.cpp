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
#include "modulo2_V3Turbo.hpp"
#include "ajustarnaslinhas.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include <unistd.h>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define VELBUSCA 20
#define OBJETIVOAREA1 25
#define OBJETIVOAREA2 28
#define OBJETIVOAREA3 30
#define DISCOSAENTREGAR 6
//*****************************************************************************************************************
// Modulo2_V3Turbo
//*****************************************************************************************************************

Modulo2_V3Turbo  *Modulo2_V3Turbo::instance()
{
    static Modulo2_V3Turbo  Modulo2_V3TurboStateInstance;
    return &Modulo2_V3TurboStateInstance;
}

Modulo2_V3Turbo::Modulo2_V3Turbo() {}

Modulo2_V3Turbo::~Modulo2_V3Turbo() {}

void Modulo2_V3Turbo::enter(Robotino *robotino)
{
    //if(!c_Modulo2_V3Turbo02) throw std::invalid_argument("Modulo2_V3Turbo must have an owner to enter.");
    std::cout << "Entrando no Modulo 2_V2...\n";
    //robotino->omniDrive.setVelocity(-200, 0 , 0 );
}

/*
    Se certificar que ele entregue o disco completamente
*/

int decidirQualAreaIrV3Turbo(Robotino * robotino){

    static bool area1disco1Entregue = false;
    static bool area2disco2Entregue = false;
    static bool area3disco1Entregue = false;
    static bool area1disco2Entregue = false;
    static bool area2disco1Entregue = false;
    static bool area3disco2Entregue = false;

    std::cout<< "Area1Entregue: " << area1disco1Entregue<< std::endl;
    std::cout<< "Area2Entregue: " << area2disco2Entregue<< std::endl;
    std::cout<< "Area3Entregue: " << area3disco1Entregue<< std::endl;
    std::cout<< "Area1Entregue: " << area1disco2Entregue<< std::endl;
    std::cout<< "Area2Entregue: " << area2disco1Entregue<< std::endl;
    std::cout<< "Area3Entregue: " << area3disco2Entregue<< std::endl;

    robotino->definirObjetoAlvo(Robotino::TODAS);

    std::cout<< "Cor a ser entregue: " << robotino->objetoAlvo.getType() << std::endl;



    if (robotino->objetoAlvo.getType() == "yellow" ){

        std::cout<< "seguindo amarelo " << std::endl;
        if(robotino->area1disco1.getType() == "yellow"  && area1disco1Entregue == false){
            area1disco1Entregue = true;
            return OBJETIVOAREA1;
        }else if(robotino->area2disco1.getType() == "yellow" && area2disco1Entregue == false){
            area2disco1Entregue = true;
            return OBJETIVOAREA2;
        }else if(robotino->area3disco1.getType() == "yellow"  &&  area3disco1Entregue == false){
            area3disco1Entregue = true;
            return OBJETIVOAREA3;
        }else if(robotino->area1disco2.getType() == "yellow"  && area1disco2Entregue == false){
            area1disco2Entregue = true;
            return OBJETIVOAREA1;
        }else if(robotino->area2disco2.getType() == "yellow" && area2disco2Entregue == false){
            area2disco2Entregue = true;
            return OBJETIVOAREA2;
        }else if(robotino->area3disco2.getType() == "yellow"  &&  area3disco2Entregue == false){
            area3disco2Entregue = true;
            return OBJETIVOAREA3;
        }

    }else if (robotino->objetoAlvo.getType() == "blue" ){

        //robotino->definirObjetoAlvo(Robotino::AZUL);
        std::cout<< "seguindo azul " << std::endl;
        if(robotino->area1disco1.getType() == "blue"  && area1disco1Entregue == false){
            area1disco1Entregue = true;
            return OBJETIVOAREA1;
        }else if(robotino->area2disco1.getType() == "blue" && area2disco1Entregue == false){
            area2disco1Entregue = true;
            return OBJETIVOAREA2;
        }else if(robotino->area3disco1.getType() == "blue"  &&  area3disco1Entregue == false){
            area3disco1Entregue = true;
            return OBJETIVOAREA3;
        }else if(robotino->area1disco2.getType() == "blue"  && area1disco2Entregue == false){
            area1disco2Entregue = true;
            return OBJETIVOAREA1;
        }else if(robotino->area2disco2.getType() == "blue" && area2disco2Entregue == false){
            area2disco2Entregue = true;
            return OBJETIVOAREA2;
        }else if(robotino->area3disco2.getType() == "blue"  &&  area3disco2Entregue == false){
            area3disco2Entregue = true;
            return OBJETIVOAREA3;
        }

    }else if (robotino->objetoAlvo.getType() == "red"){

        //robotino->definirObjetoAlvo(Robotino::VERMELHO);
        std::cout<< "seguindo vermelho " << std::endl;
        if(robotino->area1disco1.getType() == "red"  && area1disco1Entregue == false){
            area1disco1Entregue = true;
            return OBJETIVOAREA1;
        }else if(robotino->area2disco1.getType() == "red" && area2disco1Entregue == false){
            area2disco1Entregue = true;
            return OBJETIVOAREA2;
        }else if(robotino->area3disco1.getType() == "red"  &&  area3disco1Entregue == false){
            area3disco1Entregue = true;
            return OBJETIVOAREA3;
        }else if(robotino->area1disco2.getType() == "red"  && area1disco2Entregue == false){
            area1disco2Entregue = true;
            return OBJETIVOAREA1;
        }else if(robotino->area2disco2.getType() == "red" && area2disco2Entregue == false){
            area2disco2Entregue = true;
            return OBJETIVOAREA2;
        }else if(robotino->area3disco2.getType() == "red"  &&  area3disco2Entregue == false){
            area3disco2Entregue = true;
            return OBJETIVOAREA3;
        }

    }
}



void Modulo2_V3Turbo::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int areaIr = 0;
    std::cout << "objetivo_completo = " << objetivo_completo << std::endl;

// Aqui comeca o modulo 2 Indo para a area de deposito 3 identificar a cor -------------------------------------------------------------------------------------

    if(objetivo_completo == 0){

        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 1;

    }else if(objetivo_completo == 1){

        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistParede(15);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 2;

    }else if(objetivo_completo == 2){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 3;

    }else if (objetivo_completo == 3){

        robotino->setAreaDeposito(Robotino::AREA4);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 4;

    }else if (objetivo_completo == 4){

        std::cout << "Disco 1 da cor: " << robotino->area3disco1.getType() << "\n";
        std::cout << "Disco 2 da cor: " << robotino->area3disco2.getType() << "\n";
        //identificarCorFaltandoArea3(robotino);
        objetivo_completo = 5;

    }

// Indo para a area de deposito 2 identificar a cor -----------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 5) {

        robotino->definirDestino((robotino->odometryX())/10, robotino->odometryY()/10 - 50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 6;

    }else if (objetivo_completo == 6){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);
        robotino->definirDestino(destino.get_x(), robotino->odometryY()/10);
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 7;

    }else if (objetivo_completo == 7){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 8;

    }else if (objetivo_completo == 8){
        robotino->setAreaDeposito(Robotino::AREA3);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 9;

    }else if (objetivo_completo == 9){
        std::cout << "Disco 1 da cor: " << robotino->area2disco1.getType() << "\n";
        std::cout << "Disco 2 da cor: " << robotino->area2disco2.getType() << "\n";
        //identificarCorFaltandoArea2(robotino);
        objetivo_completo = 10;

    }

// Indo para a area de deposito 1 identificar a cor ------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 10) {

        robotino->definirDestino((robotino->odometryX())/10, robotino->odometryY()/10 - 50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 11;

    }else if (objetivo_completo == 11){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2);
        robotino->definirDestino(destino.get_x(), robotino->odometryY()/10);
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 12;

    }else if (objetivo_completo == 12){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 13;

    }else if (objetivo_completo == 13){
        robotino->setAreaDeposito(Robotino::AREA2);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 14;

    }else if (objetivo_completo == 14){
        std::cout << "Disco 1 da cor: " << robotino->area1disco1.getType() << "\n";
        std::cout << "Disco 2 da cor: " << robotino->area1disco2.getType() << "\n";
        //identificarCorFaltandoArea1(robotino);
        objetivo_completo = 15;

    }

// Parte que ve os discos e decide onde ir -----------------------------------------------------------------------------------------------------------------------

   else if (objetivo_completo == 15) {

        if(discos_entregues < DISCOSAENTREGAR){
            robotino->definirParedeAlvo(Robotino::NORTEN90);
            robotino->setDistParede(10);                                        // MUDOU A DISTPAREDE DA VERSAO 1
            robotino->change_state(IrParaParede::instance());

            if(discos_entregues >= 4){
                objetivo_completo = 19;

            }else{
                objetivo_completo = 16;
            }

        }else{
            objetivo_completo = 37;  // IR PARA CASA AQUI
        }

    }else if (objetivo_completo == 16) {

        robotino->setDistParede(10);
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->definirLinhaAlvo(-238.5, Robotino::VERTICAL); // COORDENADAS ESTANHAS REVER
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        if(discos_entregues >= 2){
            objetivo_completo = 17;
        }else{
            objetivo_completo = 21; // Identificar Cor
        }

    }else if (objetivo_completo == 17) {

        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-15);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 18;

    }else if (objetivo_completo == 18) {

        robotino->setDistParede(10);
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->definirLinhaAlvo(-294.5, Robotino::VERTICAL); // COORDENADAS ESTANHAS REVER
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        objetivo_completo = 21; // Identificar Cor

    }else if (objetivo_completo == 19) {

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 20;

    }else if (objetivo_completo == 20) {

        robotino->setDistParede(6);
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->definirLinhaAlvo(148.5, Robotino::HORIZONTAL); // COORDENADAS ESTANHAS REVER
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());

        objetivo_completo = 21; // Identificar Cor

    }

    else if (objetivo_completo == 21){

        robotino->setVelocity(0,50,0);
        if(robotino->bumper() == true){
            objetivo_completo = 212;
            robotino->setVelocity(0,0,0);
        }

    }else if (objetivo_completo == 212){

        if (discos_entregues >= 4){
            robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10+10);
            robotino->change_state(IrParaPonto::instance());

        }else {
            robotino->definirDestino(robotino->odometryX()/10-10, robotino->odometryY()/10);
            robotino->change_state(IrParaPonto::instance());

        }
        objetivo_completo = 213;

    }else if (objetivo_completo == 213){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 22;

    }else if (objetivo_completo == 22){

        areaIr = decidirQualAreaIrV3Turbo(robotino);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 23;
        std::cout << "Indo para a area: " << areaIr << "\n";

    }else if (objetivo_completo == 23){     // MUDOU DA VERSAO 1 - acrescentou esse objetivo

        robotino->setThetaR(180);
        robotino->change_state(Girar::instance());
        objetivo_completo = 24;

    }else if(objetivo_completo == 24){

        robotino->definirParedeAlvo(Robotino::NORTE90);
        robotino->setDistParede(15);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = areaIr;

    }
    // Indo para a Area 1
    else if(objetivo_completo == 25){

        robotino->setCarregando(false);
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2);
        robotino->definirDestino(destino.get_x(), -destino.get_y()-100);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 29;

    }else if (objetivo_completo == 26) {


        robotino->definirParedeAlvo(Robotino::NORTE90);
        robotino->setDistParede(20);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 27;

    }else if (objetivo_completo == 27) {

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = areaIr;

    }
    // Indo para area de deposito 2
    else if (objetivo_completo == 28) {

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);
        robotino->definirDestino(destino.get_x(),-destino.get_y()-100);
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 29;

    }else if (objetivo_completo == 29){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 34; // Entregar
    }
    // Indo para area de deposito 3
    else if (objetivo_completo == 30) {

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA4);
        robotino->definirDestino(destino.get_x(), -destino.get_y()-100);
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 29;

    }else if (objetivo_completo == 31){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 32;

    }else if (objetivo_completo == 32) {

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA4);
        robotino->definirDestino(destino.get_x(), robotino->odometryY()/10);
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 33;

    }else if (objetivo_completo == 33){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 34;
    }
    // Entregando
    else if (objetivo_completo == 34){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 35;
    }else if(objetivo_completo == 35){
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10+15);
        robotino->change_state(IrParaPonto::instance());
        discos_entregues++;
        objetivo_completo = 36;
    }else if(objetivo_completo == 36){
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-35);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 15;
    }
    // Indo para casa
    else if(objetivo_completo == 37){
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 38;


    }else if(objetivo_completo == 38){

        robotino->setDistParede(10);
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->definirLinhaAlvo(-171.5, Robotino::VERTICAL); // COORDENADAS ESTANHAS REVER
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        objetivo_completo = 39;

    }else if(objetivo_completo == 39){

        robotino->definirDestino((robotino->odometryX())/10, robotino->odometryY()/10-35);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 40;
    }else if(objetivo_completo == 40){

        robotino->exit("Terminou");

    }

}

void Modulo2_V3Turbo::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}