#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <iomanip>
using namespace std;

// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

class Lead { // grafite
private:
    float thickness  ;
    string hardness;
    int size =0 ;

public:
    Lead(float thickness, string hardness, int size): thickness(thickness), hardness(hardness), size(size) {}

    float getThickness() {
        return thickness;
    }

    int getSize() {
        return size;
    }

    void usageSize(int newSize) {
        this->size = newSize;
    }

    int usagePerSheet() {
        if (hardness == "HB") {
            return 1;
        }
        if (hardness == "2B") {
            return 2;
        }
        if (hardness == "4B") {
            if(size>=14){
            return 4;
            }
            return 2;
        }
        if (hardness == "6B") {
            return 6;
        }
        return 0;
    }

    string toString()  {
        ostringstream oss;
        oss << fixed << setprecision(1) << thickness;
        return "[" + oss.str() + ":" + this->hardness + ":" + to_string(this->size) + "]";
    }
};

class Lapiseira{

private:

    float thickness =0 ; // calibre
    shared_ptr<Lead> bico{nullptr};
    list<shared_ptr<Lead>> tambor;


public:

    Lapiseira(float thickness =0): thickness(thickness){}

    void insert(shared_ptr<Lead> lead){
        if(this-> thickness != lead -> getThickness()){
            cout << "fail: calibre incompatível\n";
            return;
        }
        tambor.push_back(lead); // Adiciona ao tambor

    }
    void remove(){
        if ( this -> bico == nullptr){
            cout << "fail: nao existe grafite\n" ;
        }
        this -> bico = nullptr;
    }
    void pull(){
        if(this-> bico != nullptr){
            cout << "fail: ja existe grafite no bico\n";
            return;
        }
        // tambor estiver vazio 
        if(tambor.empty()){
            cout << "fail: tambor vazio\n" ;
            return;
        }

        // bico vai apontar para o primeiro elemento da lista 
        this -> bico = tambor.front();
        // vou remover o primeiro elemento da lista
        tambor.pop_front();
    }

    void whitePage() {
    if (this->bico == nullptr) {
        cout << "fail: nao existe grafite no bico\n";
        return;
    }

    int consumo = this->bico->usagePerSheet();
    
    // menos de 10mm, o grafite deve ser descartado
    if (this->bico->getSize() <= 10) {
        cout << "fail: folha incompleta\n";
    }
    

    if (this->bico->getSize() < consumo) {
        cout << "fail: folha incompleta\n";
        this->bico->usageSize(0);
        return;
    }


    this->bico->usageSize(this->bico->getSize() - consumo);
    
    }

    string str()  {
            stringstream oss;
            auto imp = [](auto x) {return x->toString();};
            oss << "calibre: " << fixed << setprecision(1) << this-> thickness << ", bico: " << (bico != nullptr ? bico->toString() : "[]")
            << ", tambor: <" << map_join(tambor, imp, "") << ">\n" ;
            return oss.str();
        }
};

int main() {

    Lapiseira lapiseira(0.5);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;  
        }
        else if (cmd == "show") { 
            cout << lapiseira.str() ;
        } 
        else if (cmd == "init") { 
             float calibre;
             ss >> calibre;
            lapiseira = Lapiseira(calibre);
        } 
        else if (cmd == "insert") { 
             float calibre;
             string dureza;
             int tamanho;
             ss >> calibre >> dureza >> tamanho;
            lapiseira.insert(make_shared<Lead> (calibre, dureza, tamanho));
        } 
        else if (cmd == "remove") { 
             lapiseira.remove() ;

        } 
        else if (cmd == "pull") { 
            lapiseira.pull() ;
        } 
        else if (cmd == "write") {
            
            lapiseira.whitePage();
            
        } 
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
