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
    static int objetivo_completo = 0;
    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());
    if (objetivo_completo == 3)
    {
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 4;
    }else if (objetivo_completo == 2)
    {
        robotino->setOdometry(robotino->xD,robotino->yD,robotino->odometryPhi());
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA1,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->definirDestino(destino.get_x(),-destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 3;
    }else if(objetivo_completo == 1){
        robotino->setOdometry(robotino->xD,robotino->yD,robotino->odometryPhi());
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->definirDestino(destino.get_x(),-destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 2;
    }else if(objetivo_completo == 0){
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->setThetaR(45);
        robotino->definirDestino(destino.get_x(), -destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 1;
    }else{
        cout << "Azul: " << robotino->objetosAzuis.size() << endl;
        cout << "Amarelo: " << robotino->objetosAmarelos.size() << endl;
        cout << "Vermelho: " << robotino->objetosVermelhos.size() << endl;
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
    //std::cout << robotino->getImage();
}

void Control::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}