#include "ClassificadorPertinencia.hpp"

ClassificadorPertinencia::ClassificadorPertinencia(vector<Pertinencia *> pertinencia){
    this->pertinencias = pertinencia;
}

int ClassificadorPertinencia::classificar(float valor){
    float max = -1;
    int ind_max = -1;
    float valor_pertinencia;
    for(unsigned int i=0;i<pertinencias.size();i++){
         valor_pertinencia = pertinencias[i]->avaliar(valor);
        if(valor_pertinencia > max){
            max = valor_pertinencia;
            ind_max = i;
        }
    }
    return ind_max;
}

void ClassificadorPertinencia::adicionarPertinencias(vector<Pertinencia *> pertinencia){
    pertinencias = pertinencia;
}