#ifndef REGRAS_VEL_HPP
#define REGRAS_VEL_HPP

#include "Regras.hpp"
#include <vector>

using namespace std;

template <class Owner> class TurboBackward: public Regras<Owner>{
public:
    TurboBackward(Owner* o):Regras<Owner>(o){};
    virtual void executar();
};

template <class Owner> class VeryFastBackward: public Regras<Owner>{
public:
    VeryFastBackward(Owner* o):Regras<Owner>(o){};
    virtual void executar();
};

template <class Owner> class FastBackward: public Regras<Owner>{
public:
    FastBackward(Owner* o):Regras<Owner>(o){};
    virtual void executar();
};

template <class Owner> class Backward: public Regras<Owner>{
public:
    Backward(Owner* o):Regras<Owner>(o){};
    virtual void executar();
};

#include "RegrasVel.tpp"

#endif // REGRAS_VEL_HPP