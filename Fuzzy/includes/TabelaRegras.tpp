#include "TabelaRegras.hpp"

template <class Owner>
TabelaRegras<Owner>::TabelaRegras(vector<vector<Regras<Owner> *>>  regras){
    tabelaRegras = regras;
}

template <class Owner>
int TabelaRegras<Owner>::acharRegra(int m,int n){
    if ((unsigned) m > tabelaRegras.size()){
        return -1;
    }
    if((unsigned) n > tabelaRegras[m].size()){
        return -1;
    }
    tabelaRegras[m][n]->executar();
    return 0;
}

template <class Owner>
void TabelaRegras<Owner>::adicionarTabela(vector<vector<Regras<Owner> *>>  regras){
    tabelaRegras = regras;
}