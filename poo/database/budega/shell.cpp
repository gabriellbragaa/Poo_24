#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
using namespace std;

// conseguir fazer só, como já havia usado vetor na atividade do junkfood, usei o codigo dela como base;


// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "") << f(*it);
    }
    return ss.str();
}




class Pessoa{

private:

    string nome;


public:

    Pessoa(string nome): nome(nome){}

    string getNome(){return nome; }

    void setNome(string nome){this-> nome = nome;}

    string str(){return this-> nome = nome;}

};

class Mercantil{

private:
    vector<  Pessoa* > caixas;
    list < Pessoa * > fila ; 

public:
    Mercantil(int numero_caixas = 0){
        for(int i =0 ; i < numero_caixas ; i++ ){
            caixas.push_back(nullptr);
        }
    }


    void giveUp (size_t index){ // finalizar
        if(index >= caixas.size()){
            cout <<  "fail: caixa inexistente" << endl ;
            return;
        }
        if(caixas[index] == nullptr){
            cout <<  "fail: caixa vazio" << endl ;
            return;
        }
        caixas[index] = nullptr;

    }
    
    void arrive(Pessoa* pessoa){ // chegar
        fila.push_back(pessoa);
    }

    void call(int index){ // chamar 
        if(caixas[index] != nullptr ){
            std::cout << "fail: caixa ocupado\n";
            return;
        }
        if(fila.size() == 0){
            std::cout << "fail: sem clientes\n";
            return;
        }
    
        caixas[index] = fila.front();
        // removendo pessoa da lista 
        fila.pop_front();
    }

    string toString(){
        std::stringstream ss;
        ss << "Caixas: [";
        int i = 0;
        for (auto elem : caixas) {
            ss << (i++ != 0 ? ", " : "");
            ss << (elem ? elem->str() : "-----");
        }
        ss << "]\nEspera: [";
        bool first = true;
        for (auto elem : fila) {
            ss << (!first ? ", " : "") << (elem ? elem->str() : "");
            first = false;
        }
        ss << "]";
        return ss.str();

    }
};


int main() {

    Mercantil mercantil(3);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") { 
            cout << mercantil.toString() << endl;
        } else if (cmd == "init") { 
            int qtd_caixas;
            ss >> qtd_caixas;
            mercantil = Mercantil(qtd_caixas);
        } else if (cmd == "arrive") { 
             string nome;
             ss >> nome;
             mercantil.arrive(new Pessoa (nome));
        } else if (cmd == "call") { 
            int indice;
            ss >> indice;
            mercantil.call(indice);
        } else if (cmd == "finish") { 
            int indice;
            ss >> indice;
            mercantil.giveUp(indice);
        } else {
            cout << "fail: comando invalido\n";
        }
    }
}
