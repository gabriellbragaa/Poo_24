#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

using namespace std;


class Bateria {
private:
    int capacidade{0};
    int carga{0};

public:
    Bateria(int capacidade, int carga = 0) : capacidade(capacidade) {
        if (carga == 0) {
            carga = capacidade;
        }
        this->carga = carga;
    }

    int getCapacidade() {
        return capacidade;
    }

    int getCarga() {
        return carga;
    }

    void use(int minutos) {
        if (carga >= minutos) {
            carga -= minutos;
        } else {
            carga = 0;
        }
    }

    bool vazia() {
        return carga <= 0;
    }

    void carregarBateria(int minutos) {
        carga = min(capacidade, carga + minutos);
    }

    string str() {
        stringstream ss;
        ss << "(" << carga << "/" << capacidade << ")";
        return ss.str();
    }

    void ver() {
        cout << str() << endl;
    }
};

class Carregador {
private:
    int potencia{0};

public:
    Carregador(int potencia = 0) : potencia(potencia) {}

    int getPotencia() {
        return potencia;
    }

    void carregarBateria(shared_ptr<Bateria> bateria, int minutos) {
        if (bateria) {
            bateria->carregarBateria(minutos);
        }
    }

    string str() {
        stringstream ss;
        ss << potencia;
        return ss.str();
    }

    void ver() {
        cout << "(Potência " << str() << ")" << endl;
    }
};

class Notebook {
private:
    bool ligado = false;
    shared_ptr<Bateria> bateria;
    shared_ptr<Carregador> carregador;

public:
    Notebook() : ligado{false}, bateria(nullptr), carregador(nullptr) {}

    void setBateria(shared_ptr<Bateria> bat) {
        bateria = bat;
    }

    void setCarregador(shared_ptr<Carregador> ch) {
        carregador = ch;
    }

    void ligar() {
        if (ligado) {
            cout << "Notebook já está ligado.\n";
        } else if (!bateria || bateria->vazia()) {
            cout << "Não foi possível ligar\n";
        } else {
            ligado = true;
            cout << "Notebook ligado.\n";
        }
    }

    void desligar() {
        if (ligado) {
            cout << "Notebook desligado.\n";
            ligado = false;
        } else {
            cout << "Notebook está desligado.\n";
        }
    }

    void usar(int tempo) {
        if (!ligado) {
            cout << "Notebook desligado.\n";
            return;
        }

        if (!bateria || bateria->vazia()) {
            cout << "Notebook descarregou\n";
            desligar();
            return;
        }

        int uso = min(tempo, bateria->getCarga());
        bateria->use(uso);
        cout << "Usando por " << uso << " minutos.\n";

        if (bateria->vazia()) {
            cout << "Notebook descarregou\n";
            desligar();
        }
    }

    shared_ptr<Bateria> rmBateria() {
        if (!bateria) {
            cout << "Nenhuma bateria para remover.\n";
            return nullptr;
        }

        auto bateryRemove = bateria;
        bateria = nullptr;
        if (ligado) {
            desligar();
        }
        cout << "Bateria removida.\n";
        return bateryRemove;
    }

    void ver() {
        cout << "Status: " << (ligado ? "Ligado" : "Desligado");
        if (bateria) {
            cout << ", Bateria: " << bateria->str();
        } else {
            cout << ", Bateria: Nenhuma";
        }
        if (carregador) {
            cout << ", Carregador: (Potência " << carregador->str() << ")" << endl;
        } else {
            cout << ", Carregador: Desconectado\n";
        }
    }
};

int main() {
    Notebook notebook;
    notebook.ver();
    notebook.ligar();
    notebook.usar(10);

    auto bateria = make_shared<Bateria>(50); 
    bateria->ver();
    
    notebook.setBateria(bateria);
    notebook.ver();
    notebook.ligar();
    notebook.ver();
    notebook.usar(30);
    notebook.ver();
    notebook.usar(30);
    notebook.ver();
    
    auto bateryRemove = notebook.rmBateria();
    bateryRemove->ver();
    notebook.ver();

    auto carregador = make_shared<Carregador>(2);
    carregador->ver();

    notebook.setCarregador(carregador);
    notebook.ver();
    notebook.ligar();
    notebook.ver();
    notebook.setBateria(bateria);
    notebook.ver();
    notebook.usar(10);
    notebook.ver();

    return 0;
}