#include "fn.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Pet {
private:
    int energyMax, hungryMax, cleanMax;
    int energy, hungry, clean;
    int diamonds = 0, age = 0;
    bool alive = true;

    void checkAlive() {
        if (energy == 0 || hungry == 0 || clean == 0)
            alive = false;
    }

public:
    Pet(int energy, int hungry, int clean)
        : energyMax(energy), hungryMax(hungry), cleanMax(clean),
          energy(energy), hungry(hungry), clean(clean) {}

    bool isAlive() const {
        return alive;
    }

    void setEnergy(int value) {
        energy = max(0, min(energyMax, value));
        checkAlive();
    }

    void setHungry(int value) {
        hungry = max(0, min(hungryMax, value));
        checkAlive();
    }

    void setClean(int value) {
        clean = max(0, min(cleanMax, value));
        checkAlive();
    }

    void addDiamonds() {
        diamonds++;
    }

    void addAge(int value) {
        age += value;
    }

    int getEnergy() const { return energy; }
    int getHungry() const { return hungry; }
    int getClean() const { return clean; }
    int getDiamonds() const { return diamonds; }
    int getAge() const { return age; }
    int getEnergyMax() const { return energyMax; }

    string to_string() const {
        ostringstream oss;
        oss << "E:" << energy << "/" << energyMax
            << ", S:" << hungry << "/" << hungryMax
            << ", L:" << clean << "/" << cleanMax
            << ", D:" << diamonds
            << ", I:" << age;
        return oss.str();
    }
};

class Game {
private:
    Pet* pet = nullptr;

    bool testAlive() const {
        if (!pet->isAlive()) {
            cout << "fail: pet esta morto\n";
            return false;
        }
        return true;
    }

public:
    Game(int energy, int hungry, int clean)
        : pet(new Pet(energy, hungry, clean)) {}

    ~Game() {
        delete pet;
    }

    void play() {
        if (!testAlive()) return;

        pet->setEnergy(pet->getEnergy() - 2);
        pet->setHungry(pet->getHungry() - 1);
        pet->setClean(pet->getClean() - 3);
        pet->addAge(1);
        pet->addDiamonds();
    }

    void eat() {
        if (!testAlive()) return;

        pet->setEnergy(pet->getEnergy() - 1);
        pet->setHungry(pet->getHungry() + 4);
        pet->setClean(pet->getClean() - 2);
        pet->addAge(1);
    }

    void sleep() {
        if (!testAlive()) return;

        int energyNeeded = pet->getEnergyMax() - pet->getEnergy();
        if (energyNeeded < 5) {
            cout << "fail: nao esta com sono\n";
            return;
        }

        pet->setEnergy(pet->getEnergyMax());
        pet->setHungry(pet->getHungry() - 1);
        pet->addAge(energyNeeded);
    }

    void shower() {
        if (!testAlive()) return;

        pet->setEnergy(pet->getEnergy() - 3);
        pet->setHungry(pet->getHungry() - 1);
        pet->addAge(2);
    }

    string to_string() const {
        return pet->to_string();
    }
};

class Adapter {
private:
    Game* game = nullptr;

public:
    Adapter(int energy, int hungry, int clean) {
        game = new Game(energy, hungry, clean);
    }

    ~Adapter() {
        delete game;
    }

    void show() {
        cout << game->to_string() << endl;
    }

    void play() {
        game->play();
    }

    void shower() {
        game->shower();
    }

    void eat() {
        game->eat();
    }

    void sleep() {
        game->sleep();
    }
};

