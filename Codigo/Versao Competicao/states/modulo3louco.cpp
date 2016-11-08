#include "control.hpp"
#include "robotino.hpp"
#include "classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "irparaponto.hpp"
#include "controleposicao.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "identificarcor.hpp"
#include "procurarcor.hpp"
#include "seguircor.hpp"
#include "irparaparede.hpp"
#include "irparalinha.hpp"
#include "modulo3louco.hpp"
#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "nobusca.hpp"
#include "navegarentreareas.hpp"
#include "navegarentreareas2.hpp"
#include "navegarentreareas3.hpp"
#include "alinhartraseiro.hpp"
#include <unistd.h>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>

#define PI 3.14159265
#define R 0
#define Y 1
#define B 2
#define INDEFINIDO -1
#define VAZIO 4
#define AREA_D1 20
#define AREA_D2 21
#define AREA_D3 22
#define AREA_D4 23
#define AREA_D5 24
#define AREA_D6 25
#define AREA_INTERMEDIARIA 34
#define VOLTARINICIO 50
#define  RE 30

//*****************************************************************************************************************
// Modulo3Louco
//*****************************************************************************************************************


Modulo3Louco  *Modulo3Louco::instance()
{
    static Modulo3Louco  Modulo3LoucoStateInstance;
    return &Modulo3LoucoStateInstance;
}

Modulo3Louco::Modulo3Louco() {}

Modulo3Louco::~Modulo3Louco() {}

int identificarCorAreaLouco(Robotino *robotino){

    if(robotino->objetosAmarelos.size() > 0){
        robotino->definirObjetoAlvo(Robotino::AMARELO);
        return Y;
    }else if(robotino->objetosVermelhos.size() > 0){
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
       return R;
    }else if(robotino->objetosAzuis.size() > 0){
         robotino->definirObjetoAlvo(Robotino::AZUL);
       return B;
    }

}

void Modulo3Louco::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Modulo3Louco...\n";
}



int definirOndePegarLouco (NoBusca& melhorResultado, int numPassosFazer, int &numPassosFeitos){

    if (numPassosFazer == 0)
        return VOLTARINICIO;

    if(numPassosFeitos <= numPassosFazer){

        vector<NoBusca> res = melhorResultado.meuCaminho();

        std::cout << "tamanho : "<<res.size()<< std::endl;
        NoBusca resultado = res[numPassosFeitos];
        std::vector<int> valores = resultado.meusValores();

        int j = std::find(valores.begin(), valores.begin()+valores.size(), VAZIO) - valores.begin();

        switch (j){
            case 0:
                return AREA_D1;
            case 1:
                return AREA_D2;
            case 2:
                return AREA_D3;
            case 3:
                return AREA_D4;
            case 4:
                return AREA_D5;
            case 5:
                return AREA_D6;
        }
        return -1;
    }else if (numPassosFeitos == (numPassosFazer + 1)){
        return AREA_INTERMEDIARIA;
    }
    return VOLTARINICIO;
}

int definirOndeDeixarLouco(NoBusca& melhorResultado,int area, int &numPassosFeitos,int numPassosFazer){

    if (numPassosFeitos == 0) {
        numPassosFeitos ++;
        return  AREA_INTERMEDIARIA;
    }

    vector<NoBusca> res = melhorResultado.meuCaminho();
    std::cout << "tamanho : "<<res.size()<< std::endl;
    NoBusca resultado = res[numPassosFeitos-1];
    std::vector<int> valores = resultado.meusValores();

    int j = std::find(valores.begin(), valores.begin()+valores.size(), VAZIO) - valores.begin();

    numPassosFeitos ++;

    switch (j){
        case 0:
            return AREA_D1;
        case 1:
            return AREA_D2;
        case 2:
            return AREA_D3;
        case 3:
            return AREA_D4;
        case 4:
            return AREA_D5;
        case 5:
            return AREA_D6;
    }
    return -1;
}


