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

	Robotino robo(hostname.c_str(), AvoidanceControl::instance());

	/*MapaImage mapa(201.5, 201.5, 0.5);
	mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(201.5,1.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,201.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(0,200), Coordenadas(201.5,201.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(200,0), Coordenadas(201.5,201.5),mapa.PAREDE);
	mapa.inserir_retangulo(Coordenadas(170,2),Coordenadas(172,32),2);
	mapa.inserir_retangulo(Coordenadas(160,2),Coordenadas(169.5,72),3);
	mapa.mostrar_mapa();
	cv::waitKey();*/
	/*while(true){
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,10));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,20));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,30));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,40));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,50));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,60));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,70));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,80));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,90));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,100));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,110));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,120));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,130));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,140));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,150));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,160));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,170));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,180));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,190));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,200));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,210));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,220));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,230));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,240));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,250));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,260));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,270));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,280));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,290));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,300));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,310));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,320));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,330));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,340));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,350));
		cv::waitKey(100);
		mapa.mostrar_mapa_com_robo(Coordenadas(100,100,360));
		cv::waitKey(100);
	}*/
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
