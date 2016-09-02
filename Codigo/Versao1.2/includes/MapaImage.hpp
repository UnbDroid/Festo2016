#ifndef MapaImage_HPP
#define MapaImage_HPP

#include <string>
#include <map>
#include <iostream>
#include "Coordenadas.hpp"
#include "Area.hpp"

#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class MapaImage
{
public:
	MapaImage(){}

	MapaImage(float, float , float granulacao = 1);

	~MapaImage();

	string representacao() const;

	void inserir_retangulo(Coordenadas,Coordenadas,int);

	void atualizar_mapa();

	bool checar_se_na_area(Coordenadas,int);

	int qual_area(Coordenadas);

	void mostrar_mapa();

	void mostrar_mapa_com_robo(Coordenadas);

	Coordenadas coordenada_area(int, Coordenadas);

	Coordenadas coordenada_area(int);

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

std::ostream &operator<<(std::ostream &, MapaImage const &);

#endif /* MAPA_HPP */