void Modulo3Louco::execute(Robotino *robotino)
{

    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;

    static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
    static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

    static NoBusca noFinal(ordemCorreta,0);

    static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


// Saindo da area de inicio e indo para a area de deposito 6------------------------------------------------------------------------------------------

    if(objetivo_completo == 0){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 5001;

    }

    // Pulou esses agora --------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 1){

        robotino->setDistParede(20);
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->definirLinhaAlvo(263, Robotino::HORIZONTAL); // mudei para arena competicao
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        robotino->setCarregando(false);
        objetivo_completo = 4;

    }else if (objetivo_completo == 2){

        robotino->definirDestino(robotino->odometryX()/10 - 10, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 3;

    }else if (objetivo_completo == 3){

        robotino->setDistParede(10);
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->definirLinhaAlvo(200, Robotino::HORIZONTAL); // mudei para arena competicao
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        robotino->setCarregando(false);
        objetivo_completo = 4;

    }else if(objetivo_completo == 4){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(10);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 5;

    }else if (objetivo_completo == 5){

        robotino->change_state(AjustarNasLinhasOrtogonais::instance());
        objetivo_completo = 5001;

    }

// Veio direto pra cá -----------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 5001){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo =5002;

    }else if (objetivo_completo == 5002){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 5003;

    }else if (objetivo_completo == 5003){

        ordemAtualDiscos[5] = identificarCorAreaLouco(robotino);
        objetivo_completo = 6001;
        std::cout << ordemAtualDiscos[5] << std::endl;

    }

 // Indo para a area de deposito 5 identificar a cor -----------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 6001) {
        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 6;
    }
    else if (objetivo_completo == 6) {
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA6);
        robotino->definirDestino(robotino->odometryX()/10, -destino.get_y());
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 7001;
    }else if (objetivo_completo == 7001) {
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 7;
    }
    else if (objetivo_completo == 7){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 8;

    }else if (objetivo_completo == 8){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 9;

    }else if (objetivo_completo == 9){

        ordemAtualDiscos[4] = identificarCorAreaLouco(robotino);
        objetivo_completo = 90001;
        std::cout << ordemAtualDiscos[4] << std::endl;

    }

// Indo para a area de deposito 4 identificar a cor -----------------------------------------------------------------------------------------------------------------------

        else if (objetivo_completo == 90001) {
        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 9001;
    }

       else if (objetivo_completo == 9001) {
            Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA5);
            robotino->definirDestino(robotino->odometryX()/10, -destino.get_y());
            std::cout << "Destino: " << destino << std::endl;
            robotino->change_state(IrParaPonto::instance());
            objetivo_completo = 10001;
        }else if (objetivo_completo == 10001) {
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 10;
    }
        else if (objetivo_completo == 10){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 101;

    }else if (objetivo_completo == 101){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 102;

    }else if (objetivo_completo == 102){

        ordemAtualDiscos[3] = identificarCorAreaLouco(robotino);
        objetivo_completo = 1003;
        std::cout << ordemAtualDiscos[3] << std::endl;

    }

