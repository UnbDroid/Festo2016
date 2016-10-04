#include "contarlinhas.hpp"
#include "robotino.hpp"

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
    static int numeroLinhas = 0;

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
        robotino->setOdometry(680,robotino->odometryY(),179);
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
        numeroLinhas = 0;
    }

}

void ContarLinhas::exit(Robotino *robotino) {
    std::cout << "Saindo do estado ContarLinhas...\n";
}
