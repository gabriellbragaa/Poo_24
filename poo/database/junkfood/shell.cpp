#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;


// Havia chegado um pouco atrasado na aula, e havia conseguido passa apenas um teste. Peguei pontos do codigo que o senhor havia enviado na aula 

template<typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim);
        ss << func(*it);
    }
    return ss.str();
}
class Espiral{
    private:
    
    string nome;
    int quantidade;
    double preco;

    public:

    Espiral(string nome="empty", int quantidade=0, double preco=0.0) : nome(nome) , quantidade(quantidade), preco(preco) {}

    string getNome(){
        return nome;
    }
    int getQuantidade(){
        return quantidade;
    }
    double getPreco(){
        return preco;
    }

    // chama set
    
    void setNome(){
        this->nome = nome;
    }
    void setQuantidade(int quantidade){
        this-> quantidade = quantidade;
    }
    void setPreco(){
        this-> preco = preco;
    }
    string str() {
       stringstream ss;
        ss << "[" 
           << setw(8) << setfill(' ') << nome 
           << " : " << quantidade << " U : " 
           << fixed << setprecision(2) << preco
           << " RS]";
        return ss.str();
    }
};

class Maquina{
private: 
    vector<Espiral> espirais; 

    double saldo;
    double lucro;
    
public: 
    
    Maquina(int size_espirais) : saldo(0), lucro(0) {
        espirais.resize(size_espirais);  }

    
     void setEspiral(int indice, string nome, int quantidade, double preco) {
        if (indice < 0 || indice >= (int) espirais.size()) {
            cout << "fail: indice nao existe" << '\n';
            return;
        }
        espirais[indice] = Espiral(nome, quantidade, preco);
    }



    void addDinheiro(double valor){
        saldo += valor;
    }

    void limpar(size_t indice) {
        if (indice >= espirais.size()) {
            cout << "fail: indice nao existe" << '\n';
            return;
        }
        espirais[indice] = Espiral("empty", 0, 0);
    }
    double pegarTroco() {
        double troco = saldo;
        saldo = 0.00;
        return troco;
    }
    void comprar(int indice) {
    
        if (indice < 0 || indice >= (int) espirais.size()) {
            cout << "fail: indice nao existe" << '\n';
            return;
        }
        
        Espiral& espiral = espirais[indice]; // referencia ao indice
        
        
        if (espiral.getQuantidade() <= 0) {
            cout << "fail: espiral sem produtos" << '\n';
            return;
        }
        if (espiral.getPreco() > saldo) {
            cout << "fail: saldo insuficiente" << '\n';
            return;
        }
        int auxQuantidade=0;
        this->saldo -= espiral.getPreco();
        this->lucro += espiral.getPreco();
        auxQuantidade = espiral.getQuantidade() - 1;
        espiral.setQuantidade(auxQuantidade);
        

        cout << "voce comprou um " << espiral.getNome() << endl;
     }
      string str() {
        stringstream ss;
        ss << "saldo: " << fixed << setprecision(2) << saldo << endl;
        for (size_t i = 0; i < espirais.size(); i++) {
            ss << i << " " << espirais[i].str() << endl;
        }
        string saida = ss.str();
        saida.pop_back();
        return saida;
    }

};
int main() {
    Maquina maquina(5);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        try {
            if (cmd == "show") {
                 cout << maquina.str() << '\n';
            } else if (cmd == "init") {
                 int n_espirais {};
                 ss >> n_espirais;
                 maquina = Maquina(3);
            } else if (cmd == "limpar") {
                 int indice {};
                 ss >> indice;
                 maquina.limpar(indice);
            } else if (cmd == "dinheiro") {
                 int value {};
                 ss >> value;
                 maquina.addDinheiro(value);
            } else if (cmd == "comprar") {
                 int index {};
                 ss >> index;
                 maquina.comprar(index);
            } else if (cmd == "set") {
                 int index {};
                 string name;
                 int qtd {};
                 double price {};
                 ss >> index >> name >> qtd >> price;
                 maquina.setEspiral(index, name, qtd, price);
            } else if (cmd == "troco") {
                 cout << "voce recebeu " << fixed << setprecision(2) << maquina.pegarTroco() << " RS" << '\n';
            } else if (cmd == "end") {
                break;
            } else {
                cout << "comando invalido" << endl;
            }
        } catch (const char* e) {
            cout << e << endl;
        }
    }
}
