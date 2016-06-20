#ifndef REGRAS_HPP
#define REGRAS_HPP

using namespace std;

template <class Owner> class Regras{
public:
    Regras(Owner * owner){this->owner = owner;};
    virtual void executar()=0;
protected:
    Owner * owner;
};

#endif // REGRAS_HPP