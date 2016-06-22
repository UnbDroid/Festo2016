#include "robotino.hpp"
#include <cmath>

Robotino::Robotino(const char *hostname,
    State<Robotino> *initial_state):
    BaseCom(hostname),
    RobotBase<Robotino>(this, initial_state),
    x_d(1600),
    y_d(900),
    theta_d(45){
    // Connect
    try
    {
        this->start_connection();
        odometry.set(0,0,0);
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
    return this->currentSensorState.odometryPhi;
}

float Robotino::motorVelocity(unsigned int motor){
    if(motor > 3)
        return 0;
    return this->currentSensorState.actualVelocity[motor];
}

float Robotino::motorPosition(unsigned int motor){
    if(motor > 3)
        return 0;
    return this->currentSensorState.actualVelocity[motor];
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

float Robotino::calc_dist(float x1, float x2, float y1, float y2){
    return std::sqrt(std::pow(x1-x2,2)+std::pow(y1-y2,2));
}

void Robotino::update(){
    try{
        if(this->isConnected()){
            state_machine.update();
            this->waitForUpdate();
            this->currentSensorState = this->sensorState();
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
            theta_obs = 40;
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