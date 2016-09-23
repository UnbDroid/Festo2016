#ifndef ROBOTINO_HPP
#define ROBOTINO_HPP

#include "rec/robotino/com/all.h"
#include "mycamera.hpp"
#include "basecom.hpp"
#include "robotbase.hpp"
#include "mapa.hpp"
#include "object.hpp"
#include "coordenadas.hpp"
#include <opencv2/opencv.hpp>


class Robotino: public BaseCom, public RobotBase<Robotino>{
public:

    Robotino(const char *hostname,
                State<Robotino> *initial_state, Coordenadas pontoInicial);

    ~Robotino();

    void update();

    void exit(const char * motive);

    enum Motor: unsigned int {
        M_ESQUERDO = 0,
        M_TRASEIRO = 1,
        M_DIREITO = 2
    };
    enum Infra: unsigned int {
        IR_FRONTAL = 0,
        IR_F_ESQUERDO = 1,
        IR_ESQUERDO_1 = 2,
        IR_ESQUERDO_2 = 3,
        IR_T_ESQUERDO = 4,
        IR_T_DIREITO = 5,
        IR_DIREITO_2 = 6,
        IR_DIREITO_1 = 7,
        IR_F_DIREITO = 8
    };

    enum IndArea: unsigned int {
        AREA1 = 2,
        AREA2 = 3,
        AREA3 = 4,
        AREA4 = 5,
        AREA5 = 6,
        AREA6 = 7,
        AREA7 = 8,
        AREA8 = 9
    };

    enum IndParede: unsigned int {
        NORTE90  = 0,
        NORTEN90 = 1,
        SUL90    = 2,
        SULN90   = 3,
        LESTE0   = 4,
        LESTE180 = 5,
        OESTE0   = 6,
        OESTE180 = 7
    };

    enum SensorCor: unsigned int {
        SC_DIREITO = 0,
        SC_ESQUERDO = 4
    };

    enum CorObjeto: unsigned int {
        VERMELHO = 0,
        AMARELO = 1,
        AZUL = 2,
        TODAS = 3
    };

    enum DirecaoLinha: unsigned int {
        HORIZONTAL = 0,
        VERTICAL = 1,
        AMOR = 2
    };
    //void definirEstado();

    // Return the bumper state
    bool bumper();

    // Odometry values
    float odometryX();
    float odometryY();
    float odometryPhi();

    // Odometer values
    float motorVelocity(unsigned int);
    float motorPosition(unsigned int);

    // Color sensor
    int readColorSensor(unsigned int);

    // Inductive sensor
    float readInductiveSensor();

    // IR Sensors
    float irDistance(unsigned int);

    // Set individuals positions RPM
    void setMotorVelocity(unsigned int, float);

    //Set velocitys in X, Y and Omega
    void setVelocity(float, float, float);

    void obstacleDetectionUnit(float &, float &);

    void definirDestino(float, float);

    void setThetaR(float);

    void setOdometry(float, float, float);

    // Calculate distance
    float calcDist(float x1, float y1, float x2, float y2);

    Coordenadas pegarCoordenadaArea(int , Coordenadas);
    Coordenadas pegarCoordenadaArea(int);

    // Variaveis necessárias
    float dObs;
    float thetaObs;
    float xD;
    float yD;
    float thetaD;
    float dE;
    float thetaE;
    float thetaR;

    //Variaveis cor

    vector <Object> objetosAmarelos;
    vector <Object> objetosAzuis;
    vector <Object> objetosVermelhos;

    Object objetoAlvo;

    void definirObjetoAlvo(int);

    void definirCorAlvo(int);

    void setImage(cv::Mat image);

    cv::Mat getImage();

    bool carregandoDisco(){return disco;};

    void setCarregando(bool esta){disco = esta;};

    void definirParedeAlvo (int parede){this->parede = parede;};

    int paredeAlvo () {return parede;};

    float getAlturaMapa () {return mapa.getAlturaMapa();};

    float getLarguraMapa () {return mapa.getLarguraMapa();};

    float valorLinha(){return vLinha;};

    int linhaAlvo(){return lAlvo;};

    void definirLinhaAlvo(float, int);

    float getRefDistParede(){return refDistParede;};

    void setDistParede(float dist){refDistParede = dist;}

    float getVelocidadeBusca(){return velocidadeBusca;};

    void setVelocidadeBusca(float vel){velocidadeBusca = vel;}

    void girei(){girar = false;}

    bool deveGirar(){return girar;}

private:
    void construir_mapa();
    OmniDrive omniDrive;
    rec::iocontrol::remotestate::SensorState currentSensorState;
    rec::iocontrol::remotestate::SetState setState;
    Odometry odometry;
    MyCamera<Robotino> camera;
    // Imagem da camera
    cv::Mat cameraImage;
    Mapa mapa;
    bool disco;
    bool girar; // Se gira ou nao ao ir para o ponto
    int parede;
    float vLinha;
    int lAlvo;
    float refDistParede; // distancia da parede
    float velocidadeBusca;

};


#endif              /* ROBOTINO_HPP */
