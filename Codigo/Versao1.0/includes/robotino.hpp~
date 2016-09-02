#ifndef ROBOTINO_HPP
#define ROBOTINO_HPP

#include "rec/robotino/com/all.h"
#include "rec/robotino/com/JPGCamera.h"
#include "basecom.hpp"
#include "robotbase.hpp"

class MyCamera:public JPGCamera{
    /*void imageReceivedEvent(const unsigned char* data,
                                                                     unsigned int dataSize,
                                                                                                 unsigned int width,
                                                                                                 unsigned int height,
                                                                                                 unsigned int numChannels,
                                                                                                 unsigned int bitsPerChannel,
                                                                                                 unsigned int step){
        std::cout << "Imagem recebida\n";
    }*/
    void jpgReceivedEvent( const unsigned char* jpgData,
                                  unsigned int jpgDataSize ){
        std::cout << "Imagem recebida\n";
    }
};

class Robotino: public BaseCom, public RobotBase<Robotino>{
public:
    Robotino(const char *hostname,
                State<Robotino> *initial_state);

    ~Robotino();

    void update();

    void exit(const char * motive);

    enum Motor: unsigned int {
        M_ESQUERDO = 0,
        M_TRASEIRO = 1,
        M_DIREITO = 2
    };
    enum Infra: unsigned int {
        IR_FRONTAL = 0,
        IR_F_ESQUERDO = 1,
        IR_ESQUERDO_1 = 2,
        IR_ESQUERDO_2 = 3,
        IR_T_ESQUERDO = 4,
        IR_T_DIREITO = 5,
        IR_DIREITO_2 = 6,
        IR_DIREITO_1 = 7,
        IR_F_DIREITO = 8
    };

    void definirEstado();

    // Return the bumper state
    bool bumper();

    // Odometry values
    float odometryX();
    float odometryY();
    float odometryPhi();

    // Odometer values
    float motorVelocity(unsigned int);
    float motorPosition(unsigned int);

    // IR Sensors
    float ir_distance(unsigned int);

    // Set individuals positions RPM
    void setMotorVelocity(unsigned int, float);

    //Set velocitys in X, Y and Omega
    void setVelocity(float, float, float);

    void obstacleDetectionUnit(float &, float &);

    // Calculate distance
    float calc_dist(float x1, float y1, float x2, float y2);

    // Variaveis necessárias
    float d_obs;
    float theta_obs;
    float x_d;
    float y_d;
    float theta_d;
    float d_e;
    float theta_e;

private:
    OmniDrive omniDrive;
    rec::iocontrol::remotestate::SensorState currentSensorState;
    rec::iocontrol::remotestate::SetState setState;
    Odometry odometry;
public:
    MyCamera camera;

};


#endif              /* ROBOTINO_HPP */