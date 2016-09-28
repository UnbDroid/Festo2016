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
#include "modulo3.hpp"
#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "nobusca.hpp"
#include "navegarentreareas.hpp"
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

//*****************************************************************************************************************
// Modulo3
//*****************************************************************************************************************


Modulo3  *Modulo3::instance()
{
    static Modulo3  Modulo3StateInstance;
    return &Modulo3StateInstance;
}

Modulo3::Modulo3() {}

Modulo3::~Modulo3() {}

int identificarCorArea(Robotino *robotino){

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

void Modulo3::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Modulo3...\n";
}



int definirOndePegar (NoBusca& melhorResultado, int numPassosFazer, int &numPassosFeitos){

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

int definirOndeDeixar(NoBusca& melhorResultado,int area, int &numPassosFeitos,int numPassosFazer){

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


void Modulo3::execute(Robotino *robotino)
{

    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static bool deixando = false;

    static vector<int> ordemAtualDiscos = {B,R,Y};//{INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudar para 6
    static vector<int> ordemCorreta = {B,R,Y};

    static NoBusca noFinal(ordemCorreta,0);

    static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


// Saindo da area de inicio e indo para a area de deposito 3------------------------------------------------------------------------------------------

    if(objetivo_completo == 0){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 1;

    }else if(objetivo_completo == 1){

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(10);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 2;

    }else if (objetivo_completo == 2){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 3;

    }else if (objetivo_completo == 3){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 4;

    }else if (objetivo_completo == 4){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 5;

    }else if (objetivo_completo == 5){

        ordemAtualDiscos[2] = identificarCorArea(robotino);
        objetivo_completo = 6;
        std::cout << ordemAtualDiscos[2] << std::endl;

    }

    // Indo para a area de deposito 2 identificar a cor -----------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 6) {

        robotino->definirDestino((robotino->odometryX())/10+40, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 7;

    }else if (objetivo_completo == 7){

        Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA3);
        robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 8;

    }else if (objetivo_completo == 8){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 9;

    }else if (objetivo_completo == 9){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 10;

    }else if (objetivo_completo == 10){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 11;

    }else if (objetivo_completo == 11){

        ordemAtualDiscos[1] = identificarCorArea(robotino);
        objetivo_completo = 12;
        std::cout << ordemAtualDiscos[1] << std::endl;

    }

 // Indo para a area de deposito 1 identificar a cor ------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 12) {

        robotino->definirDestino((robotino->odometryX())/10+40, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 13;

    }else if (objetivo_completo == 13){

       Coordenadas destino = robotino->pegarCoordenadaArea(Robotino::AREA2);
        robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
        std::cout << "Destino: " << destino << std::endl;
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 14;

    }else if (objetivo_completo == 14){

        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 15;

    }else if (objetivo_completo == 15){

        robotino->setAreaDeposito(9999); // Para que ele nao faca nada e o vá ate o METAL! \,,/!!
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 16;

    }else if (objetivo_completo == 16){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 17;

    }else if (objetivo_completo == 17){

        ordemAtualDiscos[0] = identificarCorArea(robotino);
        std::cout << ordemAtualDiscos[0] << std::endl;
        robotino->definirDestino(robotino->odometryX()/10 + 50, robotino->odometryY()/10);
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

        objetivo_completo = definirOndePegar(melhorResultado, numPassosFazer, numPassosFeitos);
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

        robotino->setAreaDeposito(666);
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 27;

    }else if (objetivo_completo == 27){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 28;

    }else if (objetivo_completo == 28) {

         identificarCorArea(robotino);
         robotino->change_state(SeguirCor::instance());
         //robotino->setCarregando(true);
         objetivo_completo = 29;

    }else if (objetivo_completo == 29) {

        robotino->definirParedeAlvo(Robotino::SUL90);
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
        objetivo_completo = 32;

    }
    // Decide o destino do disco e difere entre deposito e area intermediaria ------------------------

    else if (objetivo_completo == 32){

        robotino->definirDestino(robotino->odometryX()/10 + 90, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = definirOndeDeixar(melhorResultado, robotino->getDepositoDestino(),numPassosFeitos, numPassosFazer);
        deixando = true;

        if (objetivo_completo != AREA_INTERMEDIARIA) {
            deixarDiscos = objetivo_completo;
            objetivo_completo = 41;
        }
    }

// Ir para area Intermediária ------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 34) {

        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 35;

    }
    // Decide se vai deixar ou pegar o disco na area intermediaria -------------------------------------------

    else if (objetivo_completo == 35) {
        robotino->definirLinhaAlvo(150, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        robotino->setCarregando(false);

        if(!deixando){
            objetivo_completo = 47;
        }else{
            objetivo_completo = 36;
        }

    }else if (objetivo_completo == 36){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10 - 30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 37;
    }

// Voltar da area intermediaria ----------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 37) {
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 38;

    }else if (objetivo_completo == 38) {
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 39;

    }else if (objetivo_completo == 39) {
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(10);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 40;

    }else if (objetivo_completo == 40) {
         robotino->change_state(AjustarNasLinhas::instance());
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

        robotino->definirLinhaAlvo(61, Robotino::HORIZONTAL);
        robotino->change_state(IrParaLinha::instance());
        objetivo_completo = 451;

    }else if (objetivo_completo == 451){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10-10, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 46;  // Ve em qual area ele pega o proximo//

    }else if (objetivo_completo == 46){
        robotino->setCarregando(false);
        robotino->definirDestino(robotino->odometryX()/10+70, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        deixando = false;
        objetivo_completo = 19;  // Ve em qual area ele pega o proximo//

    }

// Coletar disco na area intermediaria ----------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 47){

        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 48;

    }else if (objetivo_completo == 48) {

         identificarCorArea(robotino);
         robotino->change_state(SeguirCor::instance());
         deixando = true;
         //robotino->setCarregando(true);
         objetivo_completo = 37;

    }
    else if (objetivo_completo == 49){

        objetivo_completo = definirOndeDeixar(melhorResultado, robotino->getDepositoDestino(),numPassosFeitos, numPassosFazer);

        if (objetivo_completo != AREA_INTERMEDIARIA) {
            deixarDiscos = objetivo_completo;
            objetivo_completo = 41;
        }
    }

// Voltar para o Inicio -----------------------------------------------------------------------------------------------------------------------------------------------------

    else if (objetivo_completo == 50) {

        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 51;

    } else if (objetivo_completo == 51) {

        robotino->definirParedeAlvo(Robotino::NORTE90);
        robotino->setDistParede(6);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 52;

    }else if (objetivo_completo == 52) {
        robotino->definirLinhaAlvo(-150, Robotino::VERTICAL);
        robotino->change_state(IrParaLinha::instance());
        robotino->setCarregando(false);
        objetivo_completo = 53;

    }else if(objetivo_completo == 53){
        std::cout << "Y: " << robotino->odometryY() << "\n";
        if(robotino->odometryY() < -970){
             robotino->setVelocity(100,0,0);
        }else{
            robotino->setVelocity(0,0,0);
            objetivo_completo = 54;
        }

    }else if(objetivo_completo == 54){
        robotino->exit("Terminei");
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Modulo3::exit(Robotino *robotino) {}
