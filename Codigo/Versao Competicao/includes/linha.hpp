#ifndef LINHA_HPP
#define LINHA_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "coordenadas.hpp"
#include "area.hpp"

using namespace std;

class Linha: public Area
{
public:
    Linha():HORIZONTAL(0),VERTICAL(1){};
    void adicionar_coordenada(Coordenadas coord);
private:
	float xMin,xMax,yMin,yMax;
	const int HORIZONTAL;
	const int VERTICAL;
	int orientacao;
};

#endif /* LINHA_HPP */