#include "control.hpp"
#include "robotino.hpp"
#include "modulo1.hpp"
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
#include "alinhartraseiro.hpp"
#include "irparalinha.hpp"
#include "irparedepelaparede.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasnavegando.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
//*****************************************************************************************************************
// Control
//*****************************************************************************************************************

Control  *Control::instance()
{
    static Control  ControlStateInstance;
    return &ControlStateInstance;
}

Control::Control() {}

Control::~Control() {}

void Control::enter(Robotino *robotino)
{
    //if(!c_Control01) throw std::invalid_argument("Control must have an owner to enter.");
    std::cout << "Entrando no avoidance control...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

float corrigirAngulo(float Angulo){
    if(Angulo < -180)
        return Angulo+360;
    if(Angulo > 180)
        return Angulo-360;
    return Angulo;
}

void Control::execute(Robotino *robotino)
{
    static int objetivo_completo = 3;
    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());

    //robotino->setVelocity(0,-300,0);

    std::cout << "objetivo_completo: " << objetivo_completo << std::endl;
    if(objetivo_completo == 0){
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->setThetaR(-destino.get_theta());
        robotino->definirDestino(destino.get_x(), -destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 3;

    }else if (objetivo_completo == 60) {

        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistTrasParede(20);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 1;
    }

    else if(objetivo_completo == 1){
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);//,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        std::cout << "Destino:  " << destino << std::endl;
        robotino->definirDestino(robotino->odometryX()/10,-destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 50;

    }else if (objetivo_completo == 50) {
        robotino->change_state(AjustarNasLinhasNavegando::instance());


    }else if (objetivo_completo == 2){
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA1,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->definirDestino(destino.get_x(),-destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 6;
    }else if (objetivo_completo == 3){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 3;
    }else if(objetivo_completo == 11){
        robotino->definirCorAlvo(Robotino::VERMELHO);
        robotino->change_state(ProcurarCor::instance());
        objetivo_completo = 4;
    }else if(objetivo_completo == 4){
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 5;
    }else if(objetivo_completo == 5){
        std::cout << "Indo para SUL" << std::endl;
        robotino->definirParedeAlvo (Robotino::NORTEN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(6);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 60;
    }else if(objetivo_completo == 6){
        std::cout << "Indo para oeste" << std::endl;
        robotino->definirParedeAlvo (Robotino::LESTE0);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 9;
    }else if(objetivo_completo == 7){
       // robotino->setCarregando(true);
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 8;
    }else if(objetivo_completo == 8){

        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 81;
    }else if(objetivo_completo == 81){
        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 82;
    }else if(objetivo_completo == 82){
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 320;
    }else if(objetivo_completo == 320){
        //robotino->setCarregando(true);
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 321;
    }else if(objetivo_completo == 321){

        robotino->setThetaR(180);
        robotino->change_state(Girar::instance());
        objetivo_completo = 322;
    }
    else if(objetivo_completo == 150){

        robotino->definirParedeAlvo(Robotino::LESTE0);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(15);
        //robotino->setThetaR(180);
    //    robotino->change_state(IrParedePelaParedeProcurandoDisco::instance());
        objetivo_completo = 322;
    }



    else if(objetivo_completo == 9){
        robotino->definirLinhaAlvo(-100, Robotino::VERTICAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 100;
    }else if(objetivo_completo == 12){
        //robotino->setCarregando(true);
        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 90;
    }else if(objetivo_completo == 10){
        if(robotino->odometryX() > 1000){
             robotino->setVelocity(-100,0,0);
        }else{
            robotino->setVelocity(0,0,0);
            objetivo_completo = 0;
        }
        robotino->setCarregando(false);
    }else if (objetivo_completo == 15) {
        std::cout << "Sensor frente esquerda: " << robotino->irDistance(Robotino::IR_F_ESQUERDO) << std::endl;
        std::cout << "Sensor frente direito: " << robotino->irDistance(Robotino::IR_F_DIREITO) << std::endl;
        objetivo_completo = 15;

    }else if (objetivo_completo == 20) {
        robotino->change_state(PercorrerProcurandoDiscos::instance());
        objetivo_completo = 100;

    }else if (objetivo_completo == 25) {
        std::cout << "TESTE" << std::endl;
        std::cout << "Vendo na direita: " <<robotino->readColorSensor(Robotino::SC_DIREITO) << "\n";
        std::cout << "Vendo na esquerda: " <<robotino->readColorSensor(Robotino::SC_ESQUERDO) << "\n";
        std::cout << "Vendo no indutivo: " <<robotino->readInductiveSensor() << "\n";

    }else if (objetivo_completo == 30){

        robotino->setNaoDevoGirarParede(false);
        robotino->setDistParede(15);
        robotino->definirParedeAlvo (Robotino::LESTE180);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 800;

    }else if (objetivo_completo == 35){

        robotino->change_state(IdentificarCor::instance());

    }else if(objetivo_completo == 36){

        robotino->setDistParede(10);
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->definirLinhaAlvo(263, Robotino::HORIZONTAL); // mudei para arena competicao
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        robotino->setCarregando(false);
        objetivo_completo = 500;

    }else if (objetivo_completo == 37){

        robotino->definirObjetoAlvo(Robotino::TODAS);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 38;

    }

    //robotino->update();
    //std::cout << test << "\n";
    //std::cout << "Vendo na direita: " <<robotino->readColorSensor(Robotino::SC_DIREITO) << "\n";
    //std::cout << "Vendo na esquerda: " <<robotino->readColorSensor(Robotino::SC_ESQUERDO) << "\n";
    //std::cout << "Vendo no indutivo: " <<robotino->readInductiveSensor() << "\n";
    //cv::Mat img = robotino->getImage();
    //cv::Mat teste (img,cv::Rect(0,0,img.cols,img.rows - 10));
    //std::cout << img;
    //cv::imshow("Amor",img);
    //cv::waitKey(1);
    //std::cout << robotino->getImage();*/
}

void Control::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}