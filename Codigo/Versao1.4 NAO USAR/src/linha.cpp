#include "area.hpp"
#include "linha.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define PI 3.14159265f

void Linha::adicionar_coordenada(Coordenadas coord){
    Area::adicionar_coordenada(coord);
    if(coord.get_x() < xMin){
        xMin = coord.get_x();
    }
    if(coord.get_x() > xMax){
        xMax = coord.get_x();
    }
    if(coord.get_y() < yMin){
        yMin = coord.get_y();
    }
    if(coord.get_y() > yMax){
        yMax = coord.get_y();
    }
    if(std::abs(xMax-xMin) > std::abs(yMax-yMin)){
        orientacao = VERTICAL;
    }else{
        orientacao = HORIZONTAL;
    }
}
