#ifndef CLASSIFICADOR_PERTINENCIA_HPP
#define CLASSIFICADOR_PERTINENCIA_HPP

#include "Pertinencia.hpp"
#include <vector>
#include <string>

using namespace std;

class ClassificadorPertinencia{
public:
    ClassificadorPertinencia(vector<Pertinencia *> pertinencia);

    int classificar(float);

    virtual string rotular(int){return "";};

protected:
    ClassificadorPertinencia(){};

    void adicionarPertinencias(vector<Pertinencia *> pertinencia);
private:
    vector<Pertinencia *> pertinencias;
};

#endif // CLASSIFICADOR_PERTINENCIA_HPP