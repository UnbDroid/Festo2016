#ifndef MAPA_HPP
#define MAPA_HPP

#include <string>
#include <map>
#include <iostream>
#include "coordenadas.hpp"
#include "area.hpp"

#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Mapa
{
public:
	Mapa(){}

	Mapa(float, float , float granulacao = 1);

	~Mapa();

	string representacao() const;

	void inserir_retangulo(Coordenadas,Coordenadas,int);

	void atualizar_mapa();

	bool checar_se_na_area(Coordenadas,int);

	int qual_area(Coordenadas);

	void mostrar_mapa();

	void mostrar_mapa_com_robo(Coordenadas);

	Coordenadas coordenada_area(int, Coordenadas);

	Coordenadas coordenada_area(int);

	float getAlturaMapa() {return altura;};

	float getLarguraMapa() {return largura;};

	static const int LINHA = 0, PAREDE = 1;

private:
	int * mapa;
	map<int,Area> areas_armazenadas;
	Coordenadas * coordenadas_do_mapa;
	int m,n;
	float altura, largura, granulacao;
	string repr;
	void construir_representacao();
	Mat img_mapa;
	void inserir_parede(Coordenadas);
	void inserir_linha(Coordenadas);
	void inserir_marcador(Coordenadas,int);
	void definir_cores();
	Scalar cores[6];

};

std::ostream &operator<<(std::ostream &, Mapa const &);

#endif /* MAPA_HPP */