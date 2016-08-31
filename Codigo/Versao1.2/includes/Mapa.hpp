#ifndef MAPA_HPP
#define MAPA_HPP

#include <string>
#include <map>
#include <iostream>
#include "Coordenadas.hpp"

using namespace std;

class Mapa
{
public:
	Mapa(){}

	Mapa(float, float , float granulacao = 1);

	~Mapa();

	string representacao() const;

	void inserir_parede(Coordenadas);

	void inserir_retangulo(Coordenadas,Coordenadas,int);

	void inserir_linha(Coordenadas);

	void inserir_marcador(Coordenadas,int);

	void atualizar_mapa();

	bool checar_se_na_area(Coordenadas,int);

	int qual_area(Coordenadas);

	static const int LINHA = 0, PAREDE = 1;

private:
	int * mapa;
	Coordenadas * coordenadas_do_mapa;
	int m,n;
	float altura, largura, granulacao;
	string repr;
	void construir_representacao();
};

std::ostream &operator<<(std::ostream &, Mapa const &);

#endif /* MAPA_HPP */