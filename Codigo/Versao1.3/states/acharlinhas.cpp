#include "acharlinhas.hpp"
#include "robotino.hpp"

#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define Kpx 2
#define Kpy 1.5
#define KpW 4
#define yRef 180
#define xRef 150
#define limiarAlinhamento 2
#define limiarCentralizar 10
//*****************************************************************************************************************
// AcharLinhas
//*****************************************************************************************************************

AcharLinhas  *AcharLinhas::instance()
{
    static AcharLinhas  AcharLinhasStateInstance;
    return &AcharLinhasStateInstance;
}

AcharLinhas::AcharLinhas() {}

AcharLinhas::~AcharLinhas() {}

void AcharLinhas::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado AcharLinhas...\n";
}

void AcharLinhas::execute(Robotino *robotino)
{

    Mat img, cdst;
    int min_Hough = 100, dist_Hough = 50;
    int min_canny =250 , max_canny = 3*min_canny;

    img = robotino->getImage();
    cvtColor( img, cdst, CV_BGR2GRAY );

    Canny( cdst, cdst, (double)min_canny, (double)max_canny, 3 );
    convertScaleAbs(cdst, cdst);

    cv::imshow("Canny",cdst);
    cv::waitKey(1);

    threshold(cdst, cdst, (double)5, (double)255, CV_THRESH_BINARY);

    vector<Vec4i> lines;
    Vec4i l, l2;
    HoughLinesP(cdst, lines, 1, CV_PI/180, min_Hough, min_Hough, dist_Hough );

    cvtColor( cdst, cdst, CV_GRAY2BGR );
    float angLinhas = 0;
    float xMedio = 0;
    float yMaior = -1;
    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      angLinhas += atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      xMedio += (l[2]+l[0])/2;
      if(l[3] > yMaior){
        yMaior = l[3];
      }
      if(l[1] > yMaior){
        yMaior = l[1];
      }
    }
    angLinhas = angLinhas/lines.size();
    xMedio = xMedio/lines.size();

    std::cout << "Angulo médio das linhas"<< angLinhas <<"\n";
    std::cout << "Y maior"<< yMaior <<"\n";
    std::cout << "X medio"<< xMedio <<"\n";

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
    }

    std::cout << lines.size() << "\n";
    float Vx, Vy, w,
    erro_x = yRef - yMaior,
    erro_y = xRef-xMedio,
    erro_theta = -angLinhas;

    Vx = Kpx*erro_x;
    Vy = Kpy*erro_y;
    w = KpW*erro_theta;


    if(abs(erro_x)+abs(erro_theta) < limiarAlinhamento){
        if(abs(erro_y) < limiarCentralizar){
             robotino->setVelocity(0,0,0);
        }else{
             robotino->setVelocity(0,Vy,0);
        }
    }else{
        robotino->setVelocity(Vx,0,w);
    }

    cv::imshow("Linha", cdst);
    cv::waitKey(1);
}

void AcharLinhas::exit(Robotino *robotino) {}
