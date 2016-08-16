#ifndef MYCAMERA_HPP
#define MYCAMERA_HPP

#include "rec/robotino/com/all.h"
#include "rec/robotino/com/JPGCamera.h"
#include "robotino.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

//using namespace cv;

using namespace rec::robotino::com;

template <class owner_t> class MyCamera:public JPGCamera{ 
public:
	MyCamera(owner_t *robo){
        this->meuRobo = robo;
    }

    virtual void jpgReceivedEvent( const unsigned char* jpgData,
                                  unsigned int jpgDataSize ){
        unsigned int width, height;
        unsigned char *data=new unsigned char[jpgDataSize];
        strcpy((char *)data,(const char *)jpgData);
        std::cout << "Imagem recebida\n";
  		cv::Mat img = cv::Mat(1,jpgDataSize,CV_8UC3,data);  
		//cv::imshow("Original", img);

        this->meuRobo->setImage(img);
        this->resolution(&width,&height);
        std::cout << "Data SIze " << jpgDataSize << " WIdht " << width << " height " << height << "\n";
	} 
private:
	owner_t * meuRobo;
};




#endif              /* MYCAMERA_HPP */
