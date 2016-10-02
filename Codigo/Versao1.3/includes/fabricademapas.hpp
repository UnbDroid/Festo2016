#ifndef FABRICA_DE_MAPAS_HPP
#define FABRICA_DE_MAPAS_HPP

#include <iostream>
#include <string>
#include "coordenadas.hpp"
#include "mapa.hpp"

using namespace std;

class FabricaDeMapas
{
public:
    FabricaDeMapas(){};
    bool criarMapa(string, Mapa&);

private:
    // Mapas testes
    void mapaModulo1Teste(Mapa&);
    void mapaModulo11Teste(Mapa&);
    void mapaModulo2Teste(Mapa&);
    void mapaModulo3Teste(Mapa&);

    // Mapas reais
    void mapaModulo1(Mapa&);
    void mapaModulo2(Mapa&);
    void mapaModulo3(Mapa&);
};

#endif /* FABRICA_DE_MAPAS_HPP */