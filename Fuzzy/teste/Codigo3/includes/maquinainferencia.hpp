#ifndef MAQUINA_INFERENCIA_HPP
#define MAQUINA_INFERENCIA_HPP

#include <vector>
#include <string>

using namespace std;

class MaquinaInferencia{
public:
    vector <float> tabelaRegrasVx(vector<float>, vector<float>);
    vector <float> tabelaRegrasVy(vector<float>, vector<float>);
private:
    void Stop(float, float, vector<float> &);
    void TurboBackward(float, float, vector<float> &);
    void VeryFastBackward(float, float, vector<float> &);
    void FastBackward(float, float, vector<float> &);
    void Backward(float, float, vector<float> &);
    void SlowBackward(float, float, vector<float> &);
    void VerySlowBackward(float, float, vector<float> &);
    void VerySlowForward(float, float, vector<float> &);
    void SlowForward(float, float, vector<float> &);
    void Forward(float, float, vector<float> &);
    void FastForward(float, float, vector<float> &);
    void VeryFastForward(float, float, vector<float> &);
    void TurboForward(float, float, vector<float> &);
};

#endif // MAQUINA_INFERENCIA_HPP