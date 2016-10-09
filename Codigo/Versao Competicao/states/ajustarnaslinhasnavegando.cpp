#include "ajustarnaslinhasnavegando.hpp"
#include "robotino.hpp"

#include <unistd.h>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define Kpx 2
#define Kpy 1.5
#define KpW 4
#define yRef 220
#define xRef 160
#define N 6
#define limiarParada 12
#define rangeXMedio 15
//*****************************************************************************************************************
// AjustarNasLinhasNavegando
//*****************************************************************************************************************

AjustarNasLinhasNavegando  *AjustarNasLinhasNavegando::instance()
{
    static AjustarNasLinhasNavegando  AjustarNasLinhasNavegandoStateInstance;
    return &AjustarNasLinhasNavegandoStateInstance;
}

AjustarNasLinhasNavegando::AjustarNasLinhasNavegando() {}

AjustarNasLinhasNavegando::~AjustarNasLinhasNavegando() {}

void AjustarNasLinhasNavegando::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado AjustarNasLinhasNavegando...\n";
}

void AjustarNasLinhasNavegando::execute(Robotino *robotino)
{

    Mat img, cdst;
    int min_Hough = 70, dist_Hough = 150; //50
    int min_canny =150 , max_canny = 3*min_canny;
    float angLinhas = 0;
    float xMedio = 0;
    float  mediaX = 0;
    float yMaior = -1;
    float erros;
    float Vx, Vy, w;
    static float valoresX[N];
    vector<Vec4i> lines;
    Vec4i l, l2;
    static int  n = 0;
    int num_linha = 0;

    img = robotino->getImage();

    cvtColor( img, cdst, CV_BGR2GRAY );

    Canny( cdst, cdst, (double)min_canny, (double)max_canny, 3 );
    convertScaleAbs(cdst, cdst);

    cv::imshow("Canny",cdst);
    cv::waitKey(1);

    threshold(cdst, cdst, (double)5, (double)255, CV_THRESH_BINARY);

    HoughLinesP(cdst, lines, 1, CV_PI/180, min_Hough, min_Hough, dist_Hough );

    cvtColor( cdst, cdst, CV_GRAY2BGR );

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];

      if(l[3] > yMaior){
        yMaior = l[3];
      }
      if(l[1] > yMaior){
        yMaior = l[1];
      }

      std::cout<< "Coordenadas das linhas: " << l[0] << " " << l[1]<< " " << l[2]<< " " << l[3] << "\n";
      std::cout<< "Os ranges zoados: " << (l[3]  > yMaior - rangeXMedio) << " " << (l[3]  < yMaior + rangeXMedio)<< " " << (l[1]  > yMaior - rangeXMedio)<< " " << (l[1]  < yMaior + rangeXMedio) << "\n";
      if (abs(atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI) < 30 && ((l[3]  > yMaior - rangeXMedio && l[3]  < yMaior + rangeXMedio) || (l[1]  > yMaior - rangeXMedio && l[1]  < yMaior + rangeXMedio)) ){
        angLinhas += atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
        xMedio += (l[2]+l[0])/2;
        num_linha++;
      }

    }
    angLinhas = angLinhas/lines.size();
    if(num_linha!=0){
        xMedio = xMedio/num_linha;
    }

    valoresX[n%N] = xMedio;
    if(n<N){
        mediaX = xMedio;
    }else{
        for (int i = 0; i < N; ++i)
        {
            mediaX += valoresX[i];
            //std::cout << "valoresX[i] = "<< valoresX[i] << "\n";
        }
        mediaX /= N;
    }
    n++;

    std::cout << "Angulo médio das linhas "<< angLinhas <<"\n";
    std::cout << "Y maior "<< yMaior <<"\n";
    std::cout << "X medio "<< xMedio <<"\n";
    std::cout << "Media dos Xs " << mediaX << "\n";

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
    }

    std::cout << lines.size() << "\n";

    float erro_x = yRef - yMaior,
    erro_y = xRef-mediaX,
    erro_theta = -angLinhas;

    Vx = Kpx*erro_x;
    Vy = Kpy*erro_y;
    w = KpW*erro_theta;

    erros = abs(erro_x)+abs(erro_y)+abs(erro_theta);

    std::cout<<"Soma dos erros: " << erros <<std::endl;

    if(erros < limiarParada){
        //robotino->setVelocity(0,0,0);
        usleep(500000);
        n = 0;

        robotino->change_state(robotino->previous_state());
    }else{
        //robotino->setVelocity(Vx,Vy,w);
    }

    cv::imshow("Linha", cdst);
    cvMoveWindow("Linha",500,0);
    cv::waitKey(1);
}

void AjustarNasLinhasNavegando::exit(Robotino *robotino) {
    std::cout << "Saindo do estado AjustarNasLinhasNavegando...\n";
}
