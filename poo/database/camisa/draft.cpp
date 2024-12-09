#include <iostream>
#include <string.h>
#include <set>

using namespace std;

class Roupa{
private:
    string tamanho=0;
    set<string> value = {"PP", "P", "M", "G", "GG", "XG"};
public:
    // construtor
    Roupa() : tamanho("PP") {}

    // como tamanho esta private, chama set e get
    string getTamanho(){
        return tamanho;
    }

    void setTamanho(string& T){
        if(value.find(T)!= value.end()){
            tamanho = T;
            cout << "Tamanho atual da roupa: " << tamanho << endl;
        } else {
            cout << "Erro: Tamanho inválido! Valores permitidos: PP, P, M, G, GG, XG." << endl;
        }
    }


};


int main() {
    Roupa minhaRoupa;
    string input;

    cout << "Tamanho atual da roupa: \"" << minhaRoupa.getTamanho() << "\"" << std::endl;

    while (minhaRoupa.getTamanho().empty()) {
        cout << "Informe o tamanho da roupa (PP, P, M, G, GG, XG): ";
        cin >> input;
        minhaRoupa.setTamanho(input);
    }

    cout << "Tamanho final da roupa: " << minhaRoupa.getTamanho() << endl;

    return 0;
}