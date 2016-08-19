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
        //unsigned int width, height;
        
        //unsigned char *data=new unsigned char[jpgDataSize];
        //strcpy((char *)data,(const char *)jpgData);
        //this->resolution(&width,&height);
        std::cout << "Imagem recebida\n";
        //cv::Mat rawData  =  cv::Mat( 1, jpgDataSize, CV_8UC3, data );
		//cv::Mat decodedImage  =  cv::imdecode(rawData ,CV_LOAD_IMAGE_COLOR);
  		//cv::Mat img = cv::Mat(,CV_8UC3,data);
  		//cv::Mat img = imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);
  		//cv::Mat img = cv::Mat(width,height,CV_8UC3,data);  
		//cv::imshow("Original", img);
        std::ofstream myfile;
		myfile.open("temp.jpg");
        for (int i = 0; i < jpgDataSize; ++i)
        {
        	myfile << jpgData[i];
        }
        //cv::Mat test = cv::imread("temp.jpg",CV_LOAD_IMAGE_COLOR);
        //std::cout << test << "\n";
        //std::cout << "\n-------------------------------------\n\n";

        //this->meuRobo->setImage(test);

        //std::cout << "Data SIze " << jpgDataSize << " WIdht " << width << " height " << height << "\n";
	} 
private:
	owner_t * meuRobo;
};




#endif              /* MYCAMERA_HPP */
