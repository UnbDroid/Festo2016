#include "robotino.hpp"
#include "coordenadas.hpp"
#include "fabricademapas.hpp"
#include <iostream>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <ctime>

#define VXMAX 300
#define VYMAX  300
#define OMEGAMAX 40
#define ACELERAR 2


Robotino::Robotino(const char *hostname,
    State<Robotino> *initial_state, Coordenadas pontoInicial):
    BaseCom(hostname),
    RobotBase<Robotino>(this, initial_state),
    xD(1500),
    yD(-900),
    thetaD(0),
    camera(this),
    girar(false),
    disco(false),
    devoGirarParede(false),
    seteiOdometria(false){
    // Connect
    try{
        this->start_connection();
        odometry.set(pontoInicial.get_x()*10,pontoInicial.get_y()*10,pontoInicial.get_theta());
        camera.setStreaming(true);
        construir_mapa();
        coresFaltando = std::vector<int>();
    }
    catch( const rec::robotino::com::ComException& e ){
        std::cerr << "Com Error: " << e.what() << std::endl;
        throw "Erro de conexão";
    }
    catch( const std::exception& e ){
        std::cerr << "Error: " << e.what() << std::endl;
        throw "Erro explicado acima";
    }
    catch( ... ){
        std::cerr << "Unknow Error" << std::endl;
        throw "Erro inesperado";
    }
}

void Robotino::construir_mapa(){
    FabricaDeMapas criador;
    criador.criarMapa("Modulo3",mapa);
}

Robotino::~Robotino(){
    this->disconnect();
}

bool Robotino::bumper(){
    return this->currentSensorState.bumper;
}

float Robotino::odometryX(){
    if(seteiOdometria){
        return this->odometriaX;
    }else{
        return this->currentSensorState.odometryX;
    }

}

float Robotino::odometryY(){
    if(seteiOdometria){
        return this->odometriaY;
    }else{
        return this->currentSensorState.odometryY;
    }
}

float Robotino::odometryPhi(){
    if(seteiOdometria){
        return this->odometriaPhi;
    }else{
        return this->currentSensorState.odometryPhi;
    }
}

float Robotino::motorVelocity(unsigned int motor){
    if(motor > 3)
        return 0;
    return this->currentSensorState.actualVelocity[motor];
}

float Robotino::motorPosition(unsigned int motor){
    if(motor > 3)
        return 0;
    return this->currentSensorState.actualPosition[motor];
}

float Robotino::irDistance(unsigned int IF){
    if (IF > 9)
        return -1;
    float voltage = this->currentSensorState.distanceSensor[IF];
    // Valores calculados por regressão linear
    float dist = (8.26)*voltage*voltage*voltage*voltage-55.77*voltage*voltage*voltage+137.5*voltage*voltage-152.7*voltage+75.13;
    return dist;
}

void Robotino::setMotorVelocity(unsigned int motor, float rpm){
    if(motor > 3)
        return;
    setState.speedSetPoint[motor] = rpm;
    this->setSetState(setState);
}

void Robotino::setVelocity(float vx, float vy, float omega){
    //std::cout << "Velocidade em X: " << vx <<"\n";
    //std::cout << "Velocidade em Y: " << vy <<"\n";
    //std::cout << "Velocidade angular: " << omega <<"\n";
    vx = vx*ACELERAR;
    vy = vy*ACELERAR;

    if(vx > VXMAX){
        vx = VXMAX;
    }else if(vx < -VXMAX){
        vx = -VXMAX;
    }
    if(vy > VYMAX){
        vy = VYMAX;
    }else if(vy < -VYMAX){
        vy = -VYMAX;
    }
    if(omega > OMEGAMAX){
        omega = OMEGAMAX;
    }else if(omega < -OMEGAMAX){
        omega = -OMEGAMAX;
    }
    this->omniDrive.setVelocity(vx,vy,omega);
}

void Robotino::setImage(cv::Mat image){
    //this->cameraImage = new unsigned char[tamImagem]();
    this->cameraImage = image;
}

void Robotino::setThetaR(float thetaR){
    this->girar = true;
    this->thetaR = thetaR;
}

cv::Mat Robotino::getImage(){
    cv::Mat imgTemp = cv::imread("temp.jpg",-1);//this->cameraImage;
    if(imgTemp.cols == 0 || imgTemp.rows == 0){
        return cameraImage;
    }else{
        cv::Mat img (imgTemp,cv::Rect(0,0,imgTemp.cols,imgTemp.rows - 10));
        cameraImage = img;
        return img;
    }
}

float Robotino::calcDist(float x1, float x2, float y1, float y2){
    return std::sqrt(std::pow(x1-x2,2)+std::pow(y1-y2,2));
}

void Robotino::update(){
    try{
        if(this->isConnected()){
             if(this->bumper() == true){
                //this->exit("Bateu");
            }
            state_machine.update();
            if(!this->waitForUpdate(0)) std::cout << "Falhou aqui\n";
            this->currentSensorState = this->sensorState();
            mapa.mostrar_mapa_com_robo(Coordenadas(this->odometryX()/10,-this->odometryY()/10,-this->odometryPhi()));

            float dif = std::abs(this->currentSensorState.odometryX-this->odometriaX)+std::abs(this->currentSensorState.odometryY-this->odometriaY)+std::abs(this->currentSensorState.odometryPhi-this->odometriaPhi);
            static int countOdometria = 0;

            if (seteiOdometria){
                countOdometria ++;
            }

            if(dif < 10 || countOdometria == 10){
                seteiOdometria = false;
                countOdometria = 0;
            }
            cv::imshow("Amor", this->getImage());
            cvMoveWindow("Amor",0,500);
            //std::cout << "Odometria : " << odometryPhi() << std::endl;
            cv::waitKey(1);
        }
    }
    catch( const rec::robotino::com::ComException& e ){
        std::cerr << "Com Error: " << e.what() << std::endl;
        throw "Erro de conexão";
    }
    catch( const std::exception& e ){
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Aqui\n";
        throw "Erro explicado acima";
    }catch( const char * erro){
        std::cerr << erro << std::endl;
        throw "Sair";
    }
    catch( ... ){
        std::cerr << "Unknow Error" << std::endl;
        throw "Erro inesperado";
    }
}

