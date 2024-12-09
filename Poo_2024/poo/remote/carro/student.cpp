#include "fn.hpp"

using namespace std;

struct Car
{

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

    void enter()
    {

        if (pass == passMax)
        {
            cout << "fail:" << " limite de pessoas atingido" << endl;
        }
        else if (pass < passMax)
        {
            pass++;
        }
    }

    // Parte 2: desembarcar
    // Crie o método `leave` que decrementa `pass`.
    // Crie um condicional para impedir que `pass` seja menor que 0.
    // Teste seu código.

    void leave()
    {
        if (pass > 0)
        {
            pass--;
        }
        else
            cout << "fail: nao ha ninguem no carro" << endl;
    }

    // Parte 3: abastecer
    // Crie o método `fuel` que incrementa `gas` com o valor passado.
    // Crie um condicional para impedir que `gas` ultrapasse `gasMax`.
    // Teste seu código.

    void fuel(int inc)
    {
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

    // Parte 4: dirigir
    // Crie o método `drive` que incrementa `km` e decrementa `gas` com o valor passado.
    // Crie testes para impedir que o carro dirija sem passageiros ou sem combustível.

    void drive(int distancia)
    {

        if (pass == 0)
        {
            cout << "fail: nao ha ninguem no carro" << endl;
        }
        else if (gas == 0)
        {
            cout << "fail: tanque vazio" << endl;
        }
        else if (distancia > gas)
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

struct Student
{

    Car car;
    Student(int pass = 0, int gas = 0, int km = 0)
    {
        car = Car(pass, 2, gas, 100, km);
    }

    void enter()
    {
        car.enter();
    }
    void leave()
    {
        car.leave();
    }
    void fuel(int x)
    {
        car.fuel(x);
    }
    void drive(int q)
    {
        car.drive(q);
    }
    void show()
    {
        cout << car.toString() << endl;
    }
};

struct Debug
{
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run()
    {
        std::cout << "Debug ativado" << std::endl;
    }
};
