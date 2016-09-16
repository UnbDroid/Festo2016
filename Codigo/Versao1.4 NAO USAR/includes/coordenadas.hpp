#include <iostream>

#ifndef COORDENADAS_HPP
#define COORDENADAS_HPP

using namespace std;

class Coordenadas{
public:
	Coordenadas();

	Coordenadas(float,float,float theta = 0);

	Coordenadas(const Coordenadas&);

	float get_x() const{return x;}

	float get_y() const{return y;}

	float get_theta() const{return theta;}

            float set_theta(float n_theta){theta = n_theta;}

	Coordenadas mudar_referencia(float x_ref, float y_ref, float theta_ref);

             float calcular_distancia(Coordenadas);


private:
	float x,y,theta;
};

std::ostream &operator<<(std::ostream &, Coordenadas const &);

#endif /* COORDENADAS_HPP */