#include "irparaponto.hpp"
#include "robotino.hpp"
#include "classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#define PI 3.14159265
#define FATOR_VELOCIDADE  5
#define limiarAfastamento 7
#define limiarIdeal 9
#define Kpir 10

//*****************************************************************************************************************
// IrParaPonto
//*****************************************************************************************************************

IrParaPonto  *IrParaPonto::instance()
{
    static IrParaPonto  IrParaPontoStateInstance;
    return &IrParaPontoStateInstance;
}

IrParaPonto::IrParaPonto() {}

IrParaPonto::~IrParaPonto() {}

void IrParaPonto::enter(Robotino *robotino)
{
    std::cout << "Indo para o ponto...\n";
}

void IrParaPonto::execute(Robotino *robotino)
{
    float direcao;
    float vx;
    static int processoCarregamento = 0;
    static State<Robotino> * voltar;
    static bool girei = false;

    float te = robotino->irDistance(Robotino::IR_T_ESQUERDO);
    float td = robotino->irDistance(Robotino::IR_T_DIREITO);

    std::cout << "Running IrParaPonto...\n";


    if(robotino->carregandoDisco()){
        if(processoCarregamento == 0){
            direcao = atan2(robotino->yD-robotino->odometryY(),robotino->xD-robotino->odometryX())*180/PI;
            robotino->setThetaR(direcao);
            voltar = robotino->previous_state();
            girei = true;
            //robotino->change_state(Girar::instance());
            processoCarregamento = 1;
        }else if(processoCarregamento == 1){
            if(robotino->irDistance(Robotino::IR_FRONTAL) < limiarAfastamento){
                processoCarregamento = 2;
            }else{
                processoCarregamento = 1;
            }
        }
    }else{
        processoCarregamento = 1;
    }

    if(processoCarregamento == 1){
        std::cout << "Processo normal\n";
        ClassificadorAngulo CA;
        ClassificadorDistancia CD;
        Defuzzyficador D;
        MaquinaInferencia MI;

        // Calculando a distancia e o angulo para o alvo
        robotino->dE = robotino->calcDist(robotino->xD,robotino->odometryX(),robotino->yD,robotino->odometryY())/10;
        robotino->thetaE = -atan2(robotino->yD-robotino->odometryY(),robotino->xD-robotino->odometryX())*180/PI;

        // Fuzzificando os valores de angulo e distancia desejados
        CA.classificar(robotino->thetaE);
        CD.classificar(robotino->dE);
        vector<float> pertinenciaAngulo = CA.pegarVetorPertinencia();
        vector<float> pertinenciaDistancia = CD.pegarVetorPertinencia();

        // Gerando regras para os valores com a Maquina de Inferencia
        vector<float> saidaVx = MI.tabelaRegrasVx(pertinenciaDistancia,pertinenciaAngulo);
        vector<float> saidaVy = MI.tabelaRegrasVy(pertinenciaDistancia,pertinenciaAngulo);

        //  Defuzzificando os valores
        float Vx = D.centroDeMassa(saidaVx);
        float Vy = D.centroDeMassa(saidaVy);

        // Calculo velocidade utilizando theta
        Coordenadas velocidades_globais(Vx,Vy);
        Coordenadas velocidades_robo = velocidades_globais.mudar_referencia(0,0,(robotino->odometryPhi()));

        Vx = velocidades_robo.get_x();
        Vy = velocidades_robo.get_y();


        // Falando para o robo as velocidades que ele deve se mover
        robotino->setVelocity(FATOR_VELOCIDADE*Vx,FATOR_VELOCIDADE*Vy,0);

        // Se tiver chegado ao alvo, voltar para o estado anterior
        std::cout << "D_E "<<robotino->dE<<"...\n";
        std::cout << "X_D "<<robotino->xD<<"...\n";
        std::cout << "Y_D "<<robotino->yD<<"...\n";
        std::cout << "X:  "<<robotino->odometryX()<<"...\n";
        std::cout << "Y:  "<<robotino->odometryY()<<"...\n";
        std::cout << "Vx:  "<<FATOR_VELOCIDADE*Vx<<"...\n";
        std::cout << "Vy:  "<<FATOR_VELOCIDADE*Vy<<"...\n";
        if(girei && robotino->dE < 1){
            robotino->change_state(voltar);
            girei = false;
            processoCarregamento = 0;
        }else if(robotino->dE < 1){
            voltar = robotino->previous_state();
            robotino->change_state(Girar::instance());
            girei = true;
        }
    }else if(processoCarregamento == 2){
        std::cout << "Eu estou aqui\n";
        float erroDist = robotino->irDistance(Robotino::IR_FRONTAL) - limiarIdeal;
        vx = -Kpir*erroDist;
        robotino->setVelocity(vx,0,0);
        if(erroDist < 1){
            processoCarregamento = 1;
        }
    }
}

void IrParaPonto::exit(Robotino *robotino) {
    std::cout << "Cheguei no ponto...\n";
    robotino->setVelocity(0,0,0);
    usleep(500000);
}
