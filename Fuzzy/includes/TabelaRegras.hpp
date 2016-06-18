#ifndef TABELA_REGRAS_HPP
#define TABELA_REGRAS_HPP

#include "Regras.hpp"
#include <vector>

using namespace std;

template <class Owner> class TabelaRegras{
public:
    TabelaRegras(vector<vector<Regras<Owner> *>>  regras);

    int acharRegra(int,int);

protected:
    TabelaRegras(){};

    void adicionarTabela(vector<vector<Regras<Owner> *>>  regras);
private:
    vector<vector<Regras<Owner> *>>  tabelaRegras;
};

#include "TabelaRegras.tpp"

#endif // TABELA_REGRAS_HPP