// uma parte

#include <iostream>
#include "fn.hpp"

using namespace std;

class Pessoa{
private:
    string nome="";
    int dinheiro=0;
public:
    Pessoa(string nome="", int dinheiro=0 ) : nome(nome) , dinheiro(dinheiro) {}

    int getDinheiro(){
        return dinheiro;
    }

    string getName(){
        return nome;
    }

    void descontar(int x){
    if(dinheiro < x){
        dinheiro = 0;
        } else 
        dinheiro -= x;
        }
    
    void addDinheiro(int x){
        dinheiro += x;
        
    }
    string str() {
        return fn::format("{}:{}", nome, dinheiro);
    }

};
class Moto{
private:
    int custo;
    Pessoa* motorista = nullptr;
    Pessoa* passageiro = nullptr;
public: 
    Moto() : custo(0), motorista(nullptr), passageiro(nullptr){}

    int getCusto(){
        return custo;
    }
    string dirigir(int distance){
        
        if(motorista == nullptr){
            return "ja possui motorista";
        } 
        if(passageiro == nullptr){
            return "motorista esta na moto";
        }
         custo += distance;    // Cada km percorrido aumenta o custo da corrida em 1 real.
         return "moto esta em movimento";
    }
        

    // Motorista e Passageiro 
    // são pessoas que tem nome e dinheiro.
    string setPass(Pessoa* person){
        if(motorista == nullptr){
            return "nao ha motorista";
        }
        passageiro = person;
        return "passageiro subiu";

    }
    
    
    string setDriver(Pessoa* person){
      if(this->motorista != nullptr){
                return "Falha: já existe motorista\n";
            }
            motorista = person;
            return "Motorista está na moto\n";
        }
    
    string Desembacar() {
        if(passageiro == nullptr){
                return "Falha, não há passageiro\n";
            }
            if (passageiro->getDinheiro() < custo) {
                cout << "fail: Passenger does not have enough money\n";
            }
            motorista->addDinheiro(custo);
            passageiro->descontar(custo);
            string mensagem = fn::format("{}:{} leave\n", passageiro->getName(), passageiro->getDinheiro());
            custo = 0;
            passageiro = nullptr;
            return mensagem;
        }


        string str() const {
            string impMotorista = motorista ? motorista->str() : "None";
            string impPassageiroStr = passageiro ? passageiro->str() : "None";
            return fn::format("Cost: {}, Driver: {}, Passenger: {}", custo, impMotorista, impPassageiroStr);
        }

};

class Adapter {
    Moto moto;
public:

    void setDriver(string name, int money) {
        (void) name;
        (void) money;
        // criar motorista
        Pessoa* person = new Pessoa(name, money);
        moto.setDriver(person);
    }   
    void setPass(string name, int money) {
        (void) name;    
        (void) money;
        // criar o passageiro
        Pessoa* person = new Pessoa(name, money);
        moto.setPass(person);

    }
    void drive(int distance) {
        (void) distance;
        moto.dirigir(distance);
    }
    void leavePass() {
        cout << moto.Desembacar();
    }
    void show() {
        cout << moto.str() << endl;
    }
};

int main() {
    Adapter adp;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")       { break;                                  }
        else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
        else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
        else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
        else if (args[0] == "leavePass") { adp.leavePass();                        }
        else if (args[0] == "show")      { adp.show();                             }
        else                             { fn::write("fail: command not found\n"); }
    }
}