#include "avoidancecontrol.hpp"
#include "robotino.hpp"
#include "Classificadores.hpp"
#include "TabelaRegrasVel.hpp"
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

void AvoidanceControl::execute(Robotino *robotino)
{
    std::cout << "Running Avoidance Control...\n";
    if(robotino->bumper() == true)
        robotino->exit("Bateu");
    robotino->setVelocity(100,150,0);
    robotino->obstacleDetectionUnit(robotino->d_obs,robotino->theta_obs);
    std::cout << "Dist obs: " << robotino->d_obs << "\n";
    std::cout << "Theta obs: " << robotino->theta_obs << "\n";
    robotino->d_e = robotino->calc_dist(robotino->x_d,robotino->y_d,robotino->odometryX(),robotino->odometryY());
    robotino->theta_e = robotino->odometryPhi()-robotino->theta_d;
    std::cout << "Dist e: " << robotino->d_e << "\n";
    std::cout << "Theta e: " << robotino->theta_e << "\n";
    std::cout << "Phi: "<<robotino->odometryPhi()<< "\n";
    std::cout << "X: "<<robotino->odometryX()<< "\n";
    std::cout << "Y: "<<robotino->odometryY()<< "\n";
}

void AvoidanceControl::exit(Robotino *robotino) {}