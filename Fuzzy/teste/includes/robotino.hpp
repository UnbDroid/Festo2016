#ifndef ROBOTINO_HPP
#define ROBOTINO_HPP

#include "rec/robotino/com/all.h"
#include "basecom.hpp"
#include "robotbase.hpp"

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
        IF_FRONTAL = 0,
        IF_F_ESQUERDO = 1,
        IF_ESQUERDO_1 = 2,
        IF_ESQUERDO_2 = 3,
        IF_T_ESQUERDO = 4,
        IF_T_DIREITO = 5,
        IF_DIREITO_2 = 6,
        IF_DIREITO_1 = 7,
        IF_F_DIREITO = 8
    };

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

private:
    OmniDrive omniDrive;
    rec::iocontrol::remotestate::SensorState currentSensorState;
    rec::iocontrol::remotestate::SetState setState;
    Odometry odometry;

};


#endif              /* ROBOTINO_HPP */