// Indo para a area de deposito 3 identificar a cor -----------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 1003) {
        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 103;
    }

       else if (objetivo_completo == 103) {
            Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA4);
            robotino->definirDestino(robotino->odometryX()/10, -destino.get_y());
            std::cout << "Destino: " << destino << std::endl;
            robotino->change_state(IrParaPonto::instance());
            objetivo_completo = 10004;
    }else if (objetivo_completo == 10004) {
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 104;
    }
        else if (objetivo_completo == 104){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 105;

    }else if (objetivo_completo == 105){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 11;

    }else if (objetivo_completo == 11){

        ordemAtualDiscos[2] = identificarCorAreaLouco(robotino);
        objetivo_completo = 1110;
        std::cout << ordemAtualDiscos[2] << std::endl;

    }


    // Indo para a area de deposito 2 identificar a cor -----------------------------------------------------------------------------------------------------------------------

        else if (objetivo_completo == 1110) {
        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 111;
    }
    else if (objetivo_completo == 111) {
            Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);
            robotino->definirDestino(robotino->odometryX()/10, -destino.get_y());
            std::cout << "Destino: " << destino << std::endl;
            robotino->change_state(IrParaPonto::instance());
            objetivo_completo = 10012;
    }
    else if (objetivo_completo == 10012) {
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 112;
    }
        else if (objetivo_completo == 112){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 113;

    }else if (objetivo_completo == 113){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 114;

    }else if (objetivo_completo == 114){

        ordemAtualDiscos[1] = identificarCorAreaLouco(robotino);
        objetivo_completo = 1200;
        std::cout << ordemAtualDiscos[1] << std::endl;

    }

 // Indo para a area de deposito 1 identificar a cor ------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 1200) {
        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 12;
    }
    else if (objetivo_completo == 12) {
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2);
        robotino->definirDestino(robotino->odometryX()/10, -destino.get_y());
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 15000;

    }else if (objetivo_completo == 15000) {
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 15;
    }

    else if (objetivo_completo == 15){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 16;

    }else if (objetivo_completo == 16){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 17;

    }else if (objetivo_completo == 17){

        ordemAtualDiscos[0] = identificarCorAreaLouco(robotino);
        std::cout << ordemAtualDiscos[0] << std::endl;
        objetivo_completo = 1700;

    }else if (objetivo_completo == 1700) {
        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 18;
    }

// Planeja como organizar os discos ------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 18){
         NoBusca noInicial(ordemAtualDiscos);
         melhorResultado =planejarEstoque(noInicial, noFinal);
         numPassosFazer = melhorResultado.meuCustoTotal();
         robotino->setDepositoDestino(Robotino::AREA2);
         objetivo_completo = 19;

    }else if (objetivo_completo == 19){

        objetivo_completo = definirOndePegarLouco(melhorResultado, numPassosFazer, numPassosFeitos);

    }else if (objetivo_completo == 191){

        objetivo_completo = definirOndePegarLouco(melhorResultado, numPassosFazer, numPassosFeitos);

        if (objetivo_completo != VOLTARINICIO && objetivo_completo!= AREA_INTERMEDIARIA){
            pegar =  objetivo_completo;
            objetivo_completo = 192;
        }

    }else if (objetivo_completo == 192){

        //robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        //robotino->change_state(ContarLinhas::instance());
        objetivo_completo= pegar;

    }

// Indo para áreas -----------------------------------------------------------------------------------------------------------------------------------------------------

