#include "procurarcor.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "identificarcor.hpp"
#include "control.hpp"
#include "basestate.hpp"
//*****************************************************************************************************************
// ProcurarCor
//*****************************************************************************************************************

ProcurarCor  *ProcurarCor::instance()
{
    static ProcurarCor  ProcurarCorStateInstance;
    return &ProcurarCorStateInstance;
}

ProcurarCor::ProcurarCor() {}

ProcurarCor::~ProcurarCor() {}

void ProcurarCor::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado ProcurarCor...\n";
}

void ProcurarCor::execute(Robotino *robotino)
{

	float vx = robotino->getVelocidadeBusca();
	static State<Robotino> * voltar;
	static bool procurei = 0;

	if(!procurei){

		voltar = robotino->previous_state();
	}

	if(robotino->objetoAlvo.getType() == "blue"){

		if(robotino->objetosAzuis.size() == 0){

			robotino->setVelocity(vx,0,0);
			procurei = 1;
			robotino->change_state(IdentificarCor::instance());

		}else{

			robotino->setVelocity(0,0,0);
			robotino->change_state(voltar);
		}

	}

	if(robotino->objetoAlvo.getType() == "yellow"){

		if(robotino->objetosAmarelos.size() == 0){

			robotino->setVelocity(vx,0,0);
			procurei = 1;
			robotino->change_state(IdentificarCor::instance());

		}else{

			robotino->setVelocity(0,0,0);
			robotino->change_state(voltar);
		}

	}

	if(robotino->objetoAlvo.getType() == "red"){

		if(robotino->objetosVermelhos.size() == 0){

			robotino->setVelocity(vx,0,0);
			procurei = 1;
			robotino->change_state(IdentificarCor::instance());

		}else{

			robotino->setVelocity(0,0,0);
			robotino->change_state(voltar);
		}

	}


	if(robotino->objetoAlvo.getType() == "all"){

		if(robotino->objetosVermelhos.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosAzuis.size() == 0){

			robotino->setVelocity(vx,0,0);
			procurei = 1;
			robotino->change_state(IdentificarCor::instance());

		}else{

			robotino->setVelocity(0,0,0);
			robotino->change_state(voltar);
		}

	}


}

void ProcurarCor::exit(Robotino *robotino) {

	cout << "bye" << endl;

}
