#pragma once
#include "fn.hpp"

using namespace std;

struct Animal
{
    string especie, barulho;
    int idade = 0;

    Animal(string especie = "", string barulho = "")
    {
        this->especie = especie;
        this->barulho = barulho;
        this->idade = 0;
    }

    void velho(int nivel)
    {
        idade += nivel;
        if (idade >= 4)
        {
            idade = 4;
            cout << "warning: " << especie << " morreu" << endl;
        }
    }

    string fazerBarulho()
    {
        if (idade == 0)
            return "---";
        if (idade == 4)
            return "RIP";
        return barulho;
    }

    string str()
    {
        return especie + ":" + to_string(idade) + ":" + barulho;
    }
};

struct Student
{
    Animal animal;

    Student(string especie = "", string barulho = "")
    {
        animal = Animal(especie, barulho);
    }

    void grow(int nivel)
    {
        animal.velho(nivel);
    }

    void noise()
    {
        cout << animal.fazerBarulho() << endl;
    }

    void show()
    {
        cout << animal.str() << endl;
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