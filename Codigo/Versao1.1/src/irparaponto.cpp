#include "irparaponto.hpp"
#include "robotino.hpp"
#include "Classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265

//*****************************************************************************************************************
// IrParaPonto
//*****************************************************************************************************************

IrParaPonto  *IrParaPonto::instance()
{
    static IrParaPonto  IrParaPontoStateInstance;
    return &IrParaPontoStateInstance;
}

IrParaPonto::IrParaPonto() {}

IrParaPonto::~IrParaPonto() {}

void IrParaPonto::enter(Robotino *robotino)
{
    std::cout << "Indo para o ponto...\n";
}

void IrParaPonto::execute(Robotino *robotino)
{

    std::cout << "Running IrParaPonto...\n";
    ClassificadorAngulo CA;
    ClassificadorDistancia CD;
    Defuzzyficador D;
    MaquinaInferencia MI;
    static std::vector<float> x,y,theta_d,dist_d,vx,vy;

    // Calculando a distancia e o angulo para o alvo
    robotino->d_e = robotino->calc_dist(robotino->x_d,robotino->odometryX(),robotino->y_d,robotino->odometryY())/10;
    robotino->theta_e = -atan2(robotino->y_d-robotino->odometryY(),robotino->x_d-robotino->odometryX())*180/PI;

    // Fuzzificando os valores de angulo e distancia desejados
    CA.classificar(robotino->theta_e);
    CD.classificar(robotino->d_e);
    vector<float> pertinenciaAngulo = CA.pegarVetorPertinencia();
    vector<float> pertinenciaDistancia = CD.pegarVetorPertinencia();

    // Gerando regras para os valores com a Maquina de Inferencia
    vector<float> saidaVx = MI.tabelaRegrasVx(pertinenciaDistancia,pertinenciaAngulo);
    vector<float> saidaVy = MI.tabelaRegrasVy(pertinenciaDistancia,pertinenciaAngulo);

    //  Defuzzificando os valores
    float Vx = D.centroDeMassa(saidaVx);
    float Vy = D.centroDeMassa(saidaVy);

    // Falando para o robo as velocidades que ele deve se mover
    robotino->setVelocity(7.5*Vx,7.5*Vy,0);

    // Se tiver chegado ao alvo, voltar para o estado anterior
    std::cout << "D_E "<<robotino->d_e<<"...\n";
    std::cout << "X_D "<<robotino->x_d<<"...\n";
    std::cout << "Y_D "<<robotino->y_d<<"...\n";
    if(robotino->d_e < 1){
        robotino->change_state(robotino->previous_state());
    }
}

void IrParaPonto::exit(Robotino *robotino) {
    std::cout << "Cheguei no ponto...\n";   
    robotino->setVelocity(0,0,0);    
}
