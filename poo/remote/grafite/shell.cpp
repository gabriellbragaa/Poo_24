#include "fn.hpp"
#include <iostream>

using namespace std;

class Grafite{
// atributo size
private:
    int size; // tamanho grafite
    double thickness; // espessura
    string hardness; // dureza
public: 
// cria o construtor 
// inicializacao

    Grafite(double thickness= 0.3, string hardness= "HB", int size=0) : size(size), thickness(thickness), hardness(hardness){}

int usagePerSheet(){
        if(hardness == "HB"){ return 1; 
        } else if(hardness == "2B"){ return 2;
        } else if(hardness == "4B"){ return 3;
        } else if(hardness == "6B"){ return 4;
        }

    }
// chama o get pq size, thickness e hardness sao privado
// chama o set 

int getSize(){
    return size;
}
void setSize(int size){
     this-> size = size;
}
double getThickness(){
    return thickness;
}
string getHardness(){
    return hardness;
}
void setThickness(double thickness) {
        this->thickness = thickness;
    }
void setHardness(string hardness) {
        this->hardness = hardness;
    }
string toString() {
        return "Grafite [Dureza: " + hardness + ", Tamanho: " + to_string(size) + "mm]";
    }
};


class Lapiseira{
private:
    Grafite* tip;
    double thickness;
public:

    // Construtor
    Lapiseira() : tip(nullptr){}

    // bool
    bool hasGrafite(){
        return tip != nullptr; // verificar se ha grafite
    }
    
    // implementar o metodo insert
    // bool
    bool insert(double thickness, string hardness, int size) {
    
    if (tip != nullptr) {
        cout << "fail: ja existe grafite" << endl;
        return false;
    }

    if (this->thickness != thickness) {
        cout << "fail: calibre incompativel" << endl;
        return false;
    }

    // ajuda do chat
    tip = new Grafite( thickness, hardness, size);
    cout << "Grafite inserido com sucesso." << endl;
    return true;
    }
    
    // lead | null
    Grafite* remove (){ 
        if (tip == nullptr){
            cout << "fail: nao existe grafite" << endl;
            return nullptr;
        }
        Grafite* remove = tip; 
        tip = nullptr;
        return remove;
        }
    
    // void
    void writePage() {
        if (!hasGrafite()) { // se nao ha 
            cout << "fail: nao existe grafite" << endl;
            return;
        }

        int consumo = tip->usagePerSheet();
        if (tip->getSize() < consumo) { 
            cout << "fail: tamanho insuficiente " << endl;
            tip->setSize(0); // Consome todo o grafite restante
        } else {
            tip->setSize(tip->getSize() - consumo);
            cout << "fail: folha incompleta" << tip->getSize() << "mm." << endl;
        }
    }

    // Mostra o estado atual da lapiseira
    string toString() const {
        if (hasGrafite()) {
            return "Lapiseira com " + tip->toString();
        } else {
            return "Lapiseira sem grafite.";
        }
    }
};
   
    

    // - Parte 2: Remover Grafite
    // Implemente o método `remove` que retira o grafite da lapiseira, se houver.
    // Verifique se o grafite foi removido corretamente.
   // Verifique se o método `remove` retorna o grafite removido ou `null` se não havia grafite.
    


class Adapter {
private:
    Lapiseira pencil;
public:
    Adapter(double thickness=0.3, string hardness="HB", int size=0) : pencil( thickness, hardness, size) {}
    
    void insert(double thickness, string hardness,int length ) {
        (void) thickness;
        (void) hardness;
        (void) length;
        pencil.insert(make_shared<Lead>(thickness, hardness, length ));
    }

    void remove() {
        pencil.remove();
    }

    void writePage() {
        pencil.writePage();
    }

    void show() {
        fn::write(pencil.toString());
    }
};


int main() {
    Adapter adp(0);

    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line);
        fn::write(line);

        if      (args[0] == "show"  ) { adp.show();                                    }
        else if (args[0] == "init"  ) { adp = Adapter(+args[1]);                       }
        else if (args[0] == "insert") { adp.insert(+args[1], args[2], (int) +args[3]); }
        else if (args[0] == "remove") { adp.remove();                                  }
        else if (args[0] == "write" ) { adp.writePage();                               }
        else if (args[0] == "end"   ) { break;                                         }
        else                          { fn::write("fail: comando invalido");           }
    }
}
