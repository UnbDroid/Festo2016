#ifndef TABELA_REGRAS_VEL_HPP
#define TABELA_REGRAS_VEL_HPP

#include "TabelaRegras.hpp"
#include "Regras.hpp"
#include "RegrasVel.hpp"
#include <vector>

using namespace std;

class TabelaRegrasVel: public TabelaRegras<Robotino>{
public:
    TabelaRegrasVel(Robotino * o){
        Regras<Robotino> * temp1[2] = {new TurboBackward(o), new VeryFastBackward(o)};
        Regras<Robotino> * temp2[2] = {new FastBackward(o), new Backward(o)};
        vector<Regras<Robotino> *> tempV1(temp1,temp1+sizeof(temp1)/sizeof(temp1[0]));
        vector<Regras<Robotino> *> tempV2(temp2,temp2+sizeof(temp2)/sizeof(temp2[0]));
        vector<vector<Regras<Robotino> *>> tabelaTemp;
        tabelaTemp.push_back(tempV1);
        tabelaTemp.push_back(tempV2);
        this->adicionarTabela(tabelaTemp);
    };
};

#endif // TABELA_REGRAS_HPP