#include "fn.hpp"
#include <memory>  // Para usar shared_ptr e make_shared
#include <iostream> 

using namespace std;

class Towel {
private:
    string size;  
public:
    Towel() {
        this->size = "";  
    }

    string getSize() {
        return this->size; 
        
    }

    void setSize(string newSize) {
       
        if (newSize == "PP" || newSize == "P" || newSize == "M" || newSize == "GG" ||
            newSize == "XG") {
            this->size = newSize; 
            
        } else {
            cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG\n"; 
            
        }
    }
};

class Adapter {
private:
    shared_ptr<Towel> towel;  
    

public:
    Adapter() {
        this->towel = make_shared<Towel>();  
        
    }

    void size ( string& size) {
        this->towel->setSize(size);  
        
    }

    void show() {
        
        
        cout << "size: (" << this->towel->getSize() << ")\n";
    }
};

int main() {
    Adapter adapter;  

    while (true) {
        fn::write("$", "");  
        auto line = fn::input();  
        auto args = fn::split(line, ' ');  

        fn::write(line);  

        // Processa os comandos
        if (args[0] == "end") {
            break;  
        } else if (args[0] == "size") {
            adapter.size(args[1]);  
        } else if (args[0] == "show") {
            adapter.show();  
        } else {
            fn::write("Comando inválido");  
        }
    }

    return 0;
}
