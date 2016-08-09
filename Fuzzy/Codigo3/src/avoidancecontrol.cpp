#include "avoidancecontrol.hpp"
#include "robotino.hpp"
#include "Classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include <vector>
#include <cmath>

#define PI 3.14159265
//*****************************************************************************************************************
// AvoidanceControl
//*****************************************************************************************************************

AvoidanceControl  *AvoidanceControl::instance()
{
    static AvoidanceControl  AvoidanceControlStateInstance;
    return &AvoidanceControlStateInstance;
}

AvoidanceControl::AvoidanceControl() {}

AvoidanceControl::~AvoidanceControl() {}

void AvoidanceControl::enter(Robotino *robotino)
{
    //if(!c_AvoidanceControl01) throw std::invalid_argument("AvoidanceControl must have an owner to enter.");
    std::cout << "AvoidanceControling...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

float corrigirAngulo(float Angulo){
    if(Angulo < -180)
        return Angulo+360;
    if(Angulo > 180)
        return Angulo-360;
    return Angulo;
}

void AvoidanceControl::execute(Robotino *robotino)
{
    ClassificadorAngulo CA;
    ClassificadorDistancia CD;
    Defuzzyficador D;
    MaquinaInferencia MI;
    static std::vector<float> x,y,theta_d,dist_d,vx,vy;
    std::cout << "Running Avoidance Control...\n";
    robotino->d_e = robotino->calc_dist(robotino->x_d,robotino->odometryX(),robotino->y_d,robotino->odometryY())/10;
    robotino->theta_e = -atan2(robotino->y_d-robotino->odometryY(),robotino->x_d-robotino->odometryX())*180/PI;

    // // Tentando desviar de obstáculo
    robotino->obstacleDetectionUnit(robotino->d_obs,robotino->theta_obs);

    std::cout << "Distância do IR: " << robotino->d_obs << std::endl;


    if(robotino->d_obs < 18){
        std::cout << "Ângulo do IR antes: " << robotino->theta_e << std::endl;
        std::cout << "Teste 1: " << corrigirAngulo(corrigirAngulo(-(robotino->theta_e)+90)-robotino->theta_obs) << std::endl;
        std::cout << "Teste 2: " << corrigirAngulo(corrigirAngulo(-(robotino->theta_e)-90)-robotino->theta_obs)<< std::endl;
        if(corrigirAngulo(corrigirAngulo(-(robotino->theta_e)+70)-robotino->theta_obs) > 0){
            robotino->theta_e = robotino->theta_e-120;
            robotino->d_e = 500;
        }
        else if(corrigirAngulo(corrigirAngulo(-(robotino->theta_e)-70)-robotino->theta_obs) < 0){
            robotino->theta_e = robotino->theta_e+120;
            robotino->d_e = 500;
        }
        std::cout << "Ângulo do IR depois: " << robotino->theta_e << std::endl;
    }

    std::cout << "Dist e: " << robotino->d_e << "\n";
    std::cout << "Theta e: " << robotino->theta_e << "\n";

    CA.classificar(robotino->theta_e);
    CD.classificar(robotino->d_e);
    vector<float> pertinenciaAngulo = CA.pegarVetorPertinencia();
    vector<float> pertinenciaDistancia = CD.pegarVetorPertinencia();
    std::cout << " X: ";
     for (int i = 0; i < pertinenciaDistancia.size(); ++i)
     {
         std::cout << pertinenciaDistancia[i] << " ";
     }
     std::cout << std::endl;

    std::cout << " pertinencia Angulo: ";
     for (int i = 0; i < pertinenciaAngulo.size(); ++i)
     {
         std::cout << pertinenciaAngulo[i] << " ";
     }
     std::cout << std::endl;

    // for(unsigned int i = 0; i < pertinenciaAngulo.size(); i++){
    //     std::cout << pertinenciaAngulo[i] <<" Angulo "<<i<< "\n";
    // }
    // for(unsigned int i = 0; i < pertinenciaDistancia.size(); i++){
    //     std::cout << pertinenciaDistancia[i] <<" Distancia "<<i<<"\n";
    // }
    vector<float> saidaVx = MI.tabelaRegrasVx(pertinenciaDistancia,pertinenciaAngulo);
    vector<float> saidaVy = MI.tabelaRegrasVy(pertinenciaDistancia,pertinenciaAngulo);

    std::cout << " saidaVx: ";
     for (int i = 0; i < saidaVx.size(); ++i)
     {
         std::cout << saidaVx[i] << " ";
     }
     std::cout << std::endl;

    std::cout << " saidaVy: ";
     for (int i = 0; i < saidaVy.size(); ++i)
     {
         std::cout << saidaVy[i] << " ";
     }
     std::cout << std::endl;

    float Vx = D.centroDeMassa(saidaVx);
    float Vy = D.centroDeMassa(saidaVy);


    robotino->setVelocity(Vx,Vy,0);

    // for(unsigned int i = 0; i < saidaVx.size(); i++){
    //     std::cout << saidaVx[i] <<" Vx "<<signed(i-400)<<"\t";
    //     if(i%10==0){
    //         std::cout << "\n" ;
    //     }
    // }

    // for(unsigned int i = 0; i < saidaVy.size(); i++){
    //     std::cout << saidaVy[i] <<" Vy "<<signed(i-400)<<"\t";
    //     if(i%10==0){
    //         std::cout << "\n" ;
    //     }
    // }

    std::cout  << "Vx: " << Vx << "\n";

    std::cout  << "Vy: " << Vy << "\n";



   /** if(robotino->bumper() == true)
        robotino->exit("Bateu");
    robotino->setVelocity(100,150,0);
    robotino->obstacleDetectionUnit(robotino->d_obs,robotino->theta_obs);
    std::cout << "Dist obs: " << robotino->d_obs << "\n";
    std::cout << "Theta obs: " << robotino->theta_obs << "\n";
    robotino->d_e = robotino->calc_dist(robotino->x_d,robotino->y_d,robotino->odometryX(),robotino->odometryY());
    robotino->theta_e = robotino->odometryPhi()-robotino->theta_d;**/
    // std::cout << "Dist e: " << robotino->d_e << "\n";
    // std::cout << "Theta e: " << robotino->theta_e << "\n";
    // std::cout << "Phi: "<<robotino->odometryPhi()<< "\n";
    // std::cout << "X: "<<robotino->odometryX()<< "\n";
    // std::cout << "Y: "<<robotino->odometryY()<< "\n";
    // std::cout << "X: "<<robotino->x_d<< "\n";
    // std::cout << "Y: "<<robotino->y_d<< "\n";
    // x.push_back(robotino->odometryX());
    // y.push_back(robotino->odometryY());
    // vx.push_back(Vx);
    // vy.push_back(Vy);
    // theta_d.push_back(robotino->theta_e);
    // dist_d.push_back(robotino->d_e);
    // std::cout << " X: ";
    // for (int i = 0; i < x.size(); ++i)
    // {
    //     std::cout << x[i] << " ";
    // }
    // std::cout << std::endl;
    //     std::cout << " Y: ";
    // for (int i = 0; i < y.size(); ++i)
    // {
    //     std::cout << y[i] << " ";
    // }
    // std::cout << std::endl;
    //     std::cout << " Vx: ";
    // for (int i = 0; i < vx.size(); ++i)
    // {
    //     std::cout << vx[i] << " ";
    // }
    // std::cout << std::endl;
    //     std::cout << " vy: ";
    // for (int i = 0; i < vy.size(); ++i)
    // {
    //     std::cout << vy[i] << " ";
    // }
    // std::cout << std::endl;
    //     std::cout << " Dist: ";
    // for (int i = 0; i < dist_d.size(); ++i)
    // {
    //     std::cout << dist_d[i] << " ";
    // }
    // std::cout << std::endl;
    //     std::cout << " Theta: ";
    // for (int i = 0; i < theta_d.size(); ++i)
    // {
    //     std::cout << theta_d[i] << " ";
    // }
    // std::cout << std::endl;
}

void AvoidanceControl::exit(Robotino *robotino) {}