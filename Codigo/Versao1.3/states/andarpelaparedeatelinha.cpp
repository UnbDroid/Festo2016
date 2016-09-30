#include "andarpelaparedeatelinha.hpp"
#include "robotino.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define R 20
#define Kp 5
#define Ki 1
#define Kpy 10
#define Kiy 0
#define dt 0.01
#define numeroLinhasMin 2

//*****************************************************************************************************************
// AndarPelaParedeAteLinha
//*****************************************************************************************************************

AndarPelaParedeAteLinha  *AndarPelaParedeAteLinha::instance()
{
    static AndarPelaParedeAteLinha  AndarPelaParedeAteLinhaStateInstance;
    return &AndarPelaParedeAteLinhaStateInstance;
}

AndarPelaParedeAteLinha::AndarPelaParedeAteLinha() {}

AndarPelaParedeAteLinha::~AndarPelaParedeAteLinha() {}

void AndarPelaParedeAteLinha::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado AndarPelaParedeAteLinha...\n";
}

void AndarPelaParedeAteLinha::execute(Robotino *robotino)
{
    float Vx = 200, Vy, w, distParede;
    float erroDist = 0;
    int paredeAlvo = robotino->paredeAlvo();

    static State<Robotino> * voltar;
    static float a = std::sin(60*PI/180)/std::sin(80*PI/180);
    static float cos20 = std::cos(20*PI/180);
    static float K = R*(a-1);
    static float erro_int = 0;

    float e1 = robotino->irDistance(Robotino::IR_ESQUERDO_1);
    float e2 = robotino->irDistance(Robotino::IR_ESQUERDO_2);
    float ref_e1 = e2*a+K;
    float d1 = robotino->irDistance(Robotino::IR_DIREITO_1);
    float d2 = robotino->irDistance(Robotino::IR_DIREITO_2);
    float ref_d1 = 1.15*(d2*a+K);
    float distancia_da_esquerda, distancia_da_direita;
    float erro;

    vector<Vec4i> lines;
    Vec4i l, l2;
    Mat img, cdst;
    int min_Hough = 70, dist_Hough = 50;
    int min_canny =150 , max_canny = 3*min_canny;

    distParede = robotino->getRefDistParede();
    distParede += R;

    if (paredeAlvo == Robotino::NORTEN90  || paredeAlvo == Robotino::OESTE0 || paredeAlvo == Robotino::SUL90 || paredeAlvo == Robotino::LESTE180){

        erro = (e1-ref_e1);
        erro_int += erro*dt;
        w = Kp*erro+Ki*erro_int;

        distancia_da_esquerda = ((e1+ref_e1+2*R)*cos20)/2;
        erroDist = (distancia_da_esquerda) - distParede;
        Vy = Kpy*erroDist;

        std::cout << "erro dist: " << erroDist << "\n";

        std::cout<< "Esquerda 1: " << e1 << std::endl;
        std::cout<< "RefEsquerda 1: " << ref_e1 << std::endl;
        std::cout<< "Esquerda 2: " << e2 << std::endl;

        std::cout << "Distância da esquerda: " << distancia_da_esquerda << "\n";

        if (lines.size() > numeroLinhasMin){
            if (paredeAlvo == Robotino::OESTE0) {
                robotino->setOdometry(robotino->odometryX(),-(distancia_da_esquerda*10+15),0);
            }
            if (paredeAlvo == Robotino::NORTEN90) {
                robotino->setOdometry((robotino->getAlturaMapa())*10 -(distancia_da_esquerda*10+15),robotino->odometryY(),-90);
            }
             if (paredeAlvo == Robotino::SUL90) {
                robotino->setOdometry((distancia_da_esquerda*10+15),robotino->odometryY(),90);
            }
             if (paredeAlvo == Robotino::LESTE180) {
               robotino->setOdometry(robotino->odometryX(),-((robotino->getLarguraMapa())*10 -(distancia_da_esquerda*10+15)),180);
            }
        }

    }else if (paredeAlvo == Robotino::SULN90  || paredeAlvo == Robotino::LESTE0 || paredeAlvo == Robotino::NORTE90  || paredeAlvo == Robotino::OESTE180) {

        erro = (d1-ref_d1);
        erro_int += erro*dt;
        w = -Kp*erro-Ki*erro_int;

        distancia_da_direita = ((d1+ref_d1+2*R)*cos20)/2;
        erroDist = distParede - ( distancia_da_direita );
        Vy = Kpy*erroDist;

        std::cout<< "Direita 1: " << d1 << std::endl;
        std::cout<< "RefDireita 1: " << ref_d1 << std::endl;
        std::cout<< "Direita 2: " << d2 << std::endl;


        std::cout << "Distância da direita: " << distancia_da_direita << "\n";

        if (lines.size() > numeroLinhasMin){

            if (paredeAlvo == Robotino::SULN90) {
                robotino->setOdometry((distancia_da_direita*10+15),robotino->odometryY(),-90);
            }
            if (paredeAlvo == Robotino::LESTE0) {
                robotino->setOdometry(robotino->odometryX(),-((robotino->getLarguraMapa()) * 10-(distancia_da_direita*10+15)),0);
            }
            if (paredeAlvo == Robotino::NORTE90) {
                robotino->setOdometry((robotino->getAlturaMapa() - (distancia_da_direita*10+15)),robotino->odometryY(),90);
            }
            if (paredeAlvo == Robotino::OESTE180) {
                robotino->setOdometry(robotino->odometryX(),-((distancia_da_direita*10+15)),180);
            }
        }
    }

    img = robotino->getImage();

    cvtColor( img, cdst, CV_BGR2GRAY );

    Canny( cdst, cdst, (double)min_canny, (double)max_canny, 3 );
    convertScaleAbs(cdst, cdst);

    //cv::imshow("Canny",cdst);
    //cv::waitKey(1);

    threshold(cdst, cdst, (double)5, (double)255, CV_THRESH_BINARY);

    HoughLinesP(cdst, lines, 1, CV_PI/180, min_Hough, min_Hough, dist_Hough );

    cvtColor( cdst, cdst, CV_GRAY2BGR );

    if(distParede > 99){
        robotino->setVelocity(Vx,0,0);
    }else{
        robotino->setVelocity(Vx,Vy,w);
    }

    if (lines.size() > numeroLinhasMin){
        robotino->setVelocity(0,0,0);

        robotino->change_state(robotino->previous_state());
    }

}

void AndarPelaParedeAteLinha::exit(Robotino *robotino) {}
