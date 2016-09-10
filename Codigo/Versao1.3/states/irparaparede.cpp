#include "irparaparede.hpp"
#include "girar.hpp"
#include "robotino.hpp"

#define refDist 20
#define Kpy 10
#define Kiy 0
#define dt 0.01
#define limiar 1
#define limiar2 0.5
#define R 20
#define PI 3.14159265
#define Kp 5
#define Ki 1

//*****************************************************************************************************************
// IrParaParede
//*****************************************************************************************************************

IrParaParede  *IrParaParede::instance()
{
    static IrParaParede  IrParaParedeStateInstance;
    return &IrParaParedeStateInstance;
}

IrParaParede::IrParaParede() {}

IrParaParede::~IrParaParede() {}

void IrParaParede::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IrParaParede...\n";
}

void IrParaParede::execute(Robotino *robotino)
{

    float   Vy = 0;
    float direcao = 0;
    float erroDist = 0;
    int paredeAlvo = Robotino::NORTE;//robotino->paredeAlvo();
    static bool girei = false;
    static float erro_intDist = 0;
    static bool ajuste = false;
    static bool pronto = false;
    static State<Robotino> * voltar;

    static float a = std::sin(60*PI/180)/std::sin(80*PI/180);
    static float cos20 = std::cos(20*PI/180);
    static float K = R*(a-1);
    static float erro_int = 0;
    float w;
    float e1 = robotino->irDistance(Robotino::IR_ESQUERDO_1);
    float e2 = robotino->irDistance(Robotino::IR_ESQUERDO_2);
    float ref_e1 = e2*a+K;
    float d1 = robotino->irDistance(Robotino::IR_DIREITO_1);
    float d2 = robotino->irDistance(Robotino::IR_DIREITO_2);
    float ref_d1 = d2*a+K;
    float distancia_da_esquerda, distancia_da_direita;
    float erro;

    // Gira para ficar paralelo à parede desejada

    if (paredeAlvo == Robotino::NORTE && !girei){
        direcao = -90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::SUL && !girei){
        direcao = -90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if (paredeAlvo == Robotino::LESTE && !girei){
        direcao = 0;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if (paredeAlvo == Robotino::OESTE && !girei){
        direcao = 0;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }

    // Anda até a parede desejada

    if ((paredeAlvo == Robotino::NORTE  || paredeAlvo == Robotino::LESTE) && girei ) {
        erroDist = e1 - refDist;
        erro_intDist += erroDist*dt;
        Vy = Kpy*erroDist+Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;
        robotino->setVelocity(0,Vy,0);

        if (std::abs(erroDist) < limiar) {
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }

    } else if ((paredeAlvo == Robotino::SUL  || paredeAlvo == Robotino::OESTE) && girei ) {
        erroDist = d1 - refDist;
        erro_intDist += erroDist*dt;
        Vy = -Kpy*erroDist-Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;
        robotino->setVelocity(0,Vy,0);

        if (std::abs(erroDist) < limiar) {
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }
    }

    // Se alinha na parede desejada

    if ((paredeAlvo == Robotino::NORTE  || paredeAlvo == Robotino::LESTE) && ajuste ){

        erro = (e1-ref_e1);
        erro_int += erro*dt;
        w = Kp*erro+Ki*erro_int;
        robotino->setVelocity(0,0,w);

        if (std::abs(erro) < limiar2){
            girei = false;
            ajuste = false;
            pronto = false;
            erro_intDist = 0;
            erro_int = 0;
            robotino->setVelocity(0,0,0);
            distancia_da_esquerda = ((e1+ref_e1+2*R)*cos20)/2;
            std::cout << "Distância da esquerda: " << distancia_da_esquerda << "\n";
            robotino->change_state(voltar);

        }

    } else if ((paredeAlvo == Robotino::SUL  || paredeAlvo == Robotino::OESTE) && ajuste ) {

        erro = (d1-ref_d1);
        erro_int += erro*dt;
        w = -Kp*erro-Ki*erro_int;
        robotino->setVelocity(0,0,w);

        if (std::abs(erro) < limiar2){
            girei = false;
            ajuste = false;
            pronto = false;
            erro_intDist = 0;
            erro_int = 0;
            robotino->setVelocity(0,0,0);
            distancia_da_direita = ((d1+ref_d1+2*R)*cos20)/2;
            std::cout << "Distância da direita: " << distancia_da_direita << "\n";
            robotino->change_state(voltar);

        }

    }

}

void IrParaParede::exit(Robotino *robotino) {}