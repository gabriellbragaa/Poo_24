#pragma once
#include "fn.hpp"

using namespace std;

struct Animal
{
    string especie, barulho;
    int estagio = 0;

    Animal(string especie = "", string barulho = "")
    {
        this->especie = especie;
        this->barulho = barulho;
        this->estagio = 0;
    }

    void envelhecer(int nivel)
    {
        estagio += nivel;
        if (estagio >= 4)
        {
            estagio = 4;
            cout << "warning: " << especie << " morreu" << endl;
        } 
    }
    
    string fazerBarulho()
    {
        if (estagio == 0)
            return "---";
        if (estagio == 4)
            return "RIP";
        return barulho;
    }

    string str()
    {
        return especie + ":" + to_string(estagio) + ":" + barulho;
    }
};

struct Student
{
    Animal animal;

    void init(std::string especie = "", std::string barulho = "") {
        animal = Animal(especie, barulho);
    }

    void grow(int nivel)
    {
        animal.envelhecer(nivel);
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