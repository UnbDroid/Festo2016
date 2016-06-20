#include "RegrasVel.hpp"
#include "Regras.hpp"
#include "robotino.hpp"
#include <iostream>

using namespace std;

void TurboBackward::executar(){
    cout << "Turbo Backward" << endl;
    this->owner->setVelocity(200,0,0);
}

void VeryFastBackward::executar(){
    cout << "Very Fast Backward" << endl;
}

void FastBackward::executar(){
    cout << "Fast Backward" << endl;
}

void Backward::executar(){
    cout << "Backward" << endl;
}