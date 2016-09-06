#include "controleposicao.hpp"
#include "robotino.hpp"
#include "Coordenadas.hpp"
#include <fstream>
#include <iostream>
//*****************************************************************************************************************
// ControlarPosicao
//*****************************************************************************************************************

#define KpX 2.5
#define KiX 0.5*0

#define KpY 2.5
#define KiY 0.2*0

#define KpTheta 0.4*0
#define KiTheta 0.1*0

#define limiar 10
#define dt 0.01

ControlarPosicao  *ControlarPosicao::instance()
{
    static ControlarPosicao  ControlarPosicaoStateInstance;
    return &ControlarPosicaoStateInstance;
}

ControlarPosicao::ControlarPosicao() {}

ControlarPosicao::~ControlarPosicao() {}

void ControlarPosicao::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado ControlarPosicao...\n";
}

void ControlarPosicao::execute(Robotino *robotino)
{
    // Fazer o controlador para o robô se manter no theta_r
    float w,Vx,Vy,
            erroX          = -(robotino->odometryX()     - robotino->x_d),
            erroY          = -(robotino->odometryY()     - robotino->y_d),
            erroTheta   = (robotino->odometryPhi()  - robotino->theta_r);
    static float   erro_intX = 0,
                        erro_intY = 0,
                        erro_intTheta = 0;
    static vector<float> v_w,v_Vx,v_Vy,v_erroX,v_erroY,v_erroTheta,v_Phi,v_X,v_Y;

    std::cout << "----------------------------------------" << "\n";
    std::cout << "X: " << robotino->odometryX() << "\n";
    std::cout << "Referencia: "<< robotino->x_d << "\n";
    std::cout << "Erro: " << erroX << "\n";

    std::cout << "Y: " << robotino->odometryY() << "\n";
    std::cout << "Referencia: "<< robotino->y_d << "\n";
    std::cout << "Erro: " << erroY << "\n";

    std::cout << "Phi: " << robotino->odometryPhi() << "\n";
    std::cout << "Referencia: "<< robotino->theta_r << "\n";
    std::cout << "Erro: " << erroTheta << "\n";

    erro_intX += erroX*dt;
    erro_intY += erroY*dt;
    erro_intTheta += erroTheta*dt;

    Vx  = KpX*erroX+KiX*erro_intX;
    Vy  = KpY*erroY+KiY*erro_intY;
    w   = -(KpTheta*erroTheta+KiTheta*erro_intTheta);

    Coordenadas velocidades_globais(Vx,Vy);
    Coordenadas velocidades_robo = velocidades_globais.mudar_referencia(0,0,(robotino->odometryPhi()));

    std::cout << "Vx: " << Vx << "\n";
    std::cout << "Vy: " << Vy << "\n";
    std::cout << "W: " << w << "\n";

    robotino->setVelocity(Vx,Vy,w);

    v_w.push_back(w);
    v_Vx.push_back(Vx);
    v_Vy.push_back(Vx);
    v_erroX.push_back(erroX);
    v_erroY.push_back(erroY);
    v_erroTheta.push_back(erroTheta);
    v_Phi.push_back(robotino->odometryPhi());
    v_X.push_back(robotino->odometryX());
    v_Y.push_back(robotino->odometryY());

    if (std::abs(erroX) + std::abs(erroY) < limiar){
             erro_intX = 0;
             erro_intY = 0;
             erro_intTheta = 0;
             std::ofstream myfile;
             myfile.open ("example.txt");
             myfile << "X = [";
             for (std::vector<float>::iterator i = v_X.begin(); i != v_X.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "Y = [";
             for (std::vector<float>::iterator i = v_Y.begin(); i != v_Y.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "Phi = [";
             for (std::vector<float>::iterator i = v_Phi.begin(); i != v_Phi.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "Vx = [";
             for (std::vector<float>::iterator i = v_Vx.begin(); i != v_Vx.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "Vy = [";
             for (std::vector<float>::iterator i = v_Vy.begin(); i != v_Vy.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "W = [";
             for (std::vector<float>::iterator i = v_w.begin(); i != v_w.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "erroX = [";
             for (std::vector<float>::iterator i = v_erroX.begin(); i != v_erroX.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "erroY = [";
             for (std::vector<float>::iterator i = v_erroY.begin(); i != v_erroY.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;
             myfile << "erroTheta = [";
             for (std::vector<float>::iterator i = v_erroTheta.begin(); i != v_erroTheta.end(); ++i)
             {
                myfile << *i <<" ";
             }
             myfile <<"]"<< std::endl;

             //myfile << v_X;// << v_Y << v_Phi << v_Vx << v_Vy << v_w << v_erroX << v_erroY << v_erroTheta;
             myfile.close();
             robotino->change_state(robotino->previous_state());
    }
}

void ControlarPosicao::exit(Robotino *robotino) {
    std::cout << "Cheguei na posicao...\n";
    robotino->setVelocity(0,0,0);
}
