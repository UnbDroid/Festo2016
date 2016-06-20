#include "PertinenciaAngulos.hpp"
#include "Pertinencia.hpp"

 float NegInf::avaliar(float valor){
    if(valor <= -180)
        return 1;
    else if(valor >= -150)
        return 0;
    else
        return (valor*-(1./30.))-5.;
}

float NegVeryLar::avaliar(float valor){
    if(valor <= -180)
        return 0;
    else if(valor < -150)
        return (valor*(1./30.))+6.;
    else if(valor == -150)
        return 1;
    else if(valor < -120)
        return (valor*-(1./30.))-4;
    else if(valor >= -120)
        return 0;
    else
        return -1;
}


 float NegLar::avaliar(float valor){
    if(valor <= -150)
        return 0;
    else if(valor < -120)
        return (valor*(1./30.))+5.;
    else if(valor == -120)
        return 1;
    else if(valor < -90)
        return (valor*-(1./30.))-3;
    else if(valor >= -90)
        return 0;
    else
        return -1;
}

 float NegMed::avaliar(float valor){
    if(valor <= -120)
        return 0;
    else if(valor < -90)
        return (valor*(1./30.))+4.;
    else if(valor == -90)
        return 1;
    else if(valor < -60)
        return (valor*-(1./30.))-2;
    else if(valor >= -60)
        return 0;
    else
        return -1;

}

 float NegSma::avaliar(float valor){
    if(valor <= -90)
        return 0;
    else if(valor < -60)
        return (valor*(1./30.))+3.;
    else if(valor == -60)
        return 1;
    else if(valor < -30)
        return (valor*-(1./30.))-1;
    else if(valor >= -30)
        return 0;
    else
        return -1;
}

 float NegVerySma::avaliar(float valor){
    if(valor <= -60)
        return 0;
    else if(valor < -30)
        return (valor*(1./30.))+2.;
    else if(valor == -30)
        return 1;
    else if(valor < -0)
        return (valor*-(1./30.));
    else if(valor >= -0)
        return 0;
    else
        return -1;

}

 float Zero::avaliar(float valor){
    if(valor <= -30)
        return 0;
    else if(valor < 0)
        return (valor*(1./30.))+1.;
    else if(valor == 0)
        return 1;
    else if(valor < 30)
        return (valor*-(1./30.))+1;
    else if(valor >= 30)
        return 0;
    else
        return -1;

}

 float PosVerySma::avaliar(float valor){
    if(valor <= 0)
        return 0;
    else if(valor < 30)
        return (valor*(1./30.));
    else if(valor == 30)
        return 1;
    else if(valor < 60)
        return (valor*-(1./30.))+2;
    else if(valor >= 60)
        return 0;
    else
        return -1;
}

 float PosSma::avaliar(float valor){
    if(valor <= 30)
        return 0;
    else if(valor < 60)
        return (valor*(1./30.))-1;
    else if(valor == 60)
        return 1;
    else if(valor < 90)
        return (valor*-(1./30.))+3;
    else if(valor >= 90)
        return 0;
    else
        return -1;
}

 float PosMed::avaliar(float valor){
    if(valor <= 60)
        return 0;
    else if(valor < 90)
        return (valor*(1./30.))-2;
    else if(valor == 90)
        return 1;
    else if(valor < 120)
        return (valor*-(1./30.))+4;
    else if(valor >= 120)
        return 0;
    else
        return -1;
}

 float PosLar::avaliar(float valor){
    if(valor <= 90)
        return 0;
    else if(valor < 120)
        return (valor*(1./30.))-3;
    else if(valor == 120)
        return 1;
    else if(valor < 150)
        return (valor*-(1./30.))+5;
    else if(valor >= 150)
        return 0;
    else
        return -1;
}

 float PosVeryLar::avaliar(float valor){
    if(valor <= 120)
        return 0;
    else if(valor < 150)
        return (valor*(1./30.))-4;
    else if(valor == 150)
        return 1;
    else if(valor < 180)
        return (valor*-(1./30.))+6;
    else if(valor >= 180)
        return 0;
    else
        return -1;
}


 float PosInf::avaliar(float valor){
    if(valor <= 150)
        return 0;
    else if(valor >= 180)
        return 1;
    else
        return (valor*(1./30.))-5.;
}
