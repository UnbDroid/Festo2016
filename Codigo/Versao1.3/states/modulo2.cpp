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
#include "ajustarnaslinhas.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "contarlinhas.hpp"
#include "modulo2_V2.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include <unistd.h>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define VELBUSCA 20
#define OBJETIVOAREA1 32
#define OBJETIVOAREA2 48
#define OBJETIVOAREA3 36
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

/*int decidirQualAreaIr(Robotino * robotino){
    if (robotino->objetosAmarelos.size() > 0){

        robotino->definirObjetoAlvo(Robotino::AMARELO);
        std::cout<< "seguindo amarelo " << std::endl;
        if(robotino->area1discoFaltando.getType() == "yellow"){
            return OBJETIVOAREA1;
        }else if(robotino->area2discoFaltando.getType() == "yellow"){
            return OBJETIVOAREA2;
        }else if(robotino->area3discoFaltando.getType() == "yellow"){
            return OBJETIVOAREA3;
        }

    }else if (robotino->objetosAzuis.size() > 0){

        robotino->definirObjetoAlvo(Robotino::AZUL);
        std::cout<< "seguindo azul " << std::endl;
        if(robotino->area1discoFaltando.getType() == "blue"){
            return OBJETIVOAREA1;
        }else if(robotino->area2discoFaltando.getType() == "blue"){
            return OBJETIVOAREA2;
        }else if(robotino->area3discoFaltando.getType() == "blue"){
            return OBJETIVOAREA3;
        }

    }else if (robotino->objetosVermelhos.size() > 0){

        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        std::cout<< "seguindo vermelho " << std::endl;
        if(robotino->area1discoFaltando.getType() == "red"){
            return OBJETIVOAREA1;
        }else if(robotino->area2discoFaltando.getType() == "red"){
            return OBJETIVOAREA2;
        }else if(robotino->area3discoFaltando.getType() == "red"){
            return OBJETIVOAREA3;
        }

    }
}

void identificarCorFaltandoArea1(Robotino *robotino){
    if(robotino->area1disco1.getType() == "yellow"){
        if(robotino->objetosAmarelos.size() > 0){
            robotino->area1discoFaltando = robotino->area1disco2;
        }
    }else if(robotino->area1disco1.getType() == "red"){
        std::cout << "Entrei aqui\n";
        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Entrei aqui2\n";
            robotino->area1discoFaltando = robotino->area1disco2;
        }
    }else if(robotino->area1disco1.getType() == "blue"){
        if(robotino->objetosAzuis.size() > 0){
            robotino->area1discoFaltando = robotino->area1disco2;
        }
    }
    if(robotino->area1disco2.getType() == "yellow"){
        if(robotino->objetosAmarelos.size() > 0){
            robotino->area1discoFaltando = robotino->area1disco1;
        }
    }else if(robotino->area1disco2.getType() == "red"){
        std::cout << "Entrei aqui3\n";
        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Entrei aqui4\n";
            robotino->area1discoFaltando = robotino->area1disco1;
        }
    }else if(robotino->area1disco2.getType() == "blue"){
        if(robotino->objetosAzuis.size() > 0){
            robotino->area1discoFaltando = robotino->area1disco1;
        }
    }
}

void identificarCorFaltandoArea2(Robotino *robotino){
    if(robotino->area2disco1.getType() == "yellow"){
        if(robotino->objetosAmarelos.size() > 0){
            robotino->area2discoFaltando = robotino->area2disco2;
        }
    }else if(robotino->area2disco1.getType() == "red"){
        std::cout << "Entrei aqui\n";
        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Entrei aqui2\n";
            robotino->area2discoFaltando = robotino->area2disco2;
        }
    }else if(robotino->area2disco1.getType() == "blue"){
        if(robotino->objetosAzuis.size() > 0){
            robotino->area2discoFaltando = robotino->area2disco2;
        }
    }
    if(robotino->area2disco2.getType() == "yellow"){
        if(robotino->objetosAmarelos.size() > 0){
            robotino->area2discoFaltando = robotino->area2disco1;
        }
    }else if(robotino->area2disco2.getType() == "red"){
        std::cout << "Entrei aqui3\n";
        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Entrei aqui4\n";
            robotino->area2discoFaltando = robotino->area2disco1;
        }
    }else if(robotino->area2disco2.getType() == "blue"){
        if(robotino->objetosAzuis.size() > 0){
            robotino->area2discoFaltando = robotino->area2disco1;
        }
    }
}

void identificarCorFaltandoArea3(Robotino *robotino){
    if(robotino->area3disco1.getType() == "yellow"){
        if(robotino->objetosAmarelos.size() > 0){
            robotino->area3discoFaltando = robotino->area3disco2;
        }
    }else if(robotino->area3disco1.getType() == "red"){
        std::cout << "Entrei aqui\n";
        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Entrei aqui2\n";
            robotino->area3discoFaltando = robotino->area3disco2;
        }
    }else if(robotino->area3disco1.getType() == "blue"){
        if(robotino->objetosAzuis.size() > 0){
            robotino->area3discoFaltando = robotino->area3disco2;
        }
    }
    if(robotino->area3disco2.getType() == "yellow"){
        if(robotino->objetosAmarelos.size() > 0){
            robotino->area3discoFaltando = robotino->area3disco1;
        }
    }else if(robotino->area3disco2.getType() == "red"){
        std::cout << "Entrei aqui3\n";
        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Entrei aqui4\n";
            robotino->area3discoFaltando = robotino->area3disco1;
        }
    }else if(robotino->area3disco2.getType() == "blue"){
        if(robotino->objetosAzuis.size() > 0){
            robotino->area3discoFaltando = robotino->area3disco1;
        }
    }
}*/

