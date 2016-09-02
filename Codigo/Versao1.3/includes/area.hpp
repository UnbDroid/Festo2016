#ifndef AREA_HPP
#define AREA_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "coordenadas.hpp"

using namespace std;

class Area
{
public:
    Area(){num_elem = 0;};
    Area(int id);
    void adicionar_coordenada(Coordenadas coord);
    Coordenadas pegar_coordenada(Coordenadas);
    Coordenadas pegar_meio(){return ponto_medio;}
protected:
    int id;
    int num_elem;
    Coordenadas ponto_medio;
    vector<Coordenadas> coordenadas;
};

#endif /* AREA_HPP */