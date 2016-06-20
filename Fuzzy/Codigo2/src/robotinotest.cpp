#include "robotinotest.hpp"
#include "robotino.hpp"

//*****************************************************************************************************************
// Test
//*****************************************************************************************************************

Test  *Test::instance()
{
    static Test  TestStateInstance;
    return &TestStateInstance;
}

Test::Test() {}

Test::~Test() {}

void Test::enter(Robotino *robotino)
{
    //if(!c_test01) throw std::invalid_argument("Test must have an owner to enter.");
    std::cout << "Testing...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void Test::execute(Robotino *robotino)
{
    std::cout << "Running Test...\n";
    if(false == robotino->bumper()){
        if(robotino->odometryX() < 1200){
            //robotino->setVelocity(200,0,0);
            //std::cout << robotino->odometryX() << "\n";
           // std::cout << robotino->odometryY() << "\n";
            std::cout << robotino->ir_distance(Robotino::IF_FRONTAL) << "\n";
        }else if(robotino->odometryY() > -900){
            //robotino->setVelocity(0,-200,0);
            //std::cout << robotino->odometryX() << "\n";
            //std::cout << robotino->odometryY() << "\n";
            std::cout << robotino->ir_distance(Robotino::IF_FRONTAL) << "\n";
        }
        else{
            robotino->exit("Chegou");
        }
    }else{
        robotino->exit("Bateu");
    }
}

void Test::exit(Robotino *robotino) {}