/*
    Se certificar que ele entregue o disco completamente
*/

void Modulo2::execute(Robotino *robotino)
{
   /* static int objetivo_completo = 3;
    static int discos_entregues = 0;
    std::cout << "objetivo_completo = " << objetivo_completo << std::endl;

    // Usado para fazer teste pulando etapas --------------------------------------------------------------------------------------------------------------------
    if(objetivo_completo == 0){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA7);//,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        std::cout <<"Resultado"<<destino<<"\n";
        robotino->definirDestino(destino.get_x(), -(destino.get_y()+50));
        //robotino->setThetaR(160);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 30;

    }
    // Aqui comeca o modulo 2 Indo para a area de deposito 3 identificar a cor -------------------------------------------------------------------------------------
    else if(objetivo_completo == 3){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 4;

    }else if(objetivo_completo == 4){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 5;

    }else if(objetivo_completo == 5){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo =6;

    }else if (objetivo_completo == 6){

        robotino->setAreaDeposito(Robotino::AREA4);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 7;

    }else if (objetivo_completo == 7){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 8;

    }else if (objetivo_completo == 8){

        std::cout << "Disco 1 da cor: " << robotino->area3disco1.getType() << "\n";
        std::cout << "Disco 2 da cor: " << robotino->area3disco2.getType() << "\n";
        identificarCorFaltandoArea3(robotino);
        objetivo_completo = 9;

    }else if (objetivo_completo == 9){

        std::cout << "Esta faltando o disco da cor: " << robotino->area3discoFaltando.getType() << "\n";
        objetivo_completo = 10;

    }
    // Indo para a area de deposito 2 identificar a cor -----------------------------------------------------------------------------------------------------------------------
    else if (objetivo_completo == 10) {

        robotino->definirDestino((robotino->odometryX())/10+30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 11;

    }else if (objetivo_completo == 11){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);
        robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 12;

    }else if (objetivo_completo == 12){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 13;

    }else if (objetivo_completo == 13){
        robotino->setAreaDeposito(Robotino::AREA3);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 14;

    }else if (objetivo_completo == 14){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 15;

    }else if (objetivo_completo == 15){
        std::cout << "Disco 1 da cor: " << robotino->area2disco1.getType() << "\n";
        std::cout << "Disco 2 da cor: " << robotino->area2disco2.getType() << "\n";
        identificarCorFaltandoArea2(robotino);
        objetivo_completo = 16;

    }else if (objetivo_completo == 16){
        std::cout << "Esta faltando o disco da cor: " << robotino->area2discoFaltando.getType() << "\n";
        objetivo_completo = 17;

    }
    // Indo para a area de deposito 1 identificar a cor ------------------------------------------------------------------------------------------------------------------------------
    else if (objetivo_completo == 17) {

        robotino->definirDestino((robotino->odometryX())/10+30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 18;

    }else if (objetivo_completo == 18){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2);
        robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 19;

    }else if (objetivo_completo == 19){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 20;

    }else if (objetivo_completo == 20){
        robotino->setAreaDeposito(Robotino::AREA2);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 21;

    }else if (objetivo_completo == 21){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 22;

    }else if (objetivo_completo == 22){
        std::cout << "Disco 1 da cor: " << robotino->area1disco1.getType() << "\n";
        std::cout << "Disco 2 da cor: " << robotino->area1disco2.getType() << "\n";
        identificarCorFaltandoArea1(robotino);
        objetivo_completo = 23;

    }else if (objetivo_completo == 23){
        std::cout << "Esta faltando o disco da cor: " << robotino->area1discoFaltando.getType() << "\n";
        objetivo_completo = 25;

    }else if (objetivo_completo == 25) {

        std::cout << "Area 1 Esta faltando o disco da cor: " << robotino->area1discoFaltando.getType() << "\n";
        std::cout << "Area 2 Esta faltando o disco da cor: " << robotino->area2discoFaltando.getType() << "\n";
        std::cout << "Area 3 Esta faltando o disco da cor: " << robotino->area3discoFaltando.getType() << "\n";
        objetivo_completo = 26;

    }
    // Parte que ve os discos e decide onde ir -----------------------------------------------------------------------------------------------
    else if (objetivo_completo == 26) {

        if(discos_entregues < 3){
            robotino->definirParedeAlvo(Robotino::OESTE0);
            robotino->setDistParede(6);
            robotino->change_state(IrParaParede::instance());
            objetivo_completo = 27;
        }else{
            objetivo_completo = 62;
        }


    }else if (objetivo_completo == 27) {

        robotino->definirLinhaAlvo(73, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 28;

    }else if (objetivo_completo == 28){

        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 - 70);
        robotino->setThetaR(90);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 30;

    }
    // Testando percorrer procurando discos
    else if (objetivo_completo == 30) {
        robotino->change_state(PercorrerProcurandoDiscos::instance());
        objetivo_completo = 31;

    }else if (objetivo_completo == 31) {

         robotino->change_state(SeguirCor::instance());
         objetivo_completo = decidirQualAreaIr(robotino);
         robotino->setCarregando(true);

    }
    // Indo entregar o disco que for na AREA de depósito 1 ----------------------------------------------------------------------------------------------------------------------
    else if(objetivo_completo == 32){

        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(20);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 33;

    }else if(objetivo_completo == 33){

        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(30);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 34;

    }else if(objetivo_completo == 34){

        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 35;

    }else if (objetivo_completo == 35){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10+30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        discos_entregues++;
        objetivo_completo = 26;

    }
    // Indo entregar o disco que for na AREA de depósito 3 ---------------------------------------------------------------------------------------------------------------------
    else if(objetivo_completo == 36){

        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(20);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 37;

    }else if(objetivo_completo == 37){

        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 38;

    }else if(objetivo_completo == 38){

        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 39;

    }else if(objetivo_completo == 39){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(8);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 40;

    }else if(objetivo_completo == 40){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 41;

    }else if(objetivo_completo == 41){

        robotino->definirLinhaAlvo(150, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 42;

    }else if(objetivo_completo == 42){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 43;

    }else if(objetivo_completo ==43){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo =44;

    }else if (objetivo_completo == 44){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 45;

    }else if(objetivo_completo == 45){

        robotino->definirLinhaAlvo(61, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 451;

    }else if (objetivo_completo == 451){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10-10, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 46;  // Ve em qual area ele pega o proximo//

    }else if (objetivo_completo == 46){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10+40, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 47;

    }else if (objetivo_completo == 47){
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        discos_entregues++;
        objetivo_completo = 26;

    }
    // Indo entregar o disco que for na AREA de depósito 2 -----------------------------------------------------------------------------------------------
    else if(objetivo_completo == 48){

        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(20);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 49;

    }else if(objetivo_completo == 49){

        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 50;

    }else if(objetivo_completo == 50){

        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 51;

    }else if(objetivo_completo == 51){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(8);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 52;

    }else if(objetivo_completo == 52){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 53;

    }else if(objetivo_completo == 53){

        robotino->definirLinhaAlvo(150, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 54;

    }else if(objetivo_completo == 54){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 55;

    }else if(objetivo_completo ==55){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo =56;

    }else if (objetivo_completo == 56){

        robotino->setCarregando(false);
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);
        robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 57;

    }else if (objetivo_completo == 57){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 58;

    }else if (objetivo_completo == 58){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 59;

    }else if(objetivo_completo == 59){

        robotino->definirLinhaAlvo(61, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 591;

    }else if (objetivo_completo == 591){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10-10, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 60;  // Ve em qual area ele pega o proximo//

    }else if (objetivo_completo == 60){

        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10+40, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 61;

    }else if (objetivo_completo == 61){

        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        discos_entregues++;
        objetivo_completo = 26;

    }
    // Voltando para casinha -----------------------------------------------------------------------------------------------------------------------------------------------------------
    else if(objetivo_completo == 62){

        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(20);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 63;

    }else if(objetivo_completo == 63){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->setDistTrasParede(6);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 64;

    }*/

}

void Modulo2::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}