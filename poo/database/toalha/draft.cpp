#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;

class Toalha{

    private:
    string cor;
    string T;
    int umi{0}; 

    public:
        Toalha(string cor = "",string T = "") : cor(cor), T(T), umi(0){}

    int getumiMaxima() {
        if(T == "P"){
            return  10;
        }
       if(T == "M"){
            return 20;
        }
        if(T == "G"){
            return 30;
        }
        return 0;
    }

    void enxugar(int umiRecebida){
        if(umi + umiRecebida > getumiMaxima()){
            umi = getumiMaxima();
            cout << "toalha enxarcada\n";
        }else{
            umi += umiRecebida;
        }
    }

    void torcer(){
        umi = 0;
    }

    bool estaSeca() {
       if (umi == 0) {
            cout << "True\n"; 
            return true;
        } else {
            cout << "False\n";
            return false;
        }
    }

    string toString(){
        return cor + " " + T + " " + to_string(umi);
    }

    void mostrar(){
        cout << toString() << "\n";
    }
};
int main() {
 
    Toalha toalha("Azul", "P");
    toalha.mostrar();
    toalha.enxugar(5);
    toalha.mostrar();
    toalha.estaSeca();
    toalha.enxugar(5);
    toalha.mostrar();
    toalha.enxugar(5);
    toalha.mostrar();
    toalha.torcer();
    toalha = Toalha("Verde", "G");
    toalha.estaSeca();
    toalha.enxugar(30);
    toalha.mostrar();
    toalha.estaSeca();

  
    toalha.enxugar(1);
    toalha.enxugar(30);
    toalha.mostrar();

    return 0;
}
