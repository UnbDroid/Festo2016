//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <unistd.h>

#include "rec/robotino/com/all.h"
#include "rec/core_lt/utils.h"
#include "rec/core_lt/Timer.h"

#include "robotino.hpp"
#include "control.hpp"
#include "ajusteinicial.hpp"
#include "irparaponto.hpp"
#include "mapa.hpp"
#include "coordenadas.hpp"
#include "identificarcor.hpp"
#include "procurarcor.hpp"
#include "basestate.hpp"
#include "irparaparede.hpp"
#include "modulo1.hpp"
#include "modulo1_V2.hpp"
#include "modulo2.hpp"
#include "modulo2_V2.hpp"
#include "modulo3.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "fabricademapas.hpp"
#include "ajustarnaslinhas.hpp"
#include "navegarentreareas2.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"

using namespace rec::robotino::com;

#define R 0
#define Y 1
#define B 2
#define INDEFINIDO -1
#define VAZIO 4
#define N 6
#define TOTALEXPANSAOCOMPETICAO 60


int main( int argc, char **argv )
{

	/*FabricaDeMapas fab;
	Mapa mapa;
	fab.criarMapa("Modulo11Teste",mapa);
	mapa.mostrar_mapa();
	waitKey();*/
	try{
		std::string hostname = "172.26.201.1";
		if( argc > 1 )
		{
			hostname = argv[1];
		}
		//Banana
		Robotino robo(hostname.c_str(), Control::instance(), Coordenadas(30,-30,0));// Modulo 3 Coordenadas(173.5,-100,180)); // Modulo 2 Coordenadas(173.5,-173.5,90)); : modulo 2

		while(true){
			try{
				robo.update();
			}catch(const char * erro){
				std::cerr << erro << std::endl;
				throw erro;
			}
		}
	}catch(const char * erro){
		std::cerr << erro << std::endl;
	}
	//std::cout << "Press any key to exit..." << std::endl;
	//rec::core_lt::waitForKey();*/
}
