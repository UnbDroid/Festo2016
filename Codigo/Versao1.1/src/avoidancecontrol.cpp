#include "avoidancecontrol.hpp"
#include "robotino.hpp"
#include "Classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "irparaponto.hpp"
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
    /*static int objetivo_completo = 0;
    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());
    if (objetivo_completo)
    {
        robotino->exit("Terminou essa porra!");
    }else{
        robotino->definirDestino(0,50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 1;
    }*/

    //robotino->update();
    //std::cout << test << "\n";
    //std::cout << "Vendo na direita: " <<robotino->readColorSensor(Robotino::SC_DIREITO) << "\n";
    //std::cout << "Vendo na esquerda: " <<robotino->readColorSensor(Robotino::SC_ESQUERDO) << "\n";
    //std::cout << "Vendo no indutivo: " <<robotino->readInductiveSensor() << "\n";
    cv::Mat img = robotino->getImage();
    cv::Mat teste (img,cv::Rect(0,0,img.cols,img.rows - 10));
    //std::cout << img;
    cv::imshow("Amor",img);
    cv::waitKey(1);
    //std::cout << robotino->getImage();
}

void AvoidanceControl::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}