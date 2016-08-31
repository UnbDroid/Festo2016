//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <unistd.h>

#include "rec/robotino/com/all.h"
#include "rec/core_lt/utils.h"
#include "rec/core_lt/Timer.h"

#include "robotino.hpp"
#include "avoidancecontrol.hpp"
#include "irparaponto.hpp"
#include "MapaImage.hpp"
#include "Coordenadas.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace rec::robotino::com;


int main( int argc, char **argv )
{

	std::string hostname = "172.26.201.1";
	if( argc > 1 )
	{
		hostname = argv[1];
	}

	//Robotino robo(hostname.c_str(), AvoidanceControl::instance());

	MapaImage mapa(201.5, 201.5, 0.5);
	mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(201.5,1.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,201.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(0,200), Coordenadas(201.5,201.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(200,0), Coordenadas(201.5,201.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(170,2),Coordenadas(172,32),2);
	mapa.mostrar_mapa();
	cv::waitKey();

	/*while(true){
		try{
			robo.update();
		}catch(const char * erro){
			std::cerr << erro << std::endl;
			break;
		}

	}*/

	//std::cout << "Press any key to exit..." << std::endl;
	//rec::core_lt::waitForKey();
}
