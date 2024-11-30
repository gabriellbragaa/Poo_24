#pragma once
#include <iostream>
#include <string>

 /*Classe Pessoa
  - Crie a classe `Pessoa` com os atributos `age` e `name`.
  - Defina os atributos como privados.
  - Crie o construtor da classe que recebe `name` como uma string e `age` como um número.
  - Crie os métodos `getAge()` e `getName()` para retornar a idade e o nome da pessoa, respectivamente.
  - Crie o método `toString()` para retornar uma string no formato "nome:idade".
    Parte 1: Inserir
    */
using namespace std;

class Pessoa{
private:
    int age;
    string name;

public: 

    Pessoa(string name, int age ) : age(age), name(name){}

// chama o get 

    int getAge(){
        return age;
    }
    string getName(){
        return name;
    }

    string toString() const {
        return name + ":" + to_string(age);
    }

};

/*- Crie a classe `Motoca` com os atributos `potencia`, `time` e `pessoa`.
  - Inicialize os atributos no construtor, 
  onde `potencia` inicia com 1, `time` inicia com 0 e `pessoa` inicia como nulo.*/

class Motoca{
private:
    int potencia=1;
    int time=0;
    Pessoa* pessoa= nullptr; 
public:
    // criar o construtor
    Motoca(int potencia=1, int time=0) : potencia(potencia), time(time){}

/*Crie o método `inserir(pessoa: Pessoa): bool` que permite inserir uma pessoa na motoca.
  - Verifique se há uma pessoa na motoca. Se houver, imprima "fail: busy motorcycle" e retorne falso.
  - Caso contrário, insira a pessoa na motoca e retorne verdadeiro.
  - Crie o método `toString()` para mostrar o estado da motoca.*/
    
    bool inserir(Pessoa* p) {
        if (pessoa != nullptr) {
            cout << "fail: busy motorcycle" << endl;
            return false;
        }
        pessoa = p;
        return true;
    }
    Pessoa* remover() {
        if (pessoa == nullptr) {
            cout << "fail: empty motorcycle" << endl;
            return nullptr;
        }
        Pessoa* p = pessoa;
        pessoa = nullptr;
        return p;
    }
     /* Crie o método `buyTime(time: number)` que permite comprar 
     tempo em minutos para utilizar a motoca. */
    void buyTime(int t) {
        time += t;
        
    }

    // Método para dirigir a motoca
    void drive(int t) {
        if (time <= 0) {
            cout << "fail: buy time first" << endl;
            return;
        }

        if (pessoa == nullptr) {
            cout << "fail: empty motorcycle" << endl;
            return;
        }

        if (pessoa->getAge() > 10) {
            cout << "fail: too old to drive" << endl;
            return;
        }

        if (time - t <= 0) {
            cout << "fail: time finished after " << time << " minutes" << endl;
            time = 0;
            return;
        }

        time -= t;
       
    }

    /*Parte 5: Buzinar
  - Crie o método `honk()` que permite buzinar a motoca.
  - Construa a string da buzina, onde o número de "e" é igual à potência da motoca.
  - Retorne a buzina.*/
    string honk() {
        string buzina = "P";
        for (int i = 0; i < potencia; ++i) {
            buzina += "e"; // nde o número de "e" é igual à potência da motoca.
        }
        return buzina + "m";
    }

    string toString()  {
        string estado = "power:" + to_string(potencia) + ", time:" + to_string(time) ;
        if (pessoa != nullptr) {
            estado +=  ", person:(" + pessoa->toString() + ")";
        } else {
            estado += ", person:(empty)";
        }
        return estado;
    }

};

class Adapter {
     Motoca motoca;
public:

    void init(int power ) {
        (void) power;
        motoca = Motoca(power);
    }

    void enter(string name, int age) {
        (void) name;
        (void) age;
        Pessoa* person = new Pessoa(name, age);
        motoca.inserir(person);
    }

    void leave() {
        auto person = motoca.remover();
        fn::write(person == nullptr ? "---" : person->toString());
    }

    void honk()  {
        fn::write(motoca.honk());
    }

    void buy(int time) {
        (void) time;
        motoca.buyTime(time);
    }

    void drive(int time) {
        (void) time;
        motoca.drive(time);
    }

    void show() {
        fn::write(motoca.toString());
    }
};