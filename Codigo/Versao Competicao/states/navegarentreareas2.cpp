#include "navegarentreareas2.hpp"
#include "irparaponto.hpp"
#include "ajustarnaslinhasnavegando.hpp"
#include "ajustarnaslinhas.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "irparalinha.hpp"
#include "andarpelaparedeatelinha.hpp"

#include "robotino.hpp"
//*****************************************************************************************************************
// NavegarEntreAreas2
//*****************************************************************************************************************

NavegarEntreAreas2  *NavegarEntreAreas2::instance()
{
    static NavegarEntreAreas2  NavegarEntreAreas2StateInstance;
    return &NavegarEntreAreas2StateInstance;
}

float coordenadaArea(int area, Robotino * robotino){
    Coordenadas coord = robotino->pegarCoordenadaArea(area);
    return -coord.get_y();
}

NavegarEntreAreas2::NavegarEntreAreas2() {}

NavegarEntreAreas2::~NavegarEntreAreas2() {}

void NavegarEntreAreas2::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado NavegarEntreAreas2...\n";
}

void NavegarEntreAreas2::execute(Robotino *robotino)
{
    static int depositoAtual;
    static int depositoDestino;
    static int movimento;
    static int contador = 1;
    static State<Robotino> * voltar;
    static int objetivoCompleto = 0;

    std::cout << "Navegando 2 contador:  " <<contador << std::endl;
    std::cout << "Navegando 2 objetivoCompleto:  " <<objetivoCompleto << std::endl;

    if (objetivoCompleto == 0){

        std::cout << "entrei:  " << std::endl;
        voltar = robotino->previous_state();
        depositoDestino = robotino->getDepositoDestino();
        depositoAtual = robotino->getDepositoAtual();
        movimento = depositoAtual - depositoDestino;
        std::cout << "movimento:  " <<movimento<< std::endl;

        objetivoCompleto = 1;

        if(movimento == 0){

            robotino->change_state(voltar);
            contador = 1;
            objetivoCompleto = 0;

        }


    }else if(objetivoCompleto == 1){
        if (movimento < 0){
            robotino->setThetaR(-90);
            robotino->change_state(Girar::instance());
        }else if(movimento > 0){
            robotino->setThetaR(90);
            robotino->change_state(Girar::instance());
        }

        objetivoCompleto = 2;

    }else if(objetivoCompleto == 2){

        robotino->definirParedeAlvo(999);
        robotino->setDistParede(100);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivoCompleto = 3;

    }else if(objetivoCompleto == 3){

        robotino->change_state(AjustarNasLinhasNavegando::instance());
        objetivoCompleto = 4;

    }else if(objetivoCompleto == 4){

        if (movimento < 0){
            robotino->definirLinhaAlvo(coordenadaArea(depositoAtual+contador,robotino), Robotino::VERTICAL);

        }else if(movimento > 0){
            robotino->definirLinhaAlvo(coordenadaArea(depositoAtual-contador,robotino), Robotino::VERTICAL);
        }

        robotino->change_state(IrParaLinha::instance());

        if((depositoAtual + contador == depositoDestino) || (depositoAtual - contador == depositoDestino)){
            objetivoCompleto = 5;
        }else{
            contador++;
            objetivoCompleto = 2;
        }

    }else if(objetivoCompleto == 5){
        std::cout << "Navegando 2 cheguei na linha de destino :  " << std::endl;
        robotino->definirDestino(robotino->odometryX()/10+15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());

        objetivoCompleto = 6;

    }else if(objetivoCompleto == 6){

        if (movimento < 0){
            robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 - 10);

        }else if(movimento > 0){
            robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 + 10);
        }

        robotino->change_state(IrParaPonto::instance());

        objetivoCompleto = 7;

    }else if(objetivoCompleto == 7){
        std::cout << "Navegando 2 girar para a frente da area de destino :  " << std::endl;
        robotino->setThetaR(180);
        robotino->change_state(Girar::instance());

        objetivoCompleto = 8;

    }else if(objetivoCompleto == 8){

        std::cout << "Navegando 2 alinhando nas linhas para a area de destino:  " << std::endl;
        robotino->change_state(AjustarNasLinhas::instance());

        objetivoCompleto = 9;

    }else if(objetivoCompleto == 9){

            robotino->change_state(voltar);
            contador = 1;
            objetivoCompleto = 0;

    }

    std::cout << "depositoAtual:  " << depositoAtual << std::endl;
    std::cout << "depositoDestino:  " << depositoDestino << std::endl;
}

void NavegarEntreAreas2::exit(Robotino *robotino) {}
