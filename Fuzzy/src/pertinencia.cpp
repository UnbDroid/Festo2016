#include <iostream>
#include <string>
#include "Classificadores.hpp"
#include "RegrasVel.hpp"
#include "TabelaRegrasVel.hpp"

using namespace std;

int main(int argc, char * argv[]){
	ClassificadorAngulo CA;
	ClassificadorDistancia CD;
	int num = 4;
	TabelaRegrasVel<int> TR(&num);
	int tipoAngulo = CA.classificar(stof(argv[1]));
	int tipoDist = CD.classificar(stof(argv[2]));
	cout << CA.rotular(tipoAngulo) << endl;
	cout << CD.rotular(tipoDist) << endl;
	TR.acharRegra(tipoAngulo,tipoDist);
}
