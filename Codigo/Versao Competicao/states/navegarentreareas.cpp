#include "navegarentreareas.hpp"
#include "irparaponto.hpp"
#include "ajustarnaslinhas.hpp"

#include "robotino.hpp"
//*****************************************************************************************************************
// NavegarEntreAreas
//*****************************************************************************************************************

NavegarEntreAreas  *NavegarEntreAreas::instance()
{
    static NavegarEntreAreas  NavegarEntreAreasStateInstance;
    return &NavegarEntreAreasStateInstance;
}

NavegarEntreAreas::NavegarEntreAreas() {}

NavegarEntreAreas::~NavegarEntreAreas() {}

void NavegarEntreAreas::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado NavegarEntreAreas...\n";
}

void NavegarEntreAreas::execute(Robotino *robotino)
{
    static int depositoAtual;
    static int depositoDestino;
    static int movimento;
    static int contador = 1;
    static State<Robotino> * voltar;
    static bool chegueiPonto = false;
    static bool entrei = true;
    static bool chegueiDestino = false;

    if (entrei){
        std::cout << "entrei:  " << std::endl;
        voltar = robotino->previous_state();
        depositoDestino = robotino->getDepositoDestino();
        depositoAtual = robotino->getDepositoAtual();
        movimento = depositoAtual - depositoDestino;
        entrei = false;
    }

    std::cout << "depositoAtual:  " << depositoAtual << std::endl;
    std::cout << "depositoDestino:  " << depositoDestino << std::endl;

    if (movimento < 0){

        if (depositoAtual + contador <= depositoDestino) {
            if  (!chegueiPonto){
                Coordenadas destino = robotino->pegarCoordenadaArea(depositoAtual+contador);
                robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
                robotino->change_state(IrParaPonto::instance());
                chegueiPonto = true;
            }else {
                robotino->change_state(AjustarNasLinhas::instance());
                chegueiPonto = false;
                contador++;
            }
        }else if (depositoAtual + contador > depositoDestino){
                chegueiDestino = true;
        }
    }else if (movimento > 0) {

        if (depositoAtual - contador >= depositoDestino) {
            if  (!chegueiPonto){
                Coordenadas destino = robotino->pegarCoordenadaArea(depositoAtual-contador);
                robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
                robotino->setCarregando(false);
                robotino->change_state(IrParaPonto::instance());
                chegueiPonto = true;
            }else {
                robotino->change_state(AjustarNasLinhas::instance());
                chegueiPonto = false;
                contador++;
            }
        }else if (depositoAtual - contador  < depositoDestino){
                chegueiDestino = true;
        }

    }else if (movimento == 0) {
        robotino->change_state(voltar);
        chegueiDestino = false;
        entrei = true;
        chegueiPonto = false;
        contador = 1;
    }

    if (chegueiDestino){
        robotino->change_state(voltar);
        chegueiDestino = false;
        entrei = true;
        chegueiPonto = false;
        contador = 1;
    }
}

void NavegarEntreAreas::exit(Robotino *robotino) {}
