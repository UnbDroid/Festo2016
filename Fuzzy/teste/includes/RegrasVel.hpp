#ifndef REGRAS_VEL_HPP
#define REGRAS_VEL_HPP

#include "Regras.hpp"
#include "robotino.hpp"
#include <vector>

using namespace std;

class TurboBackward: public Regras<Robotino>{
public:
    TurboBackward(Robotino* robotino):Regras<Robotino>(robotino){};
    virtual void executar();
};


class VeryFastBackward: public Regras<Robotino>{
public:
    VeryFastBackward(Robotino* robotino):Regras<Robotino>(robotino){};
    virtual void executar();
};

class FastBackward: public Regras<Robotino>{
public:
    FastBackward(Robotino* robotino):Regras<Robotino>(robotino){};
    virtual void executar();
};

class Backward: public Regras<Robotino>{
public:
    Backward(Robotino* robotino):Regras<Robotino>(robotino){};
    virtual void executar();
};

#endif // REGRAS_VEL_HPP