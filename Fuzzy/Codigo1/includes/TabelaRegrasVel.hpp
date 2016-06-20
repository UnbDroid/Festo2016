#ifndef TABELA_REGRAS_VEL_HPP
#define TABELA_REGRAS_VEL_HPP

#include "TabelaRegras.hpp"
#include "Regras.hpp"
#include "RegrasVel.hpp"
#include <vector>

using namespace std;

template <class Owner>
class TabelaRegrasVel: public TabelaRegras<Owner>{
public:
    TabelaRegrasVel(Owner * o){
        Regras<Owner> * temp1[2] = {new TurboBackward<Owner>(o), new VeryFastBackward<Owner>(o)};
        Regras<Owner> * temp2[2] = {new FastBackward<Owner>(o), new Backward<Owner>(o)};
        vector<Regras<Owner> *> tempV1(temp1,temp1+sizeof(temp1)/sizeof(temp1[0]));
        vector<Regras<Owner> *> tempV2(temp2,temp2+sizeof(temp2)/sizeof(temp2[0]));
        vector<vector<Regras<Owner> *>> tabelaTemp;
        tabelaTemp.push_back(tempV1);
        tabelaTemp.push_back(tempV2);
        this->adicionarTabela(tabelaTemp);
    };
};

#endif // TABELA_REGRAS_HPP