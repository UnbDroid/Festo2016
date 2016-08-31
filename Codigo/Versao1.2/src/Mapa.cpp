#include "Mapa.hpp"
#include "Objeto.hpp"
#include <string>
#include <iostream>
#include <map>

using namespace std;

// Insira a altura e largula do objeto em metros, se quiser escolhe a granulacao
Mapa::Mapa(float altura, float largura, float granulacao){
	int m = (int) (altura/granulacao  + 1); 
	int n = (int) (largura/granulacao + 1);
	mapa = new int [m*n];
	coordenadas_do_mapa = new Coordenadas [m*n];
	this->m = m;
	this->n = n;
	this->altura = altura;
	this->largura = largura;
	this->granulacao = granulacao;
	for (int i = 0; i < m*n; ++i){
		mapa[i] = 0;
		coordenadas_do_mapa[i] = Coordenadas((int)(i/n)*granulacao,(int)(i%n)*granulacao);
	}
	construir_representacao();
}

Mapa::~Mapa(){
	delete[] mapa;
}

string Mapa::representacao() const{
	return repr;
}

void Mapa::inserir_parede(Coordenadas coord){
	int m = coord.get_x()/granulacao;
	int n = coord.get_y()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return;
	mapa[m*this->n+n] = 1;
	repr.replace(4*(m*this->n+n)+2,1,"\u25A0",2,2);
}

void Mapa::inserir_retangulo(Coordenadas coord1, Coordenadas coord2, int tipo){
	int m_inicial = coord1.get_x()/granulacao;
	int n_inicial = coord1.get_y()/granulacao;
	int m_final = coord2.get_x()/granulacao;
	int n_final = coord2.get_y()/granulacao;
	bool cond1 = (m_inicial >= m || n_inicial >= n || m < 0 || n < 0);
	bool cond2 = (m_final >= m || n_final >= n);
	bool cond3 = (m_inicial > m_final || n_inicial > n_final);
	if(cond1 || cond2 || cond3)
		return;

	for (int i = m_inicial; i <= m_final; ++i){
		for (int j = n_inicial; j <= n_final; ++j){
			if(tipo == LINHA){
				inserir_linha(Coordenadas(i*granulacao,j*granulacao));
			}else if(tipo == PAREDE){
				inserir_parede(Coordenadas(i*granulacao,j*granulacao));
			}else{
				inserir_marcador(Coordenadas(i*granulacao,j*granulacao),tipo);
			}
		}
	}
}

void Mapa::inserir_linha(Coordenadas coord){
	int m = coord.get_x()/granulacao;
	int n = coord.get_y()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return;
	mapa[m*this->n+n] = 2;
	repr.replace(4*(m*this->n+n)+2,1,"\u25A4",2,2);
}

void Mapa::inserir_marcador(Coordenadas coord, int tipo){
	int m = coord.get_x()/granulacao;
	int n = coord.get_y()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0 || tipo == LINHA || tipo == PAREDE)
		return;
	mapa[m*this->n+n] = tipo;
	repr.replace(4*(m*this->n+n)+2,1,"\u25B2",2,2);
}

bool Mapa::checar_se_na_area(Coordenadas p, int area){
	int m = p.get_x()/granulacao;
	int n = p.get_y()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return false;
	return mapa[m*this->n+n]==area;
}

int Mapa::qual_area(Coordenadas p){
	int m = p.get_x()/granulacao;
	int n = p.get_y()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return false;
	return mapa[m*this->n+n];
}

void Mapa::inserir_objeto(Objeto * obj){
	if ( objs.find(obj->get_id()) == objs.end() ) {
	  objs.insert(pair<string, Objeto*>(obj->get_id(),obj));
	}
}

void Mapa::atualizar_mapa(){
	int x,y;
	for (map<string, Objeto*>::iterator it=objs.begin(); it!=objs.end(); ++it){
   		Objeto* obj = it->second;
   		remover_objeto(obj->get_x(),obj->get_y());
   		obj->atualizar(x,y);
   		desenhar_objeto(obj,x,y);
	}
}

void Mapa::construir_representacao(){
	repr = string();
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			if(mapa[i*m+j]==0){
				repr += "\u25A1";
			}else if(mapa[i*m+j]==1){
				repr += "\u25A0";
			}else if(mapa[i*m+j]==2){
				repr += "\u25A4";
			}else{
				repr += "\u25EB";
			}
			if(j<m-1)
				repr+=" ";
		}
		repr+='\n';
	}
}

void Mapa::desenhar_objeto(Objeto* obj, int x, int y){
	if(x >= m || y >= n || x < 0 || y < 0)
		return;
	mapa[y*m+x] = 3;
	repr.replace(4*(y*m+x)+2,1,obj->get_simbolo(),2,2);
}

void Mapa::remover_objeto(int x, int y){
	if(x >= m || y >= n || x < 0 || y < 0)
		return;
	mapa[y*m+x] = 3;
	repr.replace(4*(y*m+x)+2,1,"\u25A1",2,2);
}

std::ostream &operator<<(std::ostream &os, Mapa const &m) { 
    return os << m.representacao();
}