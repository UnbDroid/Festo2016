#include "area.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define PI 3.14159265f

Area::Area(int id){
    this->id = id;
    num_elem = 0;
}

void Area::adicionar_coordenada(Coordenadas coord){
    float x_medio,y_medio;
    coordenadas.push_back(coord);
    num_elem++;
    x_medio = ponto_medio.get_x()*(num_elem-1)/num_elem + coord.get_x()/num_elem;
    y_medio = ponto_medio.get_y()*(num_elem-1)/num_elem + coord.get_y()/num_elem;
    ponto_medio = Coordenadas(x_medio, y_medio);
}

Coordenadas Area::pegar_coordenada(Coordenadas coord){
    float min = 99999,valor,orientacao;
    Coordenadas resultado;
    for (std::vector<Coordenadas>::iterator i = coordenadas.begin(); i != coordenadas.end(); ++i){
        valor = i->calcular_distancia(coord);
        //std::cout << "Valor = " << valor <<"\n";
        if(valor < min){
            //std::cout << "Menor? = " << valor <<"\n";
            min = valor;
            resultado = *i;
            //std::cout << "Ponto de origem = " << coord <<"\n";
            //std::cout << "Menor resultado = " << resultado <<"\n";
        }
    }
    orientacao = std::atan2(ponto_medio.get_y() - resultado.get_y(), ponto_medio.get_x() - resultado.get_x())*180/PI;
    resultado.set_theta(orientacao);
    return resultado;
}