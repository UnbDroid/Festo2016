#include "maquinainferencia.hpp"
#include "pertinenciaangulos.hpp"
#include "pertinenciadistancia.hpp"
#include <algorithm>

vector <float> MaquinaInferencia::tabelaRegrasVx(vector<float> vetorDistancia, vector<float> vetorAngulo){
    vector <float> pertinenciaVx(801,0.0);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[NegativeVeryLarge],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[NegativeLarge],vetorDistancia[DistZero],pertinenciaVx);

    Stop(vetorAngulo[NegativeMedium],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[VeryClose],pertinenciaVx);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[Close],pertinenciaVx);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[Middle],pertinenciaVx);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[Far],pertinenciaVx);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[VeryFar],pertinenciaVx);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[Infinite],pertinenciaVx);

    Stop(vetorAngulo[NegativeSmall],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[NegativeVerySmall],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[AngZero],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[PositiveVerySmall],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[PositiveSmall],vetorDistancia[DistZero],pertinenciaVx);

    Stop(vetorAngulo[PositiveMedium],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[VeryClose],pertinenciaVx);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[Close],pertinenciaVx);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[Middle],pertinenciaVx);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[Far],pertinenciaVx);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[VeryFar],pertinenciaVx);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[Infinite],pertinenciaVx);

    Stop(vetorAngulo[PositiveLarge],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[PositiveVeryLarge],vetorDistancia[DistZero],pertinenciaVx);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[DistZero],pertinenciaVx);

    TurboBackward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Infinite],pertinenciaVx);
    TurboBackward(vetorAngulo[NegativeInfinite],vetorDistancia[Infinite],pertinenciaVx);
    TurboBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Infinite],pertinenciaVx);
    TurboBackward(vetorAngulo[PositiveInfinite],vetorDistancia[Infinite],pertinenciaVx);

    VeryFastBackward(vetorAngulo[NegativeInfinite],vetorDistancia[VeryFar],pertinenciaVx);
    VeryFastBackward(vetorAngulo[NegativeVeryLarge],vetorDistancia[VeryFar],pertinenciaVx);
    VeryFastBackward(vetorAngulo[NegativeLarge],vetorDistancia[Infinite],pertinenciaVx);
    VeryFastBackward(vetorAngulo[PositiveLarge],vetorDistancia[Infinite],pertinenciaVx);
    VeryFastBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[VeryFar],pertinenciaVx);
    VeryFastBackward(vetorAngulo[PositiveInfinite],vetorDistancia[VeryFar],pertinenciaVx);

    FastBackward(vetorAngulo[NegativeInfinite],vetorDistancia[Far],pertinenciaVx);
    FastBackward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Far],pertinenciaVx);
    FastBackward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Middle],pertinenciaVx);
    FastBackward(vetorAngulo[NegativeLarge],vetorDistancia[VeryFar],pertinenciaVx);
    FastBackward(vetorAngulo[PositiveLarge],vetorDistancia[VeryFar],pertinenciaVx);
    FastBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Middle],pertinenciaVx);
    FastBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Far],pertinenciaVx);
    FastBackward(vetorAngulo[PositiveInfinite],vetorDistancia[Far],pertinenciaVx);

    Backward(vetorAngulo[NegativeInfinite],vetorDistancia[Middle],pertinenciaVx);
    Backward(vetorAngulo[NegativeVeryLarge],vetorDistancia[VeryClose],pertinenciaVx);
    Backward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Close],pertinenciaVx);
    Backward(vetorAngulo[NegativeLarge],vetorDistancia[Middle],pertinenciaVx);
    Backward(vetorAngulo[NegativeLarge],vetorDistancia[Far],pertinenciaVx);
    Backward(vetorAngulo[PositiveLarge],vetorDistancia[Far],pertinenciaVx);
    Backward(vetorAngulo[PositiveLarge],vetorDistancia[Middle],pertinenciaVx);
    Backward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Close],pertinenciaVx);
    Backward(vetorAngulo[PositiveVeryLarge],vetorDistancia[VeryClose],pertinenciaVx);
    Backward(vetorAngulo[PositiveInfinite],vetorDistancia[Middle],pertinenciaVx);

    SlowBackward(vetorAngulo[NegativeInfinite],vetorDistancia[Close],pertinenciaVx);
    SlowBackward(vetorAngulo[NegativeLarge],vetorDistancia[Close],pertinenciaVx);
    SlowBackward(vetorAngulo[PositiveLarge],vetorDistancia[Close],pertinenciaVx);
    SlowBackward(vetorAngulo[PositiveInfinite],vetorDistancia[Close],pertinenciaVx);

    VerySlowBackward(vetorAngulo[NegativeInfinite],vetorDistancia[VeryClose],pertinenciaVx);
    VerySlowBackward(vetorAngulo[NegativeLarge],vetorDistancia[VeryClose],pertinenciaVx);
    VerySlowBackward(vetorAngulo[PositiveLarge],vetorDistancia[VeryClose],pertinenciaVx);
    VerySlowBackward(vetorAngulo[PositiveInfinite],vetorDistancia[VeryClose],pertinenciaVx);

    VerySlowForward(vetorAngulo[NegativeSmall],vetorDistancia[VeryClose],pertinenciaVx);
    VerySlowForward(vetorAngulo[AngZero],vetorDistancia[VeryClose],pertinenciaVx);
    VerySlowForward(vetorAngulo[PositiveSmall],vetorDistancia[VeryClose],pertinenciaVx);

    SlowForward(vetorAngulo[NegativeSmall],vetorDistancia[Close],pertinenciaVx);
    SlowForward(vetorAngulo[AngZero],vetorDistancia[Close],pertinenciaVx);
    SlowForward(vetorAngulo[PositiveSmall],vetorDistancia[Close],pertinenciaVx);

    Forward(vetorAngulo[NegativeSmall],vetorDistancia[Middle],pertinenciaVx);
    Forward(vetorAngulo[NegativeSmall],vetorDistancia[Far],pertinenciaVx);
    Forward(vetorAngulo[NegativeVerySmall],vetorDistancia[VeryClose],pertinenciaVx);
    Forward(vetorAngulo[NegativeVerySmall],vetorDistancia[Close],pertinenciaVx);
    Forward(vetorAngulo[AngZero],vetorDistancia[Middle],pertinenciaVx);
    Forward(vetorAngulo[PositiveVerySmall],vetorDistancia[Close],pertinenciaVx);
    Forward(vetorAngulo[PositiveVerySmall],vetorDistancia[VeryClose],pertinenciaVx);
    Forward(vetorAngulo[PositiveSmall],vetorDistancia[Far],pertinenciaVx);
    Forward(vetorAngulo[PositiveSmall],vetorDistancia[Middle],pertinenciaVx);

    FastForward(vetorAngulo[NegativeSmall],vetorDistancia[VeryFar],pertinenciaVx);
    FastForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Far],pertinenciaVx);
    FastForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Middle],pertinenciaVx);
    FastForward(vetorAngulo[AngZero],vetorDistancia[Far],pertinenciaVx);
    FastForward(vetorAngulo[PositiveVerySmall],vetorDistancia[Middle],pertinenciaVx);
    FastForward(vetorAngulo[PositiveVerySmall],vetorDistancia[Far],pertinenciaVx);
    FastForward(vetorAngulo[PositiveSmall],vetorDistancia[VeryFar],pertinenciaVx);

    VeryFastForward(vetorAngulo[NegativeSmall],vetorDistancia[Infinite],pertinenciaVx);
    VeryFastForward(vetorAngulo[NegativeVerySmall],vetorDistancia[VeryFar],pertinenciaVx);
    VeryFastForward(vetorAngulo[AngZero],vetorDistancia[VeryFar],pertinenciaVx);
    VeryFastForward(vetorAngulo[PositiveVerySmall],vetorDistancia[VeryFar],pertinenciaVx);
    VeryFastForward(vetorAngulo[PositiveSmall],vetorDistancia[Infinite],pertinenciaVx);

    TurboForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Infinite],pertinenciaVx);
    TurboForward(vetorAngulo[AngZero],vetorDistancia[Infinite],pertinenciaVx);
    TurboForward(vetorAngulo[PositiveVerySmall],vetorDistancia[Infinite],pertinenciaVx);


    return pertinenciaVx;
}

