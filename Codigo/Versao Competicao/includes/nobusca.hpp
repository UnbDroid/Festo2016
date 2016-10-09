#ifndef NOBUSCA_HPP
#define NOBUSCA_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define VAZIO 4

class NoBusca
{
public:
    NoBusca();
    NoBusca(std::vector<int>);
    NoBusca(std::vector<int>, int);
    NoBusca(std::vector<int>, std::vector<NoBusca>,int);
    NoBusca(std::vector<int>, int, std::vector<NoBusca>,int);
    std::vector<int> meusValores() const{return valores;}
    int meuCusto() const{return custoEstimado;}
    int meuCustoCaminho() const{return custoCaminho;}
    std::vector<NoBusca> meuCaminho() const{return caminho;}
    int meuCustoTotal() const{return custoEstimado+custoCaminho;}

    void calcularCusto(std::vector<int>);
    void calcularCusto(NoBusca);

    void adicionarAoCaminho(std::vector<NoBusca> n){caminho = n;};

    std::vector<NoBusca> expandirNo(NoBusca noDesejado);
    bool operator < (const NoBusca& no) const{
        return (meuCustoTotal() < no.meuCustoTotal());
    }
    bool operator == (const NoBusca& no) const{
        return (meusValores() == no.meusValores());
    }
    NoBusca& operator=(const NoBusca& rhs) {
    	valores = std::vector<int>();
    	caminho = std::vector<NoBusca>();
    	for (int i = 0; i < rhs.valores.size(); ++i){
    		valores.push_back(rhs.valores[i]);
    	}
    	for (int i = 0; i < rhs.caminho.size(); ++i){
    		caminho.push_back(rhs.caminho[i]);
    	}
    	custoCaminho = rhs.custoCaminho;
    	custoEstimado = rhs.custoEstimado;
    	return *this;
    };
private:
    std::vector<int> valores;
    std::vector<NoBusca> caminho;
    int custoCaminho, custoEstimado;
};

std::ostream &operator<<(std::ostream &, NoBusca &);

NoBusca ordenar(NoBusca noInicial, NoBusca noFinal);

NoBusca planejarEstoque(NoBusca noInicial, NoBusca NoFinal);

#endif /* NoBusca_HPP */
