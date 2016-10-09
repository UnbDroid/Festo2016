#ifndef CLASSIFICADORES_HPP
#define CLASSIFICADORES_HPP

#include "classificadorpertinencia.hpp"
#include <vector>

using namespace std;

class ClassificadorAngulo: public ClassificadorPertinencia{
public:
    ClassificadorAngulo();
    virtual string rotular(int);
private:
    vector<Pertinencia *> rangeAngulos;
};

class ClassificadorDistancia: public ClassificadorPertinencia{
public:
    ClassificadorDistancia();
    virtual string rotular(int);
private:
    vector<Pertinencia *> rangeDistancia;
};

#endif // CLASSIFICADORES_HPP