//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "rec/robotino/com/all.h"
#include "rec/core_lt/utils.h"
#include "rec/core_lt/Timer.h"

using namespace rec::robotino::com;

class MyCom : public Com
{
public:
	MyCom()
	{
	}

	void errorEvent( Error error, const char* errorString )
	{
		std::cerr << "Error: " << errorString << std::endl;
	}

	void connectedEvent()
	{
		std::cout << "Connected." << std::endl;
	}

	void connectionClosedEvent()
	{
		std::cout << "Connection closed." << std::endl;
	}

	void modeChangedEvent( bool isPassiveMode )
	{
		if( isPassiveMode )
		{
			std::cout << "Connected int passive mode." << std::endl;
		}
	}
};

class MyCamera : public Camera
{
public:
	MyCamera()
	{
	}

	void imageReceivedEvent(const unsigned char * 	data,
				unsigned int 	      	dataSize,
				unsigned int	      	width,
				unsigned int 		height,
				unsigned int		numChannels,
				unsigned int 		bitsPerChannel,
				unsigned int		step)
	{
		std::cout << "Algo alguma vez" << std::endl;
	}	
};

MyCom com;
MyCamera camera;
OmniDrive omniDrive;
Bumper bumper;
Odometry odometry;

//rotate vector in by deg degrees and store the output in out
void rotate( const float* in, float* out, float deg )
{
	const float pi = 3.14159265358979f;

	float rad = 2 * pi / 360.0f * deg;

	out[0] = cos( rad ) * in[0] - sin( rad ) * in[1];
	out[1] = sin( rad ) * in[0] + cos( rad ) * in[1];
}

void init( const std::string& hostname )
{
	// Initialize the actors

	// Connect
	std::cout << "Connecting..." << std::endl;
	com.setAddress( hostname.c_str() );

	com.connect();

	camera.setStreaming(true);

	std::cout << std::endl << "Connected" << std::endl;
}

void drive()
{
	rec::core_lt::Timer timer;
	timer.start();




	const float startVector[2] = {200.0f, 0.0f};
	float dir[2];
	float a = 0.0f;

	bool value = true;

	rec::iocontrol::remotestate::SensorState sensorState;

	while( com.isConnected() && false == sensorState.bumper )
	{
		//rotate 360degrees in 10s
		//rotate( startVector, dir, a );
		//a = 360.0f * timer.msecsElapsed() / 5000;

		//float m1,m2,m3;
		//omniDrive.project( &m1, &m2, &m3, dir[0], dir[1], 0 );

		//rec::iocontrol::remotestate::SetState setState;
		//setState.speedSetPoint[0] = m1;
		//setState.speedSetPoint[1] = m2;
		//setState.speedSetPoint[2] = m3;

		//com.setSetState( setState );
		omniDrive.setVelocity(-100, 0 , 0 );
		

		std::cout << "X: " << odometry.x() << std::endl;
		std::cout << "Y: " << odometry.y() << std::endl;
		std::cout << "PHI: " << odometry.phi() << std::endl;
		

		com.waitForUpdate();

		sensorState = com.sensorState();
	}
}

void destroy()
{
	com.disconnect();
}

int main( int argc, char **argv )
{
	std::string hostname = "172.26.1.1";
	if( argc > 1 )
	{
		hostname = argv[1];
	}

	try
	{
		init( hostname );
		odometry.set(0,0,0);
		drive();
		destroy();
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

	//std::cout << "Press any key to exit..." << std::endl;
	//rec::core_lt::waitForKey();
}