// Ir para area 1  ---------------------------------------------------------------------

    else if (objetivo_completo == 20){

        robotino->setDepositoAtual(robotino->getDepositoDestino());
        robotino->setDepositoDestino(Robotino::AREA2);
        robotino->change_state(NavegarEntreAreas::instance());

        if (!deixando){
            objetivo_completo = 26;
        }else{
            objetivo_completo = 44;
        }

    }
    // Indo para area 2 ---------------------------------------------------------------
    else if (objetivo_completo == 21){

        robotino->setDepositoAtual(robotino->getDepositoDestino());
        robotino->setDepositoDestino(Robotino::AREA3);
        robotino->change_state(NavegarEntreAreas::instance());

        if (!deixando){
            objetivo_completo = 26;
        }else{
            objetivo_completo = 44;
        }

    }
    // Indo para area  3 --------------------------------------------------------------
    else if (objetivo_completo == 22){

        robotino->setDepositoAtual(robotino->getDepositoDestino());
        robotino->setDepositoDestino(Robotino::AREA4);
        robotino->change_state(NavegarEntreAreas::instance());

        if (!deixando){
            objetivo_completo = 26;
        }else{
            objetivo_completo = 44;
        }

    }
    // Ir para area 4  ------------------------------------------------------------------

    else if (objetivo_completo == 23){

        robotino->setDepositoAtual(robotino->getDepositoDestino());
        robotino->setDepositoDestino(Robotino::AREA5);
        robotino->change_state(NavegarEntreAreas::instance());

        if (!deixando){
            objetivo_completo = 26;
        }else{
            objetivo_completo = 44;
        }


    }
    // Indo para area  5 --------------------------------------------------------------
    else if (objetivo_completo == 24){

        robotino->setDepositoAtual(robotino->getDepositoDestino());
        robotino->setDepositoDestino(Robotino::AREA6);
        robotino->change_state(NavegarEntreAreas::instance());

        if (!deixando){
            objetivo_completo = 26;
        }else{
            objetivo_completo = 44;
        }

    }
    // Indo para area  6 --------------------------------------------------------------
    else if (objetivo_completo == 25){

        robotino->setDepositoAtual(robotino->getDepositoDestino());
        robotino->setDepositoDestino(Robotino::AREA7);
        robotino->change_state(NavegarEntreAreas::instance());

        if (!deixando){
            objetivo_completo = 26;
        }else{
            objetivo_completo = 44;
        }

    }

 // Rotina pra ir coletar o disco -------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 26){

        //f (numPassosFeitos == 0 && robotino->getDepositoDestino() == Robotino::AREA2) {
           // objetivo_completo = 27;
        //}else {
            robotino->setAreaDeposito(666);
            robotino->change_state(ContarLinhas::instance());
            objetivo_completo = 27;
        //}

    }else if (objetivo_completo == 27){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 28;

    }else if (objetivo_completo == 28) {

         identificarCorAreaLouco(robotino);
         robotino->change_state(SeguirCor::instance());
         //robotino->setCarregando(true);
         objetivo_completo = 29;

    }else if (objetivo_completo == 29) {
        robotino->setCarregando(false);
        if (robotino->getDepositoDestino() == Robotino::AREA2){
            robotino->definirParedeAlvo(Robotino::SULN90);
        }else {
            robotino->definirParedeAlvo(Robotino::SUL90);
        }
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo=30;

    }else if (objetivo_completo == 30) {

        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 31;

    }else if (objetivo_completo == 31){

        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistTrasParede(20);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 311;

    }else if (objetivo_completo == 311){

        //Coordenadas destino = robotino->pegarCoordenadaArea(robotino->getDepositoDestino());
        //robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
        //robotino->change_state(IrParaPonto::instance());

        objetivo_completo = 312;

    }else if (objetivo_completo == 312){

        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistTrasParede(20);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 32;

    }
    // Decide o destino do disco e difere entre deposito e area intermediaria ------------------------

    else if (objetivo_completo == 32){

        robotino->definirDestino(robotino->odometryX()/10 + 80, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = definirOndeDeixarLouco(melhorResultado, robotino->getDepositoDestino(),numPassosFeitos, numPassosFazer);
        deixando = true;

        if (objetivo_completo != AREA_INTERMEDIARIA) {
            deixarDiscos = objetivo_completo;
            objetivo_completo = 41;
        }
    }

// Ir para area Intermediária ------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 34){

        robotino->setDepositoDestino(Robotino::AREA2);
        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 341;
    }


    // Decide se vai deixar ou pegar o disco na area intermediaria -------------------------------------------
    else if (objetivo_completo == 341){

        robotino->definirParedeAlvo(99999);
        robotino->setDistParede(100);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 342;

    }else if (objetivo_completo == 342){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 35;


    }else if (objetivo_completo == 35){

        robotino->definirLinhaAlvo(-51,Robotino::VERTICAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 35;
        if (!deixando){
            objetivo_completo = 47;
        }else{
            objetivo_completo = 36;
        }

    }else if (objetivo_completo == 36){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10+10);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 361;

    }else if (objetivo_completo == 361){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-20);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 37;
    }

