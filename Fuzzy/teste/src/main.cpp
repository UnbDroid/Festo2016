//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "rec/robotino/com/all.h"
#include "rec/core_lt/utils.h"
#include "rec/core_lt/Timer.h"

#include "robotino.hpp"
#include "robotinotest.hpp"

using namespace rec::robotino::com;


int main( int argc, char **argv )
{
	std::string hostname = "172.26.1.1";
	if( argc > 1 )
	{
		hostname = argv[1];
	}

	Robotino robo(hostname.c_str(), Test::instance());

	while(true){
		try{
			robo.update();
		}catch(const char * erro){
			std::cerr << erro << std::endl;
			break;
		}

	}

	//std::cout << "Press any key to exit..." << std::endl;
	//rec::core_lt::waitForKey();
}
