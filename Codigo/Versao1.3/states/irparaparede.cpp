#include "irparaparede.hpp"
#include "girar.hpp"
#include "robotino.hpp"

#define refDist 20
#define Kpy 10
#define Kiy 0
#define dt 0.01
#define limiar 1

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
    int paredeAlvo = Robotino::NORTE;//robotino->paredeAlvo();
    static bool girei = false;
    static float erroDist = 0, erro_intDist = 0;
    static bool ajuste = false;
    static State<Robotino> * voltar;


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
    if ((paredeAlvo == Robotino::NORTE  || paredeAlvo == Robotino::LESTE) && girei ) {
        erroDist = robotino->irDistance(Robotino::IR_ESQUERDO_1) - refDist;
        erro_intDist += erroDist*dt;
        Vy = Kpy*erroDist+Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;
        robotino->setVelocity(0,Vy,0);

        if (erroDist < limiar) {
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }

    } else if ((paredeAlvo == Robotino::SUL  || paredeAlvo == Robotino::OESTE) && girei ) {
        erroDist = robotino->irDistance(Robotino::IR_DIREITO_1) - refDist;
        erro_intDist += erroDist*dt;
        Vy = -Kpy*erroDist-Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;
        robotino->setVelocity(0,Vy,0);

        if (erroDist < limiar) {
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }
    }
    if ((paredeAlvo == Robotino::NORTE  || paredeAlvo == Robotino::LESTE) && ajuste ){


    } else if ((paredeAlvo == Robotino::SUL  || paredeAlvo == Robotino::OESTE) && ajuste ) {

    }


}

void IrParaParede::exit(Robotino *robotino) {}