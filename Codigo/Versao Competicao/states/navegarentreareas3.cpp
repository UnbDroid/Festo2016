#include "navegarentreareas3.hpp"
#include "irparaponto.hpp"
#include "ajustarnaslinhasnavegando.hpp"
#include "ajustarnaslinhas.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "irparalinha.hpp"
#include "andarpelaparedeatelinha.hpp"

#include "robotino.hpp"
//*****************************************************************************************************************
// NavegarEntreAreas3
//*****************************************************************************************************************

NavegarEntreAreas3  *NavegarEntreAreas3::instance()
{
    static NavegarEntreAreas3  NavegarEntreAreas3StateInstance;
    return &NavegarEntreAreas3StateInstance;
}

float coordenadaArea3(int area, Robotino * robotino){
    Coordenadas coord = robotino->pegarCoordenadaArea(area);
    return -coord.get_y();
}

NavegarEntreAreas3::NavegarEntreAreas3() {}

NavegarEntreAreas3::~NavegarEntreAreas3() {}

void NavegarEntreAreas3::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado NavegarEntreAreas3...\n";
}

void NavegarEntreAreas3::execute(Robotino *robotino)
{
    static int depositoAtual;
    static int depositoDestino;
    static int movimento;
    static int contador = 0;
    static State<Robotino> * voltar;
    static int objetivoCompleto = 0;
    static bool viUmaVez;

    std::cout << "Navegando 3 contador:  " <<contador << std::endl;
    std::cout << "Navegando 3 objetivoCompleto:  " <<objetivoCompleto << std::endl;




    if (objetivoCompleto == 0){
        std::cout << "entrei:  " << std::endl;
        voltar = robotino->previous_state();
        depositoDestino = robotino->getDepositoDestino();
        depositoAtual = robotino->getDepositoAtual();
        movimento = depositoAtual - depositoDestino;
        std::cout << "movimento:  " <<movimento<< std::endl;
        objetivoCompleto = 1;
    }else if (objetivoCompleto == 1){

        if(robotino->readInductiveSensor() > 8){
            objetivoCompleto = 2;
        }
        if (movimento < 0){
            robotino->setVelocity(0,100,0);
        }else if(movimento > 0){
            robotino->setVelocity(0,-100,0);
        }

        if(movimento == 0){

            robotino->change_state(voltar);
            contador = 0;
            objetivoCompleto = 0;

        }

        if((depositoAtual + contador == depositoDestino) || (depositoAtual - contador == depositoDestino)){
            objetivoCompleto = 3;
        }else{
            objetivoCompleto = 2;
        }


    }else if(objetivoCompleto == 2){
        if(robotino->readInductiveSensor() < 8){
            objetivoCompleto = 1;
            contador++;
            robotino->setVelocity(0,0,0);
        }

    }else if(objetivoCompleto == 3){

            robotino->change_state(voltar);
            contador = 0;
            objetivoCompleto = 0;
            robotino->setVelocity(0,0,0);
    }

    std::cout << "depositoAtual:  " << depositoAtual << std::endl;
    std::cout << "depositoDestino:  " << depositoDestino << std::endl;
}

void NavegarEntreAreas3::exit(Robotino *robotino) {}
