#pragma once
#include "fn.hpp"

using namespace std;


struct Calculator{
    int Battery, BatteryMax;
    float display;

    Calculator(int Battery, int BatteryMax, float display = 0.0){
        this -> Battery = Battery;
        this -> BatteryMax = BatteryMax;
        this -> display = display;
    }
    // Parte 2
    // Crie o método charge. Tente adicionar carga à bateria.
    // Verifique se ele adiciona além do limite.
    int charge (int value){
        Battery += value; // charge 1
        if(Battery > BatteryMax){
            Battery = BatteryMax;
        }
        return Battery; 

    }
    // Crie o método para somar.
    //  Verifique se a soma é guardada no display ao invés de impressa diretamente.
    //   Imprima a mensagem de erro adequada se não houver bateria.
    //  Lembre de gastar bateria.
    int sum (int a, int b){
       if ( Battery <= 0){
        cout << "fail: bateria insuficiente" << endl;
       }
      
       display = abs(a) + abs(b);
       Battery--;
       return display;
    }
    // Crie o método para dividir.
    // Verifique se existe bateria, se existir gaste, se não, emita o erro.
    // Verifique se a divisão é possível, se não for, emita o erro e retorne.
    // Guarde o resultado no display.
    int division (int num, int den){
        if (Battery < 0 && Battery == 0  ){
            cout << "fail: bateria insuficiente" << endl;
        } 
        if (den == 0){
         cout << "fail: divisão por zero" << endl;
        }
        Battery--;
        display = (num) / den ;
        return display;

    }
    


    string toString()
    {
        return fn::format("display = {%.2f}, battery = {}", this->display, this->Battery); 
    }


};
class Student {
     Calculator c;
    public: 
    Student(int Battery, int BatteryMax, float display=0.0): c(Battery,BatteryMax,display=0.0) {} // peguei no chat
  /*  {
        c = Calculator(Battery,BatteryMax,display=0.0);
    }
    */
    void show() {
         cout << c.toString() << endl;
    }
    void init(int batteryMax) {
        (void) batteryMax;
         c = Calculator(0, batteryMax, 0.0);
    }
    void charge(int value) {
        (void) value;
        
         c.charge(value);
    }
    void sum(int a, int b) {
        (void) a;
        (void) b;
        c.sum(a, b);
    }
    void div(int num, int den) {
        (void) num;
        (void) den;
        c.division(num, den);
    }
};
