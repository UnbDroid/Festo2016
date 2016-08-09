#include "defuzzyficador.hpp"

float Defuzzyficador::centroDeMassa(std::vector<float> funcao){
    float denominador = 0 ,numerador = 0;
    for (int i = 0; i < funcao.size(); ++i){
        numerador += funcao[i]*i;
    }
    for (int i = 0; i < funcao.size(); ++i){
        denominador += funcao[i];
    }
    return numerador/denominador-400;
}