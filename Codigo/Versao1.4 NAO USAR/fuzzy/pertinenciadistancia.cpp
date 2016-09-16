#include "pertinenciadistancia.hpp"
#include "pertinencia.hpp"

 float DZero::avaliar(float valor){
    if(valor == 0)
        return 1;
    else if(valor < 50)
        return (valor*-(1./50.)+1.);
    else
        return 0;
}

float VCL::avaliar(float valor){
    if(valor <= 0)
        return 0;
    else if(valor < 50)
        return (valor*(1./50.));
    else if(valor == 50)
        return 1;
    else if(valor < 100)
        return (valor*-(1./50.))+2;
    else if(valor >= 100)
        return 0;
    else
        return -1;
}


 float CL::avaliar(float valor){
    if(valor <= 50)
        return 0;
    else if(valor < 100)
        return (valor*(1./50.))-1;
    else if(valor == 100)
        return 1;
    else if(valor < 150)
        return (valor*-(1./50.))+3;
    else if(valor >= 150)
        return 0;
    else
        return -1;
}

 float M::avaliar(float valor){
    if(valor <= 100)
        return 0;
    else if(valor < 150)
        return (valor*(1./50.))-2;
    else if(valor == 150)
        return 1;
    else if(valor < 200)
        return (valor*-(1./50.))+4;
    else if(valor >= 200)
        return 0;
    else
        return -1;
}

 float F::avaliar(float valor){
    if(valor <= 150)
        return 0;
    else if(valor < 200)
        return (valor*(1./50.))-3;
    else if(valor == 200)
        return 1;
    else if(valor < 250)
        return (valor*-(1./50.))+5;
    else if(valor >= 250)
        return 0;
    else
        return -1;
}

 float VF::avaliar(float valor){
    if(valor <= 200)
        return 0;
    else if(valor < 250)
        return (valor*(1./50.))-4;
    else if(valor == 250)
        return 1;
    else if(valor < 300)
        return (valor*-(1./50.))+6;
    else if(valor >= 300)
        return 0;
    else
        return -1;
}

 float IN::avaliar(float valor){
    if(valor <= 250)
        return 0;
    else if(valor < 300)
        return (valor*(1./50.))-5;
    else if(valor >= 300)
        return 1;
    else
        return -1;
}