vector <float> MaquinaInferencia::tabelaRegrasVy(vector<float> vetorDistancia, vector<float> vetorAngulo){
    vector <float> pertinenciaVy(801,0.0);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[VeryClose],pertinenciaVy);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[Close],pertinenciaVy);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[Middle],pertinenciaVy);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[Far],pertinenciaVy);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[VeryFar],pertinenciaVy);
    Stop(vetorAngulo[NegativeInfinite],vetorDistancia[Infinite],pertinenciaVy);

    Stop(vetorAngulo[NegativeVeryLarge],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[NegativeLarge],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[NegativeMedium],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[NegativeSmall],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[NegativeVerySmall],vetorDistancia[DistZero],pertinenciaVy);

    Stop(vetorAngulo[AngZero],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[AngZero],vetorDistancia[VeryClose],pertinenciaVy);
    Stop(vetorAngulo[AngZero],vetorDistancia[Close],pertinenciaVy);
    Stop(vetorAngulo[AngZero],vetorDistancia[Middle],pertinenciaVy);
    Stop(vetorAngulo[AngZero],vetorDistancia[Far],pertinenciaVy);
    Stop(vetorAngulo[AngZero],vetorDistancia[VeryFar],pertinenciaVy);
    Stop(vetorAngulo[AngZero],vetorDistancia[Infinite],pertinenciaVy);

    Stop(vetorAngulo[PositiveVerySmall],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[PositiveSmall],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[PositiveMedium],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[PositiveLarge],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[PositiveVeryLarge],vetorDistancia[DistZero],pertinenciaVy);

    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[DistZero],pertinenciaVy);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[VeryClose],pertinenciaVy);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[Close],pertinenciaVy);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[Middle],pertinenciaVy);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[Far],pertinenciaVy);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[VeryFar],pertinenciaVy);
    Stop(vetorAngulo[PositiveInfinite],vetorDistancia[Infinite],pertinenciaVy);

    TurboBackward(vetorAngulo[PositiveSmall],vetorDistancia[Infinite],pertinenciaVy);
    TurboBackward(vetorAngulo[PositiveMedium],vetorDistancia[Infinite],pertinenciaVy);
    TurboBackward(vetorAngulo[PositiveLarge],vetorDistancia[Infinite],pertinenciaVy);

    VeryFastBackward(vetorAngulo[PositiveSmall],vetorDistancia[VeryFar],pertinenciaVy);
    VeryFastBackward(vetorAngulo[PositiveMedium],vetorDistancia[VeryFar],pertinenciaVy);
    VeryFastBackward(vetorAngulo[PositiveLarge],vetorDistancia[VeryFar],pertinenciaVy);

    FastBackward(vetorAngulo[PositiveVerySmall],vetorDistancia[Infinite],pertinenciaVy);
    FastBackward(vetorAngulo[PositiveSmall],vetorDistancia[Far],pertinenciaVy);
    FastBackward(vetorAngulo[PositiveSmall],vetorDistancia[Middle],pertinenciaVy);
    FastBackward(vetorAngulo[PositiveMedium],vetorDistancia[Far],pertinenciaVy);
    FastBackward(vetorAngulo[PositiveLarge],vetorDistancia[Middle],pertinenciaVy);
    FastBackward(vetorAngulo[PositiveLarge],vetorDistancia[Far],pertinenciaVy);
    FastBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Infinite],pertinenciaVy);


    Backward(vetorAngulo[PositiveVerySmall],vetorDistancia[VeryFar],pertinenciaVy);
    Backward(vetorAngulo[PositiveSmall],vetorDistancia[Close],pertinenciaVy);
    Backward(vetorAngulo[PositiveMedium],vetorDistancia[Middle],pertinenciaVy);
    Backward(vetorAngulo[PositiveLarge],vetorDistancia[Close],pertinenciaVy);
    Backward(vetorAngulo[PositiveVeryLarge],vetorDistancia[VeryFar],pertinenciaVy);

    SlowBackward(vetorAngulo[PositiveVerySmall],vetorDistancia[Middle],pertinenciaVy);
    SlowBackward(vetorAngulo[PositiveVerySmall],vetorDistancia[Far],pertinenciaVy);
    SlowBackward(vetorAngulo[PositiveSmall],vetorDistancia[VeryClose],pertinenciaVy);
    SlowBackward(vetorAngulo[PositiveMedium],vetorDistancia[Close],pertinenciaVy);
    SlowBackward(vetorAngulo[PositiveLarge],vetorDistancia[VeryClose],pertinenciaVy);
    SlowBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Middle],pertinenciaVy);
    SlowBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Far],pertinenciaVy);

    VerySlowBackward(vetorAngulo[PositiveVerySmall],vetorDistancia[VeryClose],pertinenciaVy);
    VerySlowBackward(vetorAngulo[PositiveVerySmall],vetorDistancia[Close],pertinenciaVy);
    VerySlowBackward(vetorAngulo[PositiveMedium],vetorDistancia[VeryClose],pertinenciaVy);
    VerySlowBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[Close],pertinenciaVy);
    VerySlowBackward(vetorAngulo[PositiveVeryLarge],vetorDistancia[VeryClose],pertinenciaVy);

    VerySlowForward(vetorAngulo[NegativeVerySmall],vetorDistancia[VeryClose],pertinenciaVy);
    VerySlowForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Close],pertinenciaVy);
    VerySlowForward(vetorAngulo[NegativeMedium],vetorDistancia[VeryClose],pertinenciaVy);
    VerySlowForward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Close],pertinenciaVy);
    VerySlowForward(vetorAngulo[NegativeVeryLarge],vetorDistancia[VeryClose],pertinenciaVy);

    SlowForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Middle],pertinenciaVy);
    SlowForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Far],pertinenciaVy);
    SlowForward(vetorAngulo[NegativeSmall],vetorDistancia[VeryClose],pertinenciaVy);
    SlowForward(vetorAngulo[NegativeMedium],vetorDistancia[Close],pertinenciaVy);
    SlowForward(vetorAngulo[NegativeLarge],vetorDistancia[VeryClose],pertinenciaVy);
    SlowForward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Middle],pertinenciaVy);
    SlowForward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Far],pertinenciaVy);

    Forward(vetorAngulo[NegativeVerySmall],vetorDistancia[VeryFar],pertinenciaVy);
    Forward(vetorAngulo[NegativeSmall],vetorDistancia[Close],pertinenciaVy);
    Forward(vetorAngulo[NegativeMedium],vetorDistancia[Middle],pertinenciaVy);
    Forward(vetorAngulo[NegativeLarge],vetorDistancia[Close],pertinenciaVy);
    Forward(vetorAngulo[NegativeVeryLarge],vetorDistancia[VeryFar],pertinenciaVy);

    FastForward(vetorAngulo[NegativeVerySmall],vetorDistancia[Infinite],pertinenciaVy);
    FastForward(vetorAngulo[NegativeSmall],vetorDistancia[Far],pertinenciaVy);
    FastForward(vetorAngulo[NegativeSmall],vetorDistancia[Middle],pertinenciaVy);
    FastForward(vetorAngulo[NegativeMedium],vetorDistancia[Far],pertinenciaVy);
    FastForward(vetorAngulo[NegativeLarge],vetorDistancia[Middle],pertinenciaVy);
    FastForward(vetorAngulo[NegativeLarge],vetorDistancia[Far],pertinenciaVy);
    FastForward(vetorAngulo[NegativeVeryLarge],vetorDistancia[Infinite],pertinenciaVy);

    VeryFastForward(vetorAngulo[NegativeSmall],vetorDistancia[VeryFar],pertinenciaVy);
    VeryFastForward(vetorAngulo[NegativeMedium],vetorDistancia[VeryFar],pertinenciaVy);
    VeryFastForward(vetorAngulo[NegativeLarge],vetorDistancia[VeryFar],pertinenciaVy);

    TurboForward(vetorAngulo[NegativeSmall],vetorDistancia[Infinite],pertinenciaVy);
    TurboForward(vetorAngulo[NegativeMedium],vetorDistancia[Infinite],pertinenciaVy);
    TurboForward(vetorAngulo[NegativeLarge],vetorDistancia[Infinite],pertinenciaVy);


    return pertinenciaVy;
}

