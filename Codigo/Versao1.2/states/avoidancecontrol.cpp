#include "avoidancecontrol.hpp"
#include "robotino.hpp"
#include "Classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "irparaponto.hpp"
#include "controleposicao.hpp"
#include "Coordenadas.hpp"
#include "girar.hpp"
#include "identificarcor.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
//*****************************************************************************************************************
// AvoidanceControl
//*****************************************************************************************************************

AvoidanceControl  *AvoidanceControl::instance()
{
    static AvoidanceControl  AvoidanceControlStateInstance;
    return &AvoidanceControlStateInstance;
}

AvoidanceControl::AvoidanceControl() {}

AvoidanceControl::~AvoidanceControl() {}

void AvoidanceControl::enter(Robotino *robotino)
{
    //if(!c_AvoidanceControl01) throw std::invalid_argument("AvoidanceControl must have an owner to enter.");
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

void AvoidanceControl::execute(Robotino *robotino)
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
        robotino->setOdometry(robotino->x_d,robotino->y_d,robotino->odometryPhi());
        Coordenadas destino = robotino->pegar_coordenada_area(2,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->definirDestino(destino.get_x(),-destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 3;
    }else if(objetivo_completo == 1){
        robotino->setOdometry(robotino->x_d,robotino->y_d,robotino->odometryPhi());
        Coordenadas destino = robotino->pegar_coordenada_area(3,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->definirDestino(destino.get_x(),-destino.get_y());
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 2;
    }else if(objetivo_completo == 0){
        Coordenadas destino = robotino->pegar_coordenada_area(4,Coordenadas(robotino->odometryX()/10, -robotino->odometryY()/10));
        robotino->setTheta_r(45);
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

void AvoidanceControl::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}