#ifndef PERTINENCIA_ANGULOS_HPP
#define PERTINENCIA_ANGULOS_HPP

#include "pertinencia.hpp"

class NegInf:public Pertinencia{virtual float avaliar(float);};

class NegVeryLar:public Pertinencia{virtual float avaliar(float);};

class NegLar:public Pertinencia{virtual float avaliar(float);};

class NegMed:public Pertinencia{virtual float avaliar(float);};

class NegSma:public Pertinencia{virtual float avaliar(float);};

class NegVerySma:public Pertinencia{virtual float avaliar(float);};

class Zero:public Pertinencia{virtual float avaliar(float);};

class PosVerySma:public Pertinencia{virtual float avaliar(float);};

class PosSma:public Pertinencia{virtual float avaliar(float);};

class PosMed:public Pertinencia{virtual float avaliar(float);};

class PosLar:public Pertinencia{virtual float avaliar(float);};

class PosVeryLar:public Pertinencia{virtual float avaliar(float);};

class PosInf:public Pertinencia{virtual float avaliar(float);};

enum Angulos {NegativeInfinite, NegativeVeryLarge, NegativeLarge, NegativeMedium, NegativeSmall, NegativeVerySmall, AngZero, PositiveVerySmall, PositiveSmall, PositiveMedium, PositiveLarge, PositiveVeryLarge, PositiveInfinite};

#endif // PERTINENCIA_ANGULOS_HPP