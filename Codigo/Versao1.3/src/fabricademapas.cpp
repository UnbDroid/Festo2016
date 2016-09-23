#include "mapa.hpp"
#include "fabricademapas.hpp"
#include <iostream>
#include <cmath>

#define PI 3.14159265f

bool FabricaDeMapas::criarMapa(string nome, Mapa& mapa){
    if(nome == "Modulo1Teste"){

        mapaModulo1Teste(mapa);
        return true;

    }else if(nome == "Modulo2Teste"){

        mapaModulo2Teste(mapa);
        return true;

    }else if(nome == "Modulo3Teste"){

        mapaModulo3Teste(mapa);
        return true;

    }else if(nome == "Modulo1"){

        mapaModulo1(mapa);
        return true;

    }else if(nome == "Modulo2"){

        mapaModulo2(mapa);
        return true;

    }else if (nome == "Modulo3"){

        mapaModulo3(mapa);
        return true;

    }else{

        return false;

    }
}

void FabricaDeMapas::mapaModulo1Teste(Mapa & mapa){

    mapa = Mapa(200, 200, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,198.5), Coordenadas(200,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,200),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(48.5,48.5),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(49.5,2),Coordenadas(51.5,51.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,49.5),Coordenadas(51.5,51.5),mapa.LINHA);

    // Area de deposito
    mapa.inserir_retangulo(Coordenadas(151,151),Coordenadas(198,198),3);

    // Linhas da area de deposito
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(150.5,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(198,150.5),mapa.LINHA);

    // Area central
    mapa.inserir_retangulo(Coordenadas(79,69),Coordenadas(122.5,132.5),4);

    // Linhas da area central
    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(125,68.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(123,66.5),Coordenadas(125,135),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(78.5,135),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(76.5,133),Coordenadas(125,135),mapa.LINHA);
}

void FabricaDeMapas::mapaModulo2Teste(Mapa & mapa){
    mapa = Mapa(200, 200, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,198.5), Coordenadas(200,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,200),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(151,151),Coordenadas(198,198),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(150.5,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(198,150.5),mapa.LINHA);

    // Area de deposito 1
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(41.5,66.5),3);

    // Linhas da area de deposito 1
    mapa.inserir_retangulo(Coordenadas(42,2),Coordenadas(44,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,67),Coordenadas(41.5,69),mapa.LINHA);

    // Area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,69.5),Coordenadas(41.5,132),4);

    // Linhas da area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,132.5),Coordenadas(41.5,134.5),mapa.LINHA);

    // Area de deposito 3
    mapa.inserir_retangulo(Coordenadas(2,135),Coordenadas(41.5,198),5);

    // Area de retirada 1
    mapa.inserir_retangulo(Coordenadas(159,2),Coordenadas(198,41.5),6);

    // Linhas da area de retirada 1
    mapa.inserir_retangulo(Coordenadas(156.5,2),Coordenadas(158.5,41.5),mapa.LINHA);

    // Area de retirada 2
    mapa.inserir_retangulo(Coordenadas(117.5,2),Coordenadas(156,41.5),7);

    // Linhas da area de retirada 2
    mapa.inserir_retangulo(Coordenadas(115,2),Coordenadas(117.5,41.5),mapa.LINHA);

    // Area de retirada 3
    mapa.inserir_retangulo(Coordenadas(75.5,2),Coordenadas(114.5,41.5),8);

    // Linhas da area de retirada 3
    mapa.inserir_retangulo(Coordenadas(73,2),Coordenadas(75,41.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(73,42),Coordenadas(198,44),mapa.LINHA);

}

void FabricaDeMapas::mapaModulo3Teste(Mapa & mapa){

}

void FabricaDeMapas::mapaModulo1(Mapa & mapa){

}

void FabricaDeMapas::mapaModulo2(Mapa & mapa){

}

void FabricaDeMapas::mapaModulo3(Mapa & mapa){

}