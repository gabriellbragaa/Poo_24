#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

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

    void usarCarga(int minutos) {
        if (carga >= minutos) {
            carga -= minutos;
        } else {
            carga = 0;
        }
    }

    bool estaVazia() {
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

    void mostrar() {
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

    void carregarBateria(Bateria* bateria, int minutos) {
        if (bateria) {
            bateria->carregarBateria(minutos);
        }
    }

    string str() {
        stringstream ss;
        ss << potencia;
        return ss.str();
    }

    void mostrar() {
        cout << "(Potência " << str() << ")" << endl;
    }
};

class Notebook {
private:
    bool ligado = false;
    Bateria* bateria;
    Carregador* carregador;

public:
    Notebook() : ligado{false}, bateria(nullptr), carregador(nullptr) {}

    void setBateria(Bateria* bat) {
        bateria = bat;
    }

    void setCarregador(Carregador* ch) {
        carregador = ch;
    }

    void ligar() {
        if (ligado) {
            cout << "Notebook já está ligado.\n";
        } else if (!bateria || bateria->estaVazia()) {
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
            cout << "Notebook já está desligado.\n";
        }
    }

    void usar(int tempo) {
        if (!ligado) {
            cout << "Notebook desligado.\n";
            return;
        }

        if (!bateria || bateria->estaVazia()) {
            cout << "Notebook descarregou e foi desligado.\n";
            desligar();
            return;
        }

        int usoReal = min(tempo, bateria->getCarga());
        bateria->usarCarga(usoReal);
        cout << "Usando por " << usoReal << " minutos.\n";

        if (bateria->estaVazia()) {
            cout << "Notebook descarregou e foi desligado.\n";
            desligar();
        }
    }

    Bateria* rmBateria() {
        if (!bateria) {
            cout << "Nenhuma bateria para remover.\n";
            return nullptr;
        }

        auto removedBattery = bateria;
        bateria = nullptr;
        if (ligado) {
            desligar();
        }
        cout << "Bateria removida.\n";
        return removedBattery;
    }

    void mostrar() {
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
    notebook.mostrar();
    notebook.ligar();
    notebook.usar(10);

    auto bateria = make_shared<Bateria>(50); 
    bateria->mostrar();
    
    notebook.setBateria(bateria);
    notebook.mostrar();
    notebook.ligar();
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    
    auto removedBattery = notebook.rmBateria();
    removedBattery->mostrar();
    notebook.mostrar();

    auto carregador = make_shared<Carregador>(2);
    carregador->mostrar();

    notebook.setCarregador(carregador);
    notebook.mostrar();
    notebook.ligar();
    notebook.mostrar();
    notebook.setBateria(bateria);
    notebook.mostrar();
    notebook.usar(10);
    notebook.mostrar();

    return 0;
}