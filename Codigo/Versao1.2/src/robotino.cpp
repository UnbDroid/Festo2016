#include "robotino.hpp"
#include "Coordenadas.hpp"
#include <iostream>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

Robotino::Robotino(const char *hostname,
    State<Robotino> *initial_state):
    BaseCom(hostname),
    RobotBase<Robotino>(this, initial_state),
    x_d(1500),
    y_d(-900),
    theta_d(0),
    camera(this){
    // Connect
    try
    {
        //cv::namedWindow("Amor");
        //cv::waitKey();
        this->start_connection();
        odometry.set(250,-250,0);
        //this->setImageServerPort(0);
        //camera.setComId(this->id());
        camera.setStreaming(true);
        mapa = MapaImage(200, 200, 0.5);
        construir_mapa();
    }
    catch( const rec::robotino::com::ComException& e )
    {
        std::cerr << "Com Error: " << e.what() << std::endl;
    }
    catch( const std::exception& e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch( ... )
    {
        std::cerr << "Unknow Error" << std::endl;
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
    return this->currentSensorState.odometryX;
}

float Robotino::odometryY(){
    return this->currentSensorState.odometryY;
}

float Robotino::odometryPhi(){
    return this->currentSensorState.odometryPhi*0.9;
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

float Robotino::ir_distance(unsigned int IF){
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
}

void Robotino::setImage(cv::Mat image){
    //this->cameraImage = new unsigned char[tamImagem]();
    this->cameraImage = image;
}

void Robotino::setTheta_r(float theta_r){

    this->theta_r = theta_r;
}

cv::Mat Robotino::getImage(){
    cv::Mat imgTemp = cv::imread("temp.jpg",CV_LOAD_IMAGE_COLOR);//this->cameraImage;
    cv::Mat img (imgTemp,cv::Rect(0,0,imgTemp.cols,imgTemp.rows - 10));
    return img;
}

float Robotino::calc_dist(float x1, float x2, float y1, float y2){
    return std::sqrt(std::pow(x1-x2,2)+std::pow(y1-y2,2));
}

void Robotino::update(){
    try{
        if(this->isConnected()){
            if(this->bumper() == true){
                this->exit("Bateu");
            }
            state_machine.update();
            this->waitForUpdate();
            this->currentSensorState = this->sensorState();
            mapa.mostrar_mapa_com_robo(Coordenadas(this->odometryX()/10,-this->odometryY()/10,-this->odometryPhi()));
            //cv::imshow("Amor", this->getImage());
            cv::waitKey(1);
        }
    }
    catch( const rec::robotino::com::ComException& e ){
        std::cerr << "Com Error: " << e.what() << std::endl;
    }
    catch( const std::exception& e ){
        std::cerr << "Error: " << e.what() << std::endl;
    }catch( const char * erro){
        std::cerr << erro << std::endl;
        throw "Sair";
    }
    catch( ... ){
        std::cerr << "Unknow Error" << std::endl;
    }
}

int Robotino::readColorSensor(unsigned int SC){
    return this->currentSensorState.dIn[SC];
}

float Robotino::readInductiveSensor(){
    return this->currentSensorState.aIn[4];
}

void Robotino::definirDestino(float x, float y){
    this->x_d = x*10;
    this->y_d = y*10;
}

void Robotino::setOdometry(float x, float y, float theta){
    odometry.set(x,y,theta);
}

Coordenadas Robotino::pegar_coordenada_area(int id, Coordenadas p){
    return mapa.coordenada_area(id,p);
}

Coordenadas Robotino::pegar_coordenada_area(int id){
    return mapa.coordenada_area(id);
}

void Robotino::obstacleDetectionUnit(float & d_obs,float & theta_obs){
    float dist;
    float min_dist = 9999;
    unsigned int i_min=-1;
    for(unsigned int i=0;i<9;i++){
        dist = this->ir_distance(i);
        if(dist < min_dist){
            min_dist = dist;
            i_min = i;
        }
    }
    d_obs = min_dist;
    switch(i_min){
        case IR_FRONTAL:
            theta_obs = 0;
            break;
        case IR_F_ESQUERDO:
            theta_obs = 40;
            break;
        case IR_ESQUERDO_1:
            theta_obs = 80;
            break;
        case IR_ESQUERDO_2:
            theta_obs = 120;
            break;
        case IR_T_ESQUERDO:
            theta_obs = 160;
            break;
        case IR_T_DIREITO:
            theta_obs = -160;
            break;
        case IR_DIREITO_2:
            theta_obs = -120;
            break;
        case IR_DIREITO_1:
            theta_obs = -80;
            break;
        case IR_F_DIREITO:
            theta_obs = -40;
            break;
    }
}

void Robotino::exit(const char * motive){
    throw motive;
}