#ifndef TABELA_REGRAS_HPP
#define TABELA_REGRAS_HPP

#include "Regras.hpp"
#include <vector>

using namespace std;

template <class Owner> class TabelaRegras{
public:
    TabelaRegras(vector<vector<Regras<Owner> *>>  regras){
        tabelaRegras = regras;
    }

    int acharRegra(int m,int n){
        if ((unsigned) m > tabelaRegras.size()){
            return -1;
        }
        if((unsigned) n > tabelaRegras[m].size()){
            return -1;
        }
        tabelaRegras[m][n]->executar();
        return 0;
    }

protected:
    TabelaRegras(){};

    void adicionarTabela(vector<vector<Regras<Owner> *>>  regras){
        tabelaRegras = regras;
    }
private:
    vector<vector<Regras<Owner> *>>  tabelaRegras;
};

#endif // TABELA_REGRAS_HPP