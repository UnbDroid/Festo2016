#include "ajusteinicial.hpp"
#include "robotino.hpp"
#include <cmath>
#include "avoidancecontrol.hpp"

#define limiar 0.5
#define R 20
#define PI 3.14159265
#define Kp 5
#define Ki 1
#define dt 0.01
//*****************************************************************************************************************
// AjusteInicial
//*****************************************************************************************************************

AjusteInicial  *AjusteInicial::instance()
{
    static AjusteInicial  AjusteInicialStateInstance;
    return &AjusteInicialStateInstance;
}

AjusteInicial::AjusteInicial() {}

AjusteInicial::~AjusteInicial() {}

void AjusteInicial::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Ajuste Inicial...\n";
}

void AjusteInicial::execute(Robotino *robotino)
{
    static float a = std::sin(60*PI/180)/std::sin(80*PI/180);
    static float cos20 = std::cos(20*PI/180);
    static float K = R*(a-1);
    static float erro_int = 0;
    float w;
    float e1 = robotino->ir_distance(Robotino::IR_ESQUERDO_1);
    float e2 = robotino->ir_distance(Robotino::IR_ESQUERDO_2);
    float ref_e1 = e2*a+K;
    float te = robotino->ir_distance(Robotino::IR_T_ESQUERDO);
    float td = robotino->ir_distance(Robotino::IR_T_DIREITO);
    float distancia_da_esquerda, distancia_de_tras;/*
    std::cout << "Frontal: " << robotino->ir_distance(Robotino::IR_FRONTAL) << "\n";
    std::cout << "Frontal esquerdo: " << robotino->ir_distance(Robotino::IR_F_ESQUERDO) << "\n";
    std::cout << "Esquerdo 1: " << robotino->ir_distance(Robotino::IR_ESQUERDO_1) << "\n";
    std::cout << "Esquerdo 2: " << robotino->ir_distance(Robotino::IR_ESQUERDO_2) << "\n";
    std::cout << "Traseiro Esquerdo: " << robotino->ir_distance(Robotino::IR_T_ESQUERDO) << "\n";
    std::cout << "Frontal direito: " << robotino->ir_distance(Robotino::IR_F_DIREITO) << "\n";
    std::cout << "Direito 1: " << robotino->ir_distance(Robotino::IR_DIREITO_1) << "\n";
    std::cout << "Direito 2: " << robotino->ir_distance(Robotino::IR_DIREITO_2) << "\n";
    std::cout << "Traseiro Direito: " << robotino->ir_distance(Robotino::IR_T_DIREITO) << "\n";
    std::cout << "E1 deveria ser: " << robotino->ir_distance(Robotino::IR_ESQUERDO_2)*a+K << "\n" << "\n";*/
    float erro = (e1-ref_e1) + (te-td);
 /*   std::cout << "Erro esquerdo: " << (e1-ref_e1) << "\n";
    std::cout << "Erro traseiro: " << (te-td) << "\n";
    std::cout << "Erro total: " << erro << "\n";*/
    erro_int += erro*dt;
    w = Kp*erro+Ki*erro_int;
    robotino->setVelocity(0,0,w);
    if (std::abs(erro) < limiar){
        erro_int = 0;
        distancia_da_esquerda = ((e1+ref_e1+2*R)*cos20)/2;
        distancia_de_tras= ((te+td+2*R)*cos20)/2;
        std::cout << "Distância da esquerda: " << distancia_da_esquerda << "\n";
        std::cout << "Distância de tras: " << distancia_de_tras << "\n";
        robotino->setOdometry(distancia_de_tras*10+15,-(distancia_da_esquerda*10+15),0);
        robotino->change_state(AvoidanceControl::instance());
    }

}

void AjusteInicial::exit(Robotino *robotino) {}
