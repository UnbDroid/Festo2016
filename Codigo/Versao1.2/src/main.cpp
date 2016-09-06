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
#include "ajusteinicial.hpp"
#include "irparaponto.hpp"
#include "MapaImage.hpp"
#include "Coordenadas.hpp"
#include "identificarcor.hpp"
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

	Robotino robo(hostname.c_str(), AjusteInicial::instance());

	/*MapaImage mapa(201.5, 201.5, 0.5);
	    // Paredes da arena
	    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(201.5,1.5),mapa.PAREDE);
	    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,201.5),mapa.PAREDE);
	    mapa.inserir_retangulo(Coordenadas(0,200), Coordenadas(201.5,201.5),mapa.PAREDE);
	    mapa.inserir_retangulo(Coordenadas(200,0), Coordenadas(201.5,201.5),mapa.PAREDE);

	    // Area de inicio
	    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(48.5,48.5),2);

	    // Linhas da area de inicio
	    mapa.inserir_retangulo(Coordenadas(49.5,2),Coordenadas(51.5,51.5),mapa.LINHA);
	    mapa.inserir_retangulo(Coordenadas(2,49.5),Coordenadas(51.5,51.5),mapa.LINHA);

	    // Area de deposito
	    mapa.inserir_retangulo(Coordenadas(152,152),Coordenadas(200,200),3);

	    // Linhas da area de deposito
	    mapa.inserir_retangulo(Coordenadas(150,150),Coordenadas(152,200),mapa.LINHA);
	    mapa.inserir_retangulo(Coordenadas(150,150),Coordenadas(200,152),mapa.LINHA);

	    // Area central
	    mapa.inserir_retangulo(Coordenadas(79,69),Coordenadas(124,134),4);

	    // Linhas da area central
	    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(126.5,68.5),mapa.LINHA);
	    mapa.inserir_retangulo(Coordenadas(124.5,66.5),Coordenadas(126.5,136.5),mapa.LINHA);
	    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(78.5,136.5),mapa.LINHA);
	    mapa.inserir_retangulo(Coordenadas(76.5,134.5),Coordenadas(126.5,136.5),mapa.LINHA);
	mapa.mostrar_mapa();
	cv::waitKey();
	std::cout << mapa.coordenada_area(2) << "\n";
	std::cout << mapa.coordenada_area(3) << "\n";
	std::cout << mapa.coordenada_area(4) << "\n";
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
