#include "irparalinha.hpp"
#include "robotino.hpp"
//*****************************************************************************************************************
// IrParaLinha
//*****************************************************************************************************************

#define Vx 200

IrParaLinha  *IrParaLinha::instance()
{
    static IrParaLinha  IrParaLinhaStateInstance;
    return &IrParaLinhaStateInstance;
}

IrParaLinha::IrParaLinha() {}

IrParaLinha::~IrParaLinha() {}

void IrParaLinha::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IrParaLinha...\n";
}

void IrParaLinha::execute(Robotino *robotino)
{
    static bool preto = false;
    if(robotino->readColorSensor(Robotino::SC_DIREITO) || robotino->readColorSensor(Robotino::SC_ESQUERDO)){
        preto = true;
    }if(preto){
        robotino->change_state(robotino->previous_state());
        if(robotino->linhaAlvo() == Robotino::HORIZONTAL){
            robotino->setOdometry(robotino->valorLinha(), robotino->odometryY(), robotino->odometryPhi());
        }else if(robotino->linhaAlvo() == Robotino::VERTICAL){
            robotino->setOdometry(robotino->odometryX(), robotino->valorLinha(), robotino->odometryPhi());
        }
        preto = false;
    }else{
        robotino->setVelocity(Vx,0,0);
    }
}

void IrParaLinha::exit(Robotino *robotino) {
    robotino->setVelocity(0,0,0);
}
