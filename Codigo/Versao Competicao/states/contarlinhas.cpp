#include "contarlinhas.hpp"
#include "robotino.hpp"
#include "irparaponto.hpp"

//*****************************************************************************************************************
// ContarLinhas
//*****************************************************************************************************************

ContarLinhas  *ContarLinhas::instance()
{
    static ContarLinhas  ContarLinhasStateInstance;
    return &ContarLinhasStateInstance;
}

ContarLinhas::ContarLinhas() {}

ContarLinhas::~ContarLinhas() {}

void ContarLinhas::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado ContarLinhas...\n";
}

void ContarLinhas::execute(Robotino *robotino)
{
    static bool viMetal = false;
    static bool preto = false;
    static bool tag = false;
    static bool bati = false;
    static int numeroLinhas = 0;
    static State<Robotino> * voltar;

    std::cout << viMetal<<"\n";
    std::cout << robotino->readInductiveSensor()<<"\n--------------\n";
    std::cout << "Numero Linhas: "<<numeroLinhas << std::endl;

    if (robotino->readColorSensor(Robotino::SC_DIREITO) || robotino->readColorSensor(Robotino::SC_DIREITO)){
    	preto = true;
    }else{
    	preto = false;
    }

    if (preto || tag) {
        tag = true;
        if (!preto){
            numeroLinhas++;
            tag = false;
        }
    }

    if((robotino->readInductiveSensor() > 9.9 && !viMetal) || !robotino->readInductiveSensor()){
         robotino->setVelocity(80,0,0);

    }else{
        if (preto){
            numeroLinhas ++;
        }
        robotino->setVelocity(0,0,0);
        viMetal = true;
        robotino->setOdometry(760 , robotino->odometryY(), 180);
        if (numeroLinhas == 1){
            robotino->setCorDiscoDeposito(Object("blue"), Object("red"));
        }else if (numeroLinhas == 2){
            robotino->setCorDiscoDeposito(Object("yellow"), Object("blue"));
        }else if (numeroLinhas == 3){
            robotino->setCorDiscoDeposito(Object("yellow"), Object("red"));
        }
        robotino->change_state(robotino->previous_state());
        viMetal = false;
        preto = false;
        tag = false;
        bati = false;
        numeroLinhas = 0;
    }
    if (bati) {
        robotino->setVelocity(0,0,0);
        robotino->change_state(voltar);
        viMetal = false;
        preto = false;
        tag = false;
        numeroLinhas = 0;
        bati = false;
    }
    if (robotino->bumper() == true){
        voltar = robotino->previous_state();
        robotino->definirDestino(robotino->odometryX()/10 + 60, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        bati = true;
    }

}

void ContarLinhas::exit(Robotino *robotino) {
    std::cout << "Saindo do estado ContarLinhas...\n";
}
