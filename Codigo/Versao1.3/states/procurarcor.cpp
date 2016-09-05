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

	float w;
	static State<Robotino> * voltar;
	static bool procurei = 0;

	if(!procurei){

		voltar = robotino->previous_state(); 
	} 

	w = 10.0;

	if(robotino->objetoAlvo.getType() == "blue"){

		if(robotino->objetosAzuis.size() == 0){

			robotino->setVelocity(0,0,w);
			procurei = 1;
			robotino->change_state(IdentificarCor::instance());

		}else{

			robotino->setVelocity(0,0,0);
			robotino->change_state(voltar);
		}

	}

	if(robotino->objetoAlvo.getType() == "yellow"){

		if(robotino->objetosAmarelos.size() == 0){

			robotino->setVelocity(0,0,w);
			procurei = 1;
			robotino->change_state(IdentificarCor::instance());

		}else{

			robotino->setVelocity(0,0,0);
			robotino->change_state(voltar);
		}

	}

	if(robotino->objetoAlvo.getType() == "red"){

		if(robotino->objetosVermelhos.size() == 0){

			robotino->setVelocity(0,0,w);
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