void MaquinaInferencia::TurboBackward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(-400.0+float(i))+8;
        if(aux > valorRegra){
            if(valorRegra > valores[i]){
                valores[i] = valorRegra;
            }
        }else{
            if(aux > valores[i]){
                valores[i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[50]){
            valores[50] = valorRegra;
        }
    }else{
        if(aux > valores[50]){
            valores[50] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(-350+float(i))-6;
        if(aux > valorRegra){
            if(valorRegra > valores[50+i]){
                valores[50+i] = valorRegra;
            }
        }else{
            if(aux > valores[50+i]){
                valores[50+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::VeryFastBackward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(-350.0+float(i))+7;
        if(aux > valorRegra){
            if(valorRegra > valores[50+i]){
                valores[50+i] = valorRegra;
            }
        }else{
            if(aux > valores[50+i]){
                valores[50+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[100]){
            valores[100] = valorRegra;
        }
    }else{
        if(aux > valores[100]){
            valores[100] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(-300+float(i))-5;
        if(aux > valorRegra){
            if(valorRegra > valores[100+i]){
                valores[100+i] = valorRegra;
            }
        }else{
            if(aux > valores[100+i]){
                valores[100+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::FastBackward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(-300.0+float(i))+6;
        if(aux > valorRegra){
            if(valorRegra > valores[100+i]){
                valores[100+i] = valorRegra;
            }
        }else{
            if(aux > valores[100+i]){
                valores[100+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[150]){
            valores[150] = valorRegra;
        }
    }else{
        if(aux > valores[150]){
            valores[150] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(-250+float(i))-4;
        if(aux > valorRegra){
            if(valorRegra > valores[150+i]){
                valores[150+i] = valorRegra;
            }
        }else{
            if(aux > valores[150+i]){
                valores[150+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::Backward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(-250.0+float(i))+5;
        if(aux > valorRegra){
            if(valorRegra > valores[150+i]){
                valores[150+i] = valorRegra;
            }
        }else{
            if(aux > valores[150+i]){
                valores[150+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[200]){
            valores[200] = valorRegra;
        }
    }else{
        if(aux > valores[200]){
            valores[200] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(-200+float(i))-3;
        if(aux > valorRegra){
            if(valorRegra > valores[200+i]){
                valores[200+i] = valorRegra;
            }
        }else{
            if(aux > valores[200+i]){
                valores[200+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::SlowBackward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(-200.0+float(i))+4;
        if(aux > valorRegra){
            if(valorRegra > valores[200+i]){
                valores[200+i] = valorRegra;
            }
        }else{
            if(aux > valores[200+i]){
                valores[200+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[250]){
            valores[250] = valorRegra;
        }
    }else{
        if(aux > valores[250]){
            valores[250] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(-150+float(i))-2;
        if(aux > valorRegra){
            if(valorRegra > valores[250+i]){
                valores[250+i] = valorRegra;
            }
        }else{
            if(aux > valores[250+i]){
                valores[250+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::VerySlowBackward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(-150.0+float(i))+3;
        if(aux > valorRegra){
            if(valorRegra > valores[250+i]){
                valores[250+i] = valorRegra;
            }
        }else{
            if(aux > valores[250+i]){
                valores[250+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[300]){
            valores[300] = valorRegra;
        }
    }else{
        if(aux > valores[300]){
            valores[300] = aux;
        }
    }
    for(unsigned int i=1; i < 101; i++){
        //float aux = -0.02*(-100+float(i))-1;
        float aux = -0.01*(-100+float(i));
        if(aux > valorRegra){
            if(valorRegra > valores[300+i]){
                valores[300+i] = valorRegra;
            }
        }else{
            if(aux > valores[300+i]){
                valores[300+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::Stop(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 100; i++){
        float aux = 0.01*(-100.0+float(i))+1;
        if(aux > valorRegra){
            if(valorRegra > valores[300+i]){
                valores[300+i] = valorRegra;
            }
        }else{
            if(aux > valores[300+i]){
                valores[300+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[400]){
            valores[400] = valorRegra;
        }
    }else{
        if(aux > valores[400]){
            valores[400] = aux;
        }
    }
    for(unsigned int i= 1; i < 101; i++){
        float aux = -0.01*(float(i))+1;
        if(aux > valorRegra){
            if(valorRegra > valores[400+i]){
                valores[400+i] = valorRegra;
            }
        }else{
            if(aux > valores[400+i]){
                valores[400+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::VerySlowForward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 100; i++){
        //float aux = 0.02*(50.0+float(i))-1;
        float aux = 0.01*(float(i));
        if(aux > valorRegra){
            if(valorRegra > valores[400+i]){
                valores[400+i] = valorRegra;
            }
        }else{
            if(aux > valores[400+i]){
                valores[400+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[500]){
            valores[500] = valorRegra;
        }
    }else{
        if(aux > valores[500]){
            valores[500] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(100+float(i))+3;
        if(aux > valorRegra){
            if(valorRegra > valores[500+i]){
                valores[500+i] = valorRegra;
            }
        }else{
            if(aux > valores[500+i]){
                valores[500+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::SlowForward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(100.0+float(i))-2;
        if(aux > valorRegra){
            if(valorRegra > valores[500+i]){
                valores[500+i] = valorRegra;
            }
        }else{
            if(aux > valores[500+i]){
                valores[500+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[550]){
            valores[550] = valorRegra;
        }
    }else{
        if(aux > valores[550]){
            valores[550] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(150+float(i))+4;
        if(aux > valorRegra){
            if(valorRegra > valores[550+i]){
                valores[550+i] = valorRegra;
            }
        }else{
            if(aux > valores[550+i]){
                valores[550+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::Forward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(150.0+float(i))-3;
        if(aux > valorRegra){
            if(valorRegra > valores[550+i]){
                valores[550+i] = valorRegra;
            }
        }else{
            if(aux > valores[550+i]){
                valores[550+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[600]){
            valores[600] = valorRegra;
        }
    }else{
        if(aux > valores[600]){
            valores[600] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(200+float(i))+5;
        if(aux > valorRegra){
            if(valorRegra > valores[600+i]){
                valores[600+i] = valorRegra;
            }
        }else{
            if(aux > valores[600+i]){
                valores[600+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::FastForward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(200.0+float(i))-4;
        if(aux > valorRegra){
            if(valorRegra > valores[600+i]){
                valores[600+i] = valorRegra;
            }
        }else{
            if(aux > valores[600+i]){
                valores[600+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[650]){
            valores[650] = valorRegra;
        }
    }else{
        if(aux > valores[650]){
            valores[650] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(250+float(i))+6;
        if(aux > valorRegra){
            if(valorRegra > valores[650+i]){
                valores[650+i] = valorRegra;
            }
        }else{
            if(aux > valores[650+i]){
                valores[650+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::VeryFastForward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(250.0+float(i))-5;
        if(aux > valorRegra){
            if(valorRegra > valores[650+i]){
                valores[650+i] = valorRegra;
            }
        }else{
            if(aux > valores[650+i]){
                valores[650+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[700]){
            valores[700] = valorRegra;
        }
    }else{
        if(aux > valores[700]){
            valores[700] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(300+float(i))+7;
        if(aux > valorRegra){
            if(valorRegra > valores[700+i]){
                valores[700+i] = valorRegra;
            }
        }else{
            if(aux > valores[700+i]){
                valores[700+i] = aux;
            }
        }
    }
}

void MaquinaInferencia::TurboForward(float theta, float dist, vector<float> & valores){
    float valorRegra = min(theta,dist);
    for(unsigned int i= 0; i < 50; i++){
        float aux = 0.02*(300.0+float(i))-6;
        if(aux > valorRegra){
            if(valorRegra > valores[700+i]){
                valores[700+i] = valorRegra;
            }
        }else{
            if(aux > valores[700+i]){
                valores[700+i] = aux;
            }
        }
    }
    float aux = 1;
    if(aux > valorRegra){
        if(valorRegra > valores[750]){
            valores[750] = valorRegra;
        }
    }else{
        if(aux > valores[750]){
            valores[750] = aux;
        }
    }
    for(unsigned int i=1; i < 51; i++){
        float aux = -0.02*(350+float(i))+8;
        if(aux > valorRegra){
            if(valorRegra > valores[750+i]){
                valores[750+i] = valorRegra;
            }
        }else{
            if(aux > valores[750+i]){
                valores[750+i] = aux;
            }
        }
    }
}