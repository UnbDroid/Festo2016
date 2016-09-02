#include <cmath>
#include "Coordenadas.hpp"
#define PI 3.14159265359

Coordenadas::Coordenadas(){
	this->x = 0;
	this->y = 0;
	this->theta = 0;
}

Coordenadas::Coordenadas(float x,float y, float theta){
	this->x = x;
	this->y = y;
	this->theta = theta;
}

Coordenadas::Coordenadas(const Coordenadas& coord){
	this->x = coord.x;
	this->y = coord.y;
	this->theta = coord.theta;
}

Coordenadas Coordenadas::mudar_referencia(float x_ref, float y_ref, float theta_ref){
	float dx, dy, n_x, n_y, n_theta, theta_rad = theta_ref*PI/180;
	dx = x - x_ref;
	dy = y - y_ref;
	n_x =  std::cos(theta_rad)*dx + std::sin(theta_rad)*dy;
	n_y = -std::sin(theta_rad)*dx + std::cos(theta_rad)*dy;
	n_theta = theta - theta_ref;
	return Coordenadas(n_x, n_y, n_theta);
}

float Coordenadas::calcular_distancia(Coordenadas coord){
	return std::sqrt(std::pow(x-coord.get_x(),2)+std::pow(y-coord.get_y(),2));
}

std::ostream &operator<<(std::ostream &os, Coordenadas const &c) {
    return os << "X: " << c.get_x()<< " Y: " << c.get_y()<< " theta: " << c.get_theta();
}