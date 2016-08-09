#ifndef PERTINENCIA_DISTANCIA_HPP
#define PERTINENCIA_DISTANCIA_HPP

#include "Pertinencia.hpp"

class DZero:public Pertinencia{virtual float avaliar(float);};

class VCL:public Pertinencia{virtual float avaliar(float);};

class CL:public Pertinencia{virtual float avaliar(float);};

class M:public Pertinencia{virtual float avaliar(float);};

class F:public Pertinencia{virtual float avaliar(float);};

class VF:public Pertinencia{virtual float avaliar(float);};

class IN:public Pertinencia{virtual float avaliar(float);};

enum Distancias {DistZero ,VeryClose, Close, Middle, Far, VeryFar, Infinite};

#endif // PERTINENCIA_DISTANCIA_HPP