#include <iostream>

using namespace std;

class Chinela {
private:
    int tamanho;

public:
    // Construtor
    Chinela() : tamanho(0) {}

    // chama o set de tamanho
    void setTamanho(int T) {
        
        if (T <= 20 || T >= 50) {
            cout << "tamanho deve estar entre 20 e 50 " << endl;
        } else if (T % 2 != 0) {
            cout << "tamanho deve ser par" << endl;
        } else {
            tamanho = T;
            cout << "Tamanho da chinela: " << tamanho << endl;
        }
    }

    // chama o get
    int getTamanho() {
        return tamanho;
    }
};

int main() {
    Chinela chinela; // Cria o objeto 
    int input;  

    // Loop
    while (chinela.getTamanho() == 0) {
        cout << "Informe o tamanho da chinela, um número par entre 20 e 50): " << endl;
        cin >> input;
        chinela.setTamanho(input);  // Valida o tamanho
    }

    
    cout << "Tamanho da chinela: " << chinela.getTamanho() << endl;

    return 0;
}
