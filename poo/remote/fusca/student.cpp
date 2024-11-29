#include "fn.hpp"

using namespace std;

struct Car{
    int pass, passMax, gas, gasMax;
    int km;

    Car(int pass = 0, int passMax = 2, int gas = 0, int gasMax = 100, int km = 0)
    {
        this->pass = pass;
        this->passMax = passMax;
        this->gas = gas;
        this->gasMax = gasMax;
        this->km = km;
    }
void enter(){
     void enter() {
        if (pass < passMax) {
            pass++;
            cout << "Um passageiro entrou no carro." << endl;
        } else {
            cout << "fail: limite de pessoas atingido" << endl;
        }
    }
void leave(){
    if(pass == 0){
        cout << "fail: nao ha ninguem no carro." << endl ; 
    } else {
        pass--;
           
    }
}
void fuel(int inc){
     gas += inc;
        if (gas > gasMax)
        {
            gas = gasMax;
        }
        else
        {
            return;
        }
    }

void drive(int distancia){

        if (distancia > gas)
        {

            km += gas;
            cout << "fail: tanque vazio apos andar " << gas << " km" << endl;
            gas = 0;
        }
        else
        {
            km += distancia;
            gas -= distancia;
        }
    }
    string toString()
    {
        return "pass: " + to_string(pass) + ", gas: " + to_string(gas) + ", km: " + to_string(km);
    }

};
struct Student {

    Car car;
    Student(int pass = 0, int gas = 0, int km = 0)
    {
        car = Car(pass, 2, gas, 100, km);
    }

    void enter() {
        car.enter();
    }

    void leave() {
        car.leave();
    }

    void fuel(int q) {
        car.fuel(q);
    }

    void drive(int q) {
        car.drive(q);
    }

    void show() {
        cout << car.toString() << endl;
    }
};

struct Debug {
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run() {
        std::cout << "Debug ativado" << std::endl;
    }
};