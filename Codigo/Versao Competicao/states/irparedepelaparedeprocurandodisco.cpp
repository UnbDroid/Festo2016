#include "irparedepelaparedeprocurandodisco.hpp"
#include "robotino.hpp"
#include "girar.hpp"
#include "identificarcor.hpp"

#define Kpx 2
#define Kpy 10
#define Kiy 0
#define dt 0.01
#define limiar 2
#define limiar2 0.5
#define R 20
#define PI 3.14159265
#define Kp 5
#define Ki 1
#define minFrames 1

//*****************************************************************************************************************
// IrParedePelaParedeProcurandoDisco
//*****************************************************************************************************************

IrParedePelaParedeProcurandoDisco  *IrParedePelaParedeProcurandoDisco::instance()
{
    static IrParedePelaParedeProcurandoDisco  IrParedePelaParedeProcurandoDiscoStateInstance;
    return &IrParedePelaParedeProcurandoDiscoStateInstance;
}

IrParedePelaParedeProcurandoDisco::IrParedePelaParedeProcurandoDisco() {}

IrParedePelaParedeProcurandoDisco::~IrParedePelaParedeProcurandoDisco() {}

void IrParedePelaParedeProcurandoDisco::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IrParedePelaParedeProcurandoDisco...\n";
}

void IrParedePelaParedeProcurandoDisco::execute(Robotino *robotino)
{
    float refDist = robotino->getRefDistParede();
    float refDistTras = robotino->getRefDistTrasParede();

    float   Vy = 0, Vx = 0;
    float direcao = 0;
    float erroDist = 0;
    float erroDistTras = 0;
    int paredeAlvo = robotino->paredeAlvo();
    static bool girei = robotino->getNaoDevoGirarParede();
    static float erro_intDist = 0;
    static bool ajuste = false;
    static bool pronto = false;
    static bool entrei = true;
    static State<Robotino> * voltar;
    static int contadorFramesAmarelos = 0, contadorFramesAzuis = 0, contadorFramesVermelhos = 0;

    static float a = std::sin(60*PI/180)/std::sin(80*PI/180);
    static float cos20 = std::cos(20*PI/180);
    static float K = R*(a-1);
    static float erro_int = 0;
    float w;
    float e1 = robotino->irDistance(Robotino::IR_ESQUERDO_1);
    float e2 = robotino->irDistance(Robotino::IR_ESQUERDO_2);
    float ref_e1 = e2*a+K;
    float d1 = robotino->irDistance(Robotino::IR_DIREITO_1);
    float d2 = robotino->irDistance(Robotino::IR_DIREITO_2);
    float te = robotino->irDistance(Robotino::IR_T_ESQUERDO);
    float td = robotino->irDistance(Robotino::IR_T_DIREITO);
    float ref_d1 = 1.15*(d2*a+K);
    float distancia_da_esquerda, distancia_da_direita, distancia_de_tras;
    float erro;

    if (entrei) {
        robotino->objetosAmarelos.clear();
        robotino->objetosVermelhos.clear();
        robotino->objetosAzuis.clear();
        entrei=false;
    }
    if (girei) {
        robotino->change_state(IdentificarCor::instance());
    }


    // Anda até a parede desejada

    if ((paredeAlvo == Robotino::NORTEN90  || paredeAlvo == Robotino::OESTE0 || paredeAlvo == Robotino::SUL90 || paredeAlvo == Robotino::LESTE180) && girei && !ajuste ) {

        distancia_da_esquerda = ((e1+ref_e1+2*R)*cos20)/2;
        erroDist = (distancia_da_esquerda-20) - refDist;
        erro_intDist += erroDist*dt;
        Vy = Kpy*erroDist+Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;

        distancia_de_tras= ((te+td+2*R)*cos20)/2;

        erroDistTras = refDistTras - (distancia_de_tras -20);

        Vx = Kpx*erroDistTras;

        erro = te - td;
        w = Kp*erro;

        robotino->setVelocity(Vx,Vy, w);

        if (std::abs(erroDist) < limiar) {
            std::cout << "Andei ate a parede" << std::endl;
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }

    } else if ((paredeAlvo == Robotino::SULN90  || paredeAlvo == Robotino::LESTE0 || paredeAlvo == Robotino::NORTE90  || paredeAlvo == Robotino::OESTE180) && girei && !ajuste) {

        distancia_da_direita = ((d1+ref_d1+2*R)*cos20)/2;
        erroDist = (distancia_da_direita-20) - refDist;
        erro_intDist += erroDist*dt;
        Vy = -Kpy*erroDist-Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;

        distancia_de_tras= ((te+td+2*R)*cos20)/2;

        std::cout << "distancia_de_tras: " << distancia_de_tras <<"\n";

        erroDistTras = refDistTras - (distancia_de_tras - 20);

        Vx = Kpx*erroDistTras;

        erro = te - td;
        w = Kp*erro;

        robotino->setVelocity(Vx,Vy, w);

        if (std::abs(erroDist) < limiar ) {
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }
    }


    // Gira para ficar paralelo à parede desejada

    if (paredeAlvo == Robotino::NORTEN90 && !girei){
        direcao = -90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::NORTE90 && !girei){
        direcao = 90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if(paredeAlvo == Robotino::SULN90 && !girei){
        direcao = -90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::SUL90 && !girei){
        direcao = 90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if (paredeAlvo == Robotino::OESTE0 && !girei){
        direcao = 0;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::OESTE180 && !girei){
        direcao = 179;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if (paredeAlvo == Robotino::LESTE0 && !girei){
        direcao = 0;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if(paredeAlvo == Robotino::LESTE180 && !girei){
        direcao = 179;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }


    // Se alinha na parede desejada

    if ((paredeAlvo == Robotino::NORTEN90  || paredeAlvo == Robotino::OESTE0 || paredeAlvo == Robotino::SUL90 || paredeAlvo == Robotino::LESTE180) && ajuste ){

        erro = (e1-ref_e1);
        erro_int += erro*dt;
        w = Kp*erro+Ki*erro_int;
        robotino->setVelocity(0,0,w);

        std::cout<< "Esquerda 1: " << e1 << std::endl;
        std::cout<< "RefEsquerda 1: " << ref_e1 << std::endl;
        std::cout<< "Esquerda 2: " << e2 << std::endl;

        if (std::abs(erro) < limiar2){
              std::cout << "Alhinhei na parede" << std::endl;
            girei  = false;
            robotino->setNaoDevoGirarParede(girei);
            ajuste = false;
            pronto = false;
            erro_intDist = 0;
            entrei = true;
            erro_int = 0;
            robotino->setVelocity(0,0,0);
            distancia_da_esquerda = ((e1+ref_e1+2*R)*cos20)/2;
            std::cout << "Distância da esquerda: " << distancia_da_esquerda << "\n";
            if (paredeAlvo == Robotino::OESTE0) {
                robotino->setOdometry(robotino->odometryX(),-(distancia_da_esquerda*10+15),0);
            }
            if (paredeAlvo == Robotino::NORTEN90) {
                robotino->setOdometry((robotino->getAlturaMapa())*10 -(distancia_da_esquerda*10+15),robotino->odometryY(),-90);
            }
             if (paredeAlvo == Robotino::SUL90) {
                robotino->setOdometry((distancia_da_esquerda*10+15),robotino->odometryY(),90);
            }
             if (paredeAlvo == Robotino::LESTE180) {
                robotino->setOdometry(robotino->odometryX(),-((robotino->getLarguraMapa())*10 -(distancia_da_esquerda*10+15)),180);
            }
            robotino->change_state(voltar);

        }

    } else if ((paredeAlvo == Robotino::SULN90  || paredeAlvo == Robotino::LESTE0 || paredeAlvo == Robotino::NORTE90  || paredeAlvo == Robotino::OESTE180) && ajuste ) {

        erro = (d1-ref_d1);
        erro_int += erro*dt;
        w = -Kp*erro-Ki*erro_int;
        robotino->setVelocity(0,0,w);


        std::cout<< "Direita 1: " << d1 << std::endl;
        std::cout<< "RefDireita 1: " << ref_d1 << std::endl;
        std::cout<< "Direita 2: " << d2 << std::endl;

        if (std::abs(erro) < limiar2){
            girei = false;
            robotino->setNaoDevoGirarParede(girei);
            ajuste = false;
            pronto = false;
            erro_intDist = 0;
            erro_int = 0;
            entrei = true;
            robotino->setVelocity(0,0,0);
            distancia_da_direita = ((d1+ref_d1+2*R)*cos20)/2;
            std::cout << "Distância da direita: " << distancia_da_direita << "\n";
            if (paredeAlvo == Robotino::SULN90) {
                robotino->setOdometry((distancia_da_direita*10+15),robotino->odometryY(),-90);
            }
            if (paredeAlvo == Robotino::LESTE0) {
                robotino->setOdometry(robotino->odometryX(),-((robotino->getLarguraMapa()) * 10-(distancia_da_direita*10+15)),0);
            }
            if (paredeAlvo == Robotino::NORTE90) {
                robotino->setOdometry((robotino->getAlturaMapa()*10 - (distancia_da_direita*10+15)),robotino->odometryY(),90);
            }
            if (paredeAlvo == Robotino::OESTE180) {
                robotino->setOdometry(robotino->odometryX(),-((distancia_da_direita*10+15)),180);
            }

            robotino->change_state(voltar);

        }

    }

    if (robotino->objetosAmarelos.size() > 0 || robotino->objetosVermelhos.size() > 0 || robotino->objetosAzuis.size() > 0 ) {

        if(robotino->objetosAmarelos.size() > 0){
            std::cout << "Vi um bumbum amaerlo \n";
            contadorFramesAmarelos++;
        }else{
            std::cout << "Nao vi um bumbum amaerlo \n";
            contadorFramesAmarelos = 0;
        }

        if(robotino->objetosVermelhos.size() > 0){
            std::cout << "Vi um bumbum vermelho \n";
            contadorFramesVermelhos++;
        }else{
            std::cout << "Nao vi um bumbum vermelho \n";
            contadorFramesVermelhos = 0;

        }

        if(robotino->objetosAzuis.size() > 0){
            std::cout << "Vi um bumbum azuis\n";
            contadorFramesAzuis++;
        }else{
            std::cout << "Nap vi um bumbum azuis \n";
            contadorFramesAzuis = 0;
        }

        std::cout << "Seu Bumbum Amarelo: "<< contadorFramesAmarelos <<"\n";
        std::cout << "Seu Bumbum Azul: "<< contadorFramesAzuis <<"\n";
        std::cout << "Seu Bumbum Vermelho: "<< contadorFramesVermelhos <<"\n";

        if(contadorFramesAzuis > minFrames || contadorFramesAmarelos > minFrames || contadorFramesVermelhos > minFrames){
            robotino->definirObjetoAlvo(Robotino::TODAS);
            robotino->change_state(voltar);
            girei = false;
            robotino->setNaoDevoGirarParede(girei);
            ajuste = false;
            pronto = false;
            erro_intDist = 0;
            erro_int = 0;
            entrei = true;
            contadorFramesAzuis = 0;
            contadorFramesAmarelos  = 0;
            contadorFramesVermelhos = 0;
            robotino->setVelocity(0,0,0);
        }
    }

}

void IrParedePelaParedeProcurandoDisco::exit(Robotino *robotino) {}