int Robotino::readColorSensor(unsigned int SC){
    return this->currentSensorState.dIn[SC];
}

float Robotino::readInductiveSensor(){
    return this->currentSensorState.aIn[4];
}

void Robotino::definirDestino(float x, float y){
    this->xD = x*10;
    this->yD = y*10;
}

void Robotino::setOdometry(float x, float y, float theta){
    odometry.set(x,y,theta);
    odometriaX = x;
    odometriaY = y;
    odometriaPhi = theta;
    seteiOdometria = true;
}

Coordenadas Robotino::pegarCoordenadaArea(int id, Coordenadas p){
    return mapa.coordenada_area(id,p);
}

Coordenadas Robotino::pegarCoordenadaArea(int id){
    return mapa.coordenada_area(id);
}

void Robotino::obstacleDetectionUnit(float & dObs,float & thetaObs){
    float dist;
    float min_dist = 9999;
    unsigned int i_min=-1;
    for(unsigned int i=0;i<9;i++){
        dist = this->irDistance(i);
        if(dist < min_dist){
            min_dist = dist;
            i_min = i;
        }
    }
    dObs = min_dist;
    switch(i_min){
        case IR_FRONTAL:
            thetaObs = 0;
            break;
        case IR_F_ESQUERDO:
            thetaObs = 40;
            break;
        case IR_ESQUERDO_1:
            thetaObs = 80;
            break;
        case IR_ESQUERDO_2:
            thetaObs = 120;
            break;
        case IR_T_ESQUERDO:
            thetaObs = 160;
            break;
        case IR_T_DIREITO:
            thetaObs = -160;
            break;
        case IR_DIREITO_2:
            thetaObs = -120;
            break;
        case IR_DIREITO_1:
            thetaObs = -80;
            break;
        case IR_F_DIREITO:
            thetaObs = -40;
            break;
    }
}

void Robotino::exit(const char * motive){
    throw motive;
}

void Robotino::definirObjetoAlvo(int cor){

    int yMax = -1;

    if(cor == VERMELHO){

        for (std::vector<Object>::iterator i = objetosVermelhos.begin(); i != objetosVermelhos.end(); ++i)
        {
            if(i->getYPos() > yMax){

                objetoAlvo = *i;
                yMax = i->getYPos();
            }
        }

    }

    if(cor == AMARELO){

        for (std::vector<Object>::iterator i = objetosAmarelos.begin(); i != objetosAmarelos.end(); ++i)
        {
            if(i->getYPos() > yMax){

                objetoAlvo = *i;
                yMax = i->getYPos();
            }
        }

    }

    if(cor == AZUL){

        for (std::vector<Object>::iterator i = objetosAzuis.begin(); i != objetosAzuis.end(); ++i)
        {
            if(i->getYPos() > yMax){

                objetoAlvo = *i;
                yMax = i->getYPos();
            }
        }

    }

    if(cor == TODAS){
        int yMaxR =-1, yMaxY = -1, yMaxB = -1;
        Object alvoAzul, alvoVermelho, alvoAmarelo;
        for (std::vector<Object>::iterator i = objetosAzuis.begin(); i != objetosAzuis.end(); ++i)
        {
            if(i->getYPos() > yMaxB){

                alvoAzul = *i;
                yMaxB = i->getYPos();
            }
        }
        for (std::vector<Object>::iterator i = objetosAmarelos.begin(); i != objetosAmarelos.end(); ++i)
        {
            if(i->getYPos() > yMaxY){

                alvoAmarelo = *i;
                yMaxY = i->getYPos();
            }
        }
        for (std::vector<Object>::iterator i = objetosVermelhos.begin(); i != objetosVermelhos.end(); ++i)
        {
            if(i->getYPos() > yMaxR){

                alvoVermelho = *i;
                yMaxR = i->getYPos();
            }
        }
        if(yMaxR >= yMaxB && yMaxR>= yMaxY){
            objetoAlvo = alvoVermelho;
        }else if(yMaxB >= yMaxY){
            objetoAlvo = alvoAzul;
        }else if(yMaxY > yMaxB){
            objetoAlvo = alvoAmarelo;
        }
    }
}

void Robotino::definirCorAlvo(int cor){

    string nome;

    if(cor ==   VERMELHO)
        nome = "red";
    if(cor ==   AMARELO)
        nome = "yellow";
    if(cor ==   AZUL)
        nome = "blue";
    if(cor == TODAS)
        nome = "all";

    Object objetoAux(nome);
    objetoAlvo = objetoAux;

}

void Robotino::definirLinhaAlvo(float valor, int direcao){
    vLinha = valor*10;
    lAlvo = direcao;
}

void Robotino::setCorDiscoDeposito (Object obj1, Object obj2) {

    if (areaDeposito == AREA2){
        area1disco1 = obj1;
        area1disco2 = obj2;

    }else if (areaDeposito == AREA3){
        area2disco1 = obj1;
        area2disco2 = obj2;

    }else if (areaDeposito == AREA4){
        area3disco1 = obj1;
        area3disco2 = obj2;

    }

}

void Robotino::removerCorFaltando(int cor){
    coresFaltando.erase(std::find(coresFaltando.begin(), coresFaltando.end(), cor));
    std::cout << "Perigo de dar caquinha\n";
}