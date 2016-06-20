#include "Classificadores.hpp"
#include "PertinenciaAngulos.hpp"
#include "PertinenciaDistancia.hpp"

ClassificadorAngulo::ClassificadorAngulo(){
    Pertinencia * temp[13] = {new NegInf(), new NegVeryLar(), new NegLar(), new NegMed(), new NegSma(), new NegVerySma(), new Zero(), new PosVerySma(), new PosSma(), new PosMed(), new PosLar(), new PosVeryLar(), new PosInf()};
    vector<Pertinencia *> tempV(temp,temp+sizeof(temp)/sizeof(temp[0]));
    rangeAngulos = tempV;
    adicionarPertinencias(rangeAngulos);
}

string ClassificadorAngulo::rotular(int angulo){
    switch(angulo){
        case NegativeInfinite:
            return "Negative Infinite";
            break;
        case NegativeVeryLarge:
            return "Negative Very Large";
            break;
        case NegativeLarge:
            return "Negative Large";
            break;
        case NegativeMedium:
            return "Negative Medium";
            break;
        case NegativeSmall:
            return "Negative Small";
            break;
        case NegativeVerySmall:
            return "Negative Very Small";
            break;
        case AngZero:
            return "Zero";
            break;
        case PositiveVerySmall:
            return "Positive Very Small";
            break;
        case PositiveSmall:
            return "Positive Small";
            break;
        case PositiveMedium:
            return "Positive Medium";
            break;
        case PositiveLarge:
            return "Positive Large";
            break;
        case PositiveVeryLarge:
            return "Positive Very Large";
            break;
        case PositiveInfinite:
            return "Positive Infinite";
            break;
    }
    return "Nada";
}

ClassificadorDistancia::ClassificadorDistancia(){
    Pertinencia * temp[7] = {new DZero(), new VCL(), new CL(), new M(), new F(), new VF(), new IN()};
    vector<Pertinencia *> tempV(temp,temp+sizeof(temp)/sizeof(temp[0]));
    rangeDistancia = tempV;
    adicionarPertinencias(rangeDistancia);
}

string ClassificadorDistancia::rotular(int distancia){
    switch(distancia){
        case DistZero:
            return "Zero";
            break;
        case VeryClose:
            return "Very Close";
            break;
        case Close:
            return "Close";
            break;
        case Middle:
            return "Middle";
            break;
        case Far:
            return "Far";
            break;
        case VeryFar:
            return "Very Far";
            break;
        case Infinite:
            return "Infinite";
            break;
    }
    return "Nada";
}