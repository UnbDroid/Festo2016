#include "robotino.hpp"
#include "coordenadas.hpp"
#include <iostream>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <ctime>
#define PI 3.14159265f


Robotino::Robotino(const char *hostname,
    State<Robotino> *initial_state):
    BaseCom(hostname),
    RobotBase<Robotino>(this, initial_state),
    xD(1500),
    yD(-900),
    thetaD(0),
    X(0),
    Y(0),
    Theta(0),
    camera(this),
    disco(false){
    // Connect
    try{
        xPriori = Mat::zeros(3, 1, CV_64F);
        PPriori = Mat::eye(3, 3, CV_64F);
        PPosteriori = Mat::eye(3, 3, CV_64F);
        H = Mat::eye(3, 3, CV_64F);
        U = Mat::zeros(3,1,CV_64F);

        // Confiancas
        R = Mat::eye(3, 3, CV_64F)*0.25;
        Q = Mat::eye(3, 3, CV_64F)*0.000000001;

        jacobianoFx = Mat::zeros(3,3,CV_64F);

        this->start_connection();

        odometry.set(250,-250,0);

        camera.setStreaming(true);

        mapa = Mapa(200, 200, 0.5);
        construir_mapa();

        timer.start();
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
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,198.5), Coordenadas(200,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,200),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(48.5,48.5),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(49.5,2),Coordenadas(51.5,51.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,49.5),Coordenadas(51.5,51.5),mapa.LINHA);

    // Area de deposito
    mapa.inserir_retangulo(Coordenadas(151,151),Coordenadas(198,198),3);

    // Linhas da area de deposito
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(150.5,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(198,150.5),mapa.LINHA);

    // Area central
    mapa.inserir_retangulo(Coordenadas(79,69),Coordenadas(122.5,132.5),4);

    // Linhas da area central
    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(125,68.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(123,66.5),Coordenadas(125,135),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(78.5,135),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(76.5,133),Coordenadas(125,135),mapa.LINHA);
}

Robotino::~Robotino(){
    this->disconnect();
}

bool Robotino::bumper(){
    return this->currentSensorState.bumper;
}

float Robotino::odometryX(){
    //return this->currentSensorState.odometryX;
    return X;
}

float Robotino::odometryY(){
    //return this->currentSensorState.odometryY;
    return Y;
}

float Robotino::odometryPhi(){
    //return this->currentSensorState.odometryPhi;
    return Theta;
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
    this->omniDrive.setVelocity(vx,vy,omega);
    Vx = vx;
    Vy = vy;
    W = omega;
    U.at<double>(0,0) = Vx;
    U.at<double>(1,0) = Vy;
    U.at<double>(2,0) = W;
}

void Robotino::setImage(cv::Mat image){
    //this->cameraImage = new unsigned char[tamImagem]();
    this->cameraImage = image;
}

void Robotino::setThetaR(float thetaR){

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
                this->exit("Bateu");
            }
            state_machine.update();

            t = timer.msecsElapsed()/1000.0f;

            timer.start();
            if(!this->waitForUpdate(0)) std::cout << "Falhou aqui\n";
            this->currentSensorState = this->sensorState();
            //mapa.mostrar_mapa_com_robo(Coordenadas(this->odometryX()/10,-this->odometryY()/10,-this->odometryPhi()));
            mapa.mostrar_mapa_com_robo(Coordenadas(X/10,-Y/10,-Theta));
            std::cout << X << "\n";
            std::cout << Y << "\n";
            std::cout << Theta << "\n";
            FiltroKalman();
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

}

void Robotino::definirCorAlvo(int cor){

    string nome;

    if(cor ==   VERMELHO)
        nome = "red";
    if(cor ==   AMARELO)
        nome = "yellow";
    if(cor ==   AZUL)
        nome = "blue";

    Object objetoAux(nome);
    objetoAlvo = objetoAux;

}

void Robotino::definirLinhaAlvo(float valor, int direcao){
    vLinha = valor*10;
    lAlvo = direcao;
}

void Robotino::FiltroKalman () {
    calcularJacobiano();
    cv::Mat TJacobiano;
    cv::Mat TH;
    cv::Mat IKH;
    cv::Mat TIKH;
    cv::Mat TK;
    cv::Mat y = Mat::zeros(3,1,CV_64F);
    y.at<double>(0,0) = this->currentSensorState.odometryX;
    y.at<double>(1,0) = this->currentSensorState.odometryY;
    y.at<double>(2,0) = this->currentSensorState.odometryPhi;
    cv::Mat I = Mat::eye(3,3,CV_64F);
    transpose(jacobianoFx,TJacobiano);
    transpose(H,TH);
    // Estimacao
    xPriori = funcaoNaoLinear();
    PPriori = jacobianoFx*PPosteriori*TJacobiano+Q;
    // Ganho de Kalman
    cv::Mat K = PPriori*TH*(H*PPriori*TH+R).inv();

    // Correcao
    IKH = (I-K*H);
    transpose(IKH,TIKH);
    transpose(K,TK);
    xPosteriori = xPriori+K*(y-H*xPriori);
    PPosteriori = IKH*PPriori*TIKH+K*R*TK;

    X = xPosteriori.at<double>(0,0);
    Y = xPosteriori.at<double>(1,0);
    Theta = xPosteriori.at<double>(2,0);

}

cv::Mat Robotino::funcaoNaoLinear(){
    cv::Mat R = Mat::eye(3,3,CV_64F);
    R.at<double>(0,0) = std::cos(Theta*PI/180);
    R.at<double>(0,1) = -std::sin(Theta*PI/180);
    R.at<double>(0,2) = 0;
    R.at<double>(1,0) = std::sin(Theta*PI/180);
    R.at<double>(1,1) = std::cos(Theta*PI/180);
    R.at<double>(1,2) = 0;
    R.at<double>(2,0) = 0;
    R.at<double>(2,1) = 0;
    R.at<double>(2,2) = 1;
    return xPosteriori+R*U*t;
}

void Robotino::calcularJacobiano(){
    std::cerr << "Comeca a treta\n";
    jacobianoFx.at<double>(0,0) = 1;
    std::cerr << "Comeca a treta2\n";
    jacobianoFx.at<double>(0,1) = 0;
    std::cerr << "Acho que aqui\n";
    jacobianoFx.at<double>(0,2) = t*(-std::sin(Theta*PI/180)*Vx-std::cos(Theta*PI/180)*Vy);
    std::cerr << "Porra\n";
    jacobianoFx.at<double>(1,0) = 0;
    jacobianoFx.at<double>(1,1) = 1;
    jacobianoFx.at<double>(1,2) = t*(std::cos(Theta*PI/180)*Vx-std::sin(Theta*PI/180)*Vy);
    jacobianoFx.at<double>(2,0) = 0;
    jacobianoFx.at<double>(2,1) = 0;
    jacobianoFx.at<double>(2,2) = 0;
}