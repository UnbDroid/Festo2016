#include "RegrasVel.hpp"
#include "Regras.hpp"
#include <iostream>

using namespace std;

template <class Owner>
void TurboBackward<Owner>::executar(){
    cout << "Turbo Backward" << endl;
}

template <class Owner>
void VeryFastBackward<Owner>::executar(){
    cout << "Very Fast Backward" << endl;
}

template <class Owner>
void FastBackward<Owner>::executar(){
    cout << "Fast Backward" << endl;
}

template <class Owner>
void Backward<Owner>::executar(){
    cout << "Backward" << endl;
}