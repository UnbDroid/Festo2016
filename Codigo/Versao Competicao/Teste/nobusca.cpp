#include "nobusca.hpp"

NoBusca::NoBusca(){
	custoEstimado = -999;
	custoCaminho = 0;
}

NoBusca::NoBusca(std::vector<int> val):valores(val){
	custoEstimado = -999;
	custoCaminho = 0;
}

NoBusca::NoBusca(std::vector<int> val,  int c):valores(val),custoEstimado(c){
	custoEstimado = c;
	custoCaminho = 0;
}

NoBusca::NoBusca(std::vector<int> val, std::vector<NoBusca> cam, int c_caminho):valores(val){
	custoCaminho = c_caminho+1;
}

NoBusca::NoBusca(std::vector<int> val,  int c, std::vector<NoBusca> cam, int c_caminho):valores(val),custoEstimado(c){
	custoEstimado = c;
	custoCaminho = c_caminho+1;
}

void NoBusca::calcularCusto(std::vector<int> desejado){
	custoEstimado = 0;
	for (int i = 0; i < valores.size() || i < desejado.size(); ++i){
		if(valores[i]!=desejado[i]){
			custoEstimado++;
		}
	}
}

void NoBusca::calcularCusto(NoBusca noDesejado){
	std::vector<int> desejado = noDesejado.meusValores();
	custoEstimado = 0;
	for (int i = 0; i < valores.size() || i < desejado.size(); ++i){
		if(valores[i]!=desejado[i]){
			custoEstimado++;
		}
	}
}

std::vector<NoBusca> NoBusca::expandirNo(NoBusca noDesejado){
	std::vector<int> permutar;
    	std::vector<NoBusca> combinacoes;

    	permutar = valores;


	int posicaoGap = std::find(valores.begin(), valores.end(),VAZIO) - valores.begin();

	std::sort (permutar.begin(),permutar.end());
	do {
	if(permutar!=valores && permutar[posicaoGap]!=valores[posicaoGap]){
		this->calcularCusto(permutar);
		if(custoEstimado==2){
			std::vector<NoBusca> criarCaminho;
			criarCaminho = caminho;
			NoBusca novo = NoBusca(permutar,meuCaminho(),meuCustoCaminho());
			novo.calcularCusto(noDesejado);

			criarCaminho.push_back(novo);
			novo.adicionarAoCaminho(criarCaminho);
			    // for (std::vector<NoBusca>::iterator i = criarCaminho.begin(); i != criarCaminho.end(); ++i)
			    // {
			    //     std::cout <<"Estado no caminho: "<<*i<<"\n";
			    // }
			//std::cout << novo << "\n";
			combinacoes.push_back(novo);
		}
	}
	}while ( std::next_permutation(permutar.begin(),permutar.end()) );
	this->calcularCusto(noDesejado);
	return combinacoes;
}

std::ostream &operator<<(std::ostream &os, NoBusca &c) {
	os << "(";
	for (int i = 0; i < c.meusValores().size(); ++i){
		if( i == c.meusValores().size()-1){
			os << c.meusValores()[i];
		}else{
			os << c.meusValores()[i] << ", ";
		}
	}
	return os << ") Custo: " << c.meuCustoTotal();
}

NoBusca ordenar(NoBusca noInicial, NoBusca noFinal){
    NoBusca noAtual;
    std::vector<NoBusca> NosASeremPesquisados;
    std::vector<NoBusca> NosVisitados;
    std::vector<NoBusca> NosFilhos;
    std::vector<NoBusca> criarCaminho;



    noInicial.calcularCusto(noFinal);
    criarCaminho.push_back(noInicial);
    noInicial.adicionarAoCaminho(criarCaminho);
    NosASeremPesquisados.push_back(noInicial);

    while(!NosASeremPesquisados.empty()) {
        std::vector<NoBusca>::iterator iteratorNoAtual = std::min_element(NosASeremPesquisados.begin(), NosASeremPesquisados.end());
        noAtual = *iteratorNoAtual;
         //std::cout <<"Estado atual: "<<noAtual<<"\n";
         if(noAtual == noFinal){
            return noAtual;

        }else{
            NosVisitados.push_back(noAtual);
            NosASeremPesquisados.erase(iteratorNoAtual);

            NosFilhos = noAtual.expandirNo(noFinal);
            for (std::vector<NoBusca>::iterator i = NosFilhos.begin(); i != NosFilhos.end(); ++i){
                if(std::find(NosVisitados.begin(), NosVisitados.end(),*i) == NosVisitados.end()){
                    NosASeremPesquisados.push_back(*i);
                }
            }
        }
    }
}


void planejarEstoque(NoBusca noInicial, NoBusca noFinal){
	std::vector<int> inicial = noInicial.meusValores();
	std::vector<int> final = noFinal.meusValores();
	std::vector<int> aux , aux2;
	std::vector<NoBusca> nosIniciais;
	std::vector<NoBusca> nosFinais;
	NoBusca resultado;
	NoBusca melhorResultado;
	int menorCusto = 999999;
	for (int i = 0; i < inicial.size(); ++i){
		aux = inicial;
		aux2 = final;
		aux[i] = VAZIO;
		int j = std::find(final.begin(), final.end(), inicial[i]) - final.begin();
		aux2[j] = VAZIO;
		nosIniciais.push_back(NoBusca(aux));
		nosFinais.push_back(NoBusca(aux2));
	}

	for (int i = 0; i < nosIniciais.size(); ++i){
		//std::cout << nosIniciais[i] << " Inicial \n";
		//std::cout << nosFinais[i] << " final \n";
		resultado = ordenar(nosIniciais[i],nosFinais[i]);
		if(resultado.meuCustoCaminho() < menorCusto){
			menorCusto = resultado.meuCustoCaminho();
			melhorResultado = resultado;
		}
	}
	std::cout <<"Melhor resultado: \n";
	for (int i = 0; i < melhorResultado.meuCaminho().size(); ++i){
        		std::cout << melhorResultado.meuCaminho()[i] << "\n";
    	}
}