// Voltar da area intermediaria ----------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 37) {
        robotino->setCarregando(false);
        robotino->setThetaR(180);
        robotino->change_state(Girar::instance());
        objetivo_completo = 38;

    }else if (objetivo_completo == 38) {
        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2);
        robotino->definirDestino(destino.get_x()+90, -destino.get_y());
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 39;
    }else if (objetivo_completo == 39) {
        robotino->change_state(AjustarNasLinhas::instance());
        if(!deixando){
            objetivo_completo = 40;
        }else{
            objetivo_completo = 49;
        }

    }else if (objetivo_completo == 40){   //Chamada depois de ir para area correta//

        robotino->setAreaDeposito(666);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 401;

    }else if (objetivo_completo == 401){   //Chamada depois de ir para area correta//

        robotino->definirDestino(robotino->odometryX()/10+RE, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        if(!deixando){
             objetivo_completo = 19;
        }else{
            objetivo_completo = 49;
        }

    }

 // Deixar Discos a partir do deposito ----------------------------------------------------------------------------------------------------------------------------------------------------------------

     // Comeca a se arrumar pra deixar os discos ----------------------------------------------------

    else if (objetivo_completo == 41) {

        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 42;

    }else if (objetivo_completo == 42) {

        robotino->setThetaR(180);
        robotino->change_state(Girar::instance());
        objetivo_completo = 43;

    }else if (objetivo_completo == 43){

        robotino->change_state(AjustarNasLinhas::instance());
        robotino->setCarregando(false);
        deixando = true;
        objetivo_completo = deixarDiscos;    // Vai para a área que deve deixar o disco //

    }

    // Indo deixar o disco ------------------------------------------------------------------------------------

     else if (objetivo_completo == 44){   //Chamada depois de ir para area correta//

        robotino->setAreaDeposito(666);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 45;

    }else if(objetivo_completo == 45){

        robotino->definirLinhaAlvo(72, Robotino::HORIZONTAL); // mudei para a arena nova
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 451;

    }else if (objetivo_completo == 451){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10-15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 46;  // Ve em qual area ele pega o proximo//

    }else if (objetivo_completo == 46){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10+70, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 461;  // Ve em qual area ele pega o proximo//

    }else if (objetivo_completo == 461){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 191;

    }

// Coletar disco na area intermediaria ----------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 47){

        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-30);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 471;

    }else if (objetivo_completo == 471){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 48;

    }else if (objetivo_completo == 48) {

         identificarCorAreaLouco(robotino);
         robotino->change_state(SeguirCor::instance());
         deixando = true;
         //robotino->setCarregando(true);
         objetivo_completo = 37;

    }
    else if (objetivo_completo == 49){

        objetivo_completo = definirOndeDeixarLouco(melhorResultado, robotino->getDepositoDestino(),numPassosFeitos, numPassosFazer);

    }

// Voltar para o Inicio -----------------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 50){

        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10+30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());

        objetivo_completo = 501;

    }else if (objetivo_completo == 501) {

        robotino->setNaoDevoGirarParede(true);
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 51;

    } else if (objetivo_completo == 51) {

        robotino->definirParedeAlvo(Robotino::NORTE90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 52;

    }else if (objetivo_completo == 52) {

        robotino->definirParedeAlvo(Robotino::NORTE90);
        robotino->setDistParede(15);
        robotino->definirLinhaAlvo(-225, Robotino::VERTICAL); //mudei para arena nova
        robotino->change_state(AndarPelaParedeAteLinhaSensor::instance());
        robotino->setCarregando(false);
        objetivo_completo = 53;

    }else if(objetivo_completo == 53){
        robotino->definirDestino((robotino->odometryX())/10, robotino->odometryY()/10+35);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 54;

    }else if(objetivo_completo == 54){
        robotino->exit("Terminei");
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Modulo3Louco::exit(Robotino *robotino) {}
