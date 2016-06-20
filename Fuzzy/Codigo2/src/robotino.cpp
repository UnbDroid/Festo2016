#include "robotino.hpp"

Robotino::Robotino(const char *hostname,
    State<Robotino> *initial_state):
    BaseCom(hostname),
    RobotBase<Robotino>(this, initial_state){
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

void Robotino::exit(const char * motive){
    throw motive;
}