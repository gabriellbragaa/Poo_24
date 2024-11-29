#include "fn.hpp"
#include <iostream>

using namespace std;

class Lapiseira{
// atributo size
private:
    int size; // tamanho grafite
    double thickness; // espessura
    string hardness; // dureza
public: 
// cria o construtor 
// inicializacao

    Lapiseira(double thickness, string hardness, int size) : size(size), thickness(thickness), hardness(hardness){}

int usagePerSheet(){
        if(hardness == "HB"){ return 1; 
        } else if(hardness == "2B"){ return 2;
        } else if(hardness == "4B"){ return 3;
        } else if(hardness == "6B"){ return 4;
        } return 0;

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
        ostringstream oss;
        oss << fixed << setprecision(1) << this->thickness;
        return "[" + oss.str() + ":" + this->hardness + ":" + to_string(this->size) + "]";
    }

};


class Grafite{
private:
    Lapiseira* tip;
    double thickness;
public:

    // Construtor
    Grafite(double thickness) : thickness(thickness){}

    // bool
    bool hasGrafite(){
        if(tip == nullptr){ // verificar se ha grafite
        return false;
    }
    return true;
}
    
    // implementar o metodo insert
    // bool
    void insert(double thickness, const std::string& hardness, int size) {
        if (this->tip != nullptr) {
            std::cout << "fail: ja existe grafite" << std::endl;
            return;
        }

        if (this->thickness != thickness) {
            std::cout << "fail: calibre incompativel" << std::endl;
            return;
        }

        this->tip = new Lapiseira(thickness, hardness, size);
        std::cout << "Grafite inserido com sucesso." << std::endl;
    }

    Lapiseira* remove() {
        if (tip == nullptr) {
            cout << "fail: nao existe grafite" << endl;
            return nullptr;
        }

        Lapiseira* removed = tip;
        tip = nullptr;
        delete removed; // Libera a memória alocada
        return removed;
    }
    // void
    void writePage() {
        if (this->tip == nullptr) {
            fn::write("fail: nao existe grafite");
            return;
        }

        if (this->tip->getSize() <= 10) {
            fn::write("fail: tamanho insuficiente");
            return;
        }

        int usage = this->tip->usagePerSheet();
        if (this->tip->getSize() < usage + 10) {
            fn::write("fail: folha incompleta");
            this->tip->setSize(10);
            return;
        }

        this->tip->setSize(this->tip->getSize() - usage);
    }
        

    // Mostra o estado atual da lapiseira
    string toString()  {
        std::string leadInfo = "null";
        if (this->tip != nullptr) {
            leadInfo = this->tip->toString();
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << this->thickness;
        return "calibre: " + oss.str() + ", grafite: " + leadInfo;
    }
};

   
    

    // - Parte 2: Remover Grafite
    // Implemente o método `remove` que retira o grafite da lapiseira, se houver.
    // Verifique se o grafite foi removido corretamente.
   // Verifique se o método `remove` retorna o grafite removido ou `null` se não havia grafite.
    


class Adapter {
private:
    Grafite pencil;
public:
    Adapter(double thickness) : pencil( thickness) {}
    
    void insert(double thickness, string hardness,int length ) {
        pencil.insert(thickness, hardness, length );
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
