#include "irparaponto.hpp"
#include "robotino.hpp"
#include "Classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "Coordenadas.hpp"
#include "girar.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define FATOR_VELOCIDADE  5

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
    static bool girei = false;
    static State<Robotino> * voltar;
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

    // Calculo velocidade utilizando theta
    Coordenadas velocidades_globais(Vx,Vy);
    Coordenadas velocidades_robo = velocidades_globais.mudar_referencia(0,0,(robotino->odometryPhi()));

    Vx = velocidades_robo.get_x();
    Vy = velocidades_robo.get_y();

    // Falando para o robo as velocidades que ele deve se mover
    robotino->setVelocity(FATOR_VELOCIDADE*Vx,FATOR_VELOCIDADE*Vy,0);

    // Se tiver chegado ao alvo, voltar para o estado anterior
    std::cout << "D_E "<<robotino->d_e<<"...\n";
    std::cout << "X_D "<<robotino->x_d<<"...\n";
    std::cout << "Y_D "<<robotino->y_d<<"...\n";
    std::cout << "X:  "<<robotino->odometryX()<<"...\n";
    std::cout << "Y:  "<<robotino->odometryY()<<"...\n";
    if(girei){
        std::cout << "Entrei aqui nessa paradinha dinha dinha\n";
        robotino->change_state(voltar);
        girei = false;
    }else if(robotino->d_e < 1){
        std::cout << "Entrei aqui nessa paradinha dinha dinha 2\n";
        voltar = robotino->previous_state();
        robotino->change_state(Girar::instance());
        girei = true;
    }
}

void IrParaPonto::exit(Robotino *robotino) {
    std::cout << "Cheguei no ponto...\n";
    robotino->setVelocity(0,0,0);
}
