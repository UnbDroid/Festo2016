#include <algorithm>
#include <iostream>
#include <vector>
#include "nobusca.hpp"

#define R 0
#define Y 1
#define B 2
#define INDEFINIDO -1
#define VAZIO 4
#define N 6
#define TOTALEXPANSAOCOMPETICAO 60

using namespace std;


int main( int argc, char **argv )
{

    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudar para 6
    static vector<int> ordemInicial1 = {VAZIO,Y,B};
    static vector<int> ordemCorreta1 = {B,Y,VAZIO};
    static vector<int> ordemInicial2 = {R,VAZIO,B};
    static vector<int> ordemCorreta2 = {B,VAZIO,R};
    static vector<int> ordemInicial3 = {R,Y,VAZIO};
    static vector<int> ordemCorreta3 = {VAZIO,Y,R};

    
    NoBusca noInicial1(ordemInicial1);
    NoBusca noFinal1(ordemCorreta1,0);
    NoBusca noInicial2(ordemInicial2);
    NoBusca noFinal2(ordemCorreta2,0);
    NoBusca noInicial3(ordemInicial3);
    NoBusca noFinal3(ordemCorreta3,0);


    
    std::cout <<"Estado Inicial 1: "<<noInicial1<<"\n";
    std::cout <<"Estado Final 1: "<<noFinal1<<"\n";
    
    
    NoBusca resultado1 = ordenar(noInicial1,noFinal1);
    std::cout <<"Resultado1: "<<resultado1<<" \n";
    for (int i = 0; i < resultado1.meuCaminho().size(); ++i){
        std::cout << resultado1.meuCaminho()[i] << "\n";
    }
    
    std::cout <<"------------------------------------------------------------ \n";
    
    std::cout <<"Estado Inicial 2: "<<noInicial2<<"\n";
    std::cout <<"Estado Final 2: "<<noFinal2<<"\n";
    
    
    NoBusca resultado2 = ordenar(noInicial2,noFinal2);
    std::cout <<"Resultado 2: \n";
    for (int i = 0; i < resultado2.meuCaminho().size(); ++i){
        std::cout << resultado2.meuCaminho()[i] << "\n";
    }

    std::cout <<"------------------------------------------------------------ \n";

    std::cout <<"Estado Inicial 3: "<<noInicial3<<"\n";
    std::cout <<"Estado Final 3: "<<noFinal3<<"\n";
    
    
    NoBusca resultado3 = ordenar(noInicial3,noFinal3);
    std::cout <<"Resultado 3: \n";
    for (int i = 0; i < resultado3.meuCaminho().size(); ++i){
        std::cout << resultado3.meuCaminho()[i] << "\n";
    }

    std::cout <<"------------------------------------------------------------ \n";

    static vector<int> ordemInicial = {R,Y,B};
    static vector<int> ordemCorreta = {R,B,Y};
    
    
    NoBusca noInicial(ordemInicial);
    NoBusca noFinal(ordemCorreta,0);
    
    planejarEstoque(noInicial, noFinal);

}
