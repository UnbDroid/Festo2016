#include "percorrerprocurandodiscos.hpp"
#include "robotino.hpp"
#include "identificarcor.hpp"

#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define Kpx 2
#define KpW 4
#define yRef 180
#define N 6
#define limiarParada 12
#define Vy -50
//*****************************************************************************************************************
// PercorrerProcurandoDiscos
//*****************************************************************************************************************

PercorrerProcurandoDiscos  *PercorrerProcurandoDiscos::instance()
{
    static PercorrerProcurandoDiscos  PercorrerProcurandoDiscosStateInstance;
    return &PercorrerProcurandoDiscosStateInstance;
}

PercorrerProcurandoDiscos::PercorrerProcurandoDiscos() {}

PercorrerProcurandoDiscos::~PercorrerProcurandoDiscos() {}

void PercorrerProcurandoDiscos::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado PercorrerProcurandoDiscos...\n";
}

void PercorrerProcurandoDiscos::execute(Robotino *robotino)
{
    Mat img, cdst;
    int min_Hough = 70, dist_Hough = 50;
    int min_canny =150 , max_canny = 3*min_canny;
    float angLinhas = 0, angulo = 0;
    float xMedio = 0;
    float  mediaX = 0;
    float yMaior = -1;
    float erros;
    float Vx, w;
    int cor = -1;
    static bool entrei = false;
    vector<Vec4i> lines;
    Vec4i l, l2;
    static float valoresX[N];
    static int  n = 0;
    static State<Robotino> * voltar;

    img = robotino->getImage();

    cvtColor( img, cdst, CV_BGR2GRAY );

    Canny( cdst, cdst, (double)min_canny, (double)max_canny, 3 );
    convertScaleAbs(cdst, cdst);

    //cv::imshow("Canny",cdst);
    //cv::waitKey(1);

    threshold(cdst, cdst, (double)5, (double)255, CV_THRESH_BINARY);

    HoughLinesP(cdst, lines, 1, CV_PI/180, min_Hough, min_Hough, dist_Hough );

    cvtColor( cdst, cdst, CV_GRAY2BGR );

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      angulo = atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      if(l[3] > yMaior  && abs(angulo) < 60){
        yMaior = l[3];
        angLinhas = atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      }
      if(l[1] > yMaior && abs(angulo) < 60){
        yMaior = l[1];
        angLinhas = atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      }
    }

    std::cout << "Angulo da linha mais perto "<< angLinhas <<"\n";
    std::cout << "Y maior "<< yMaior <<"\n";
    std::cout << "Media dos Xs " << mediaX << "\n";

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
    }

    float erro_x = yRef - yMaior,

    erro_theta = -angLinhas;

    Vx = Kpx*erro_x;
    w = KpW*erro_theta;

    erros = abs(erro_x)+abs(erro_theta);

    std::cout<<"Soma dos erros: " << erros <<std::endl;

    if (!entrei){
        voltar = robotino->previous_state();
        robotino->objetosAmarelos.clear();
        robotino->objetosAzuis.clear();
        robotino->objetosVermelhos.clear();
        entrei = true;
    }

    robotino->change_state(IdentificarCor::instance());



    if (robotino->objetosAmarelos.size() > 0 || robotino->objetosVermelhos.size() > 0 || robotino->objetosAzuis.size() > 0 ){

        if(robotino->objetosAmarelos.size() > 0 && entrei){
            cor = Robotino::AMARELO;
            if (robotino->corFaltando(cor)){
                std::cout << "Percorreu e vai pegar amarelo " << std::endl;
                std::cout << "Cor:  " << cor << std::endl;
                robotino->removerCorFaltando(cor);
                robotino->definirObjetoAlvo(Robotino::AMARELO);
                robotino->setVelocity(0,0,0);
                entrei = false;
                robotino->change_state(voltar);
            }else{
                robotino->setVelocity(Vx,Vy,w);
            }
        }if(robotino->objetosVermelhos.size() > 0  && entrei){
            cor = Robotino::VERMELHO;
            if (robotino->corFaltando(cor)){
                std::cout << "Percorreu e vai pegar vermelho " << std::endl;
                std::cout << "Cor:  " << cor << std::endl;
                robotino->removerCorFaltando(cor);
                robotino->definirObjetoAlvo(Robotino::VERMELHO);
                robotino->setVelocity(0,0,0);
                entrei = false;
                robotino->change_state(voltar);
            }else{
                robotino->setVelocity(Vx,Vy,w);
            }
        }if(robotino->objetosAzuis.size() > 0  && entrei){
             cor = Robotino::AZUL;
            if (robotino->corFaltando(cor)){
                std::cout << "Percorreu e vai pegar azul " << std::endl;
                std::cout << "Cor:  " << cor << std::endl;
                robotino->removerCorFaltando(cor);
                robotino->definirObjetoAlvo(Robotino::AZUL);
                robotino->setVelocity(0,0,0);
                entrei = false;
                robotino->change_state(voltar);
            }else{
                robotino->setVelocity(Vx,Vy,w);
            }
        }
        std::cout << "OIIII????\n";


    }else{
        robotino->setVelocity(Vx,Vy,w);
    }

    cv::imshow("Linha", cdst);
    cv::waitKey(1);

}

void PercorrerProcurandoDiscos::exit(Robotino *robotino) {}
