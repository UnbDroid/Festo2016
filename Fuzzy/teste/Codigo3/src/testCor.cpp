#include "testCor.hpp"
#include "robotino.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
//*****************************************************************************************************************
// TestCor
//*****************************************************************************************************************

TestCor  *TestCor::instance()
{
    static TestCor  TestCorStateInstance;
    return &TestCorStateInstance;
}

TestCor::TestCor() {}

TestCor::~TestCor() {}

void TestCor::enter(Robotino *robotino)
{
    //if(!c_TestCor01) throw std::invalid_argument("TestCor must have an owner to enter.");
    std::cout << "TestCor...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void TestCor::execute(Robotino *robotino)
{

}

void TestCor::exit(Robotino *robotino) {}