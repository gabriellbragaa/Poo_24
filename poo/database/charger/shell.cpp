#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
using namespace std;

class Carregador{
    private:
        int potencia{0};
    public:
        Carregador(int potencia = 0) : potencia(potencia){}

        int getPotencia() {
            return this->potencia;
        }

        void setPotencia(int novaPotencia) {
            this->potencia = novaPotencia;
        }

        string str() {
            stringstream ss;
            ss << "Carregador " << this->getPotencia() << "W";
            return ss.str();
        }
};

class Bateria{
    private:
        int capacidade{0};
        int carga{0};
    public: 
        Bateria(int capacidade = 0, int carga = 0) : capacidade(capacidade){
            if (carga == 0) {
                carga = capacidade;
            }
            this->carga = carga;}

        int getCapacidade() {
            return this->capacidade;
        }

        int getCarga() {
            return this->carga;
        }

        void setCarga(int newCarga){
            this->carga = newCarga;
            if(this->carga > this->capacidade){
                this->carga = this->capacidade;
            }
        }


        string str() {
            stringstream ss;
            ss << this->carga << "/" << this->capacidade;
            return ss.str();
        }
};

class Notebook{
    private:
        bool ligado;
        shared_ptr<Bateria> bateria;
        shared_ptr<Carregador> carregador;
        int tempo{0};
    public:
        Notebook(){
            this->bateria = nullptr;
            this-> carregador  = nullptr;
            this->ligado = false;
            this->tempo = 0;
        }

        void setCarregador(shared_ptr<Carregador> novoCarregador){
            if(this->carregador == nullptr){
                this->carregador = novoCarregador;
                }else{
                    cout << "fail: carregador já conectado\n";
                }
        }

        void removeCarregador(){
            if(this->carregador != nullptr){
                cout << "Removido " << this->carregador->getPotencia() << "W" <<endl;
                this->carregador = nullptr;
                this->ligado = false;
            }else{
                cout << "fail: Sem carregador\n";
            }
        }

        void setBateria(shared_ptr<Bateria> novaBateria){
            if(this->bateria == nullptr){
            this->bateria = novaBateria;
            }else{
                cout << "fail: já existe bateria\n";
            }
        }

        void removeBateria(){
            if(this->bateria != nullptr){
                cout << "Removido " << this->bateria->getCarga() << "/" << this->bateria->getCapacidade() <<
                endl;
                this->bateria = nullptr;
                if(this->carregador == nullptr){
                this->ligado = false;
                }
            }else{
                cout << "fail: Sem bateria\n";
            }
        }

        void ligar(){
            if(this->bateria != nullptr || this->carregador != nullptr){
                this->ligado = true;
            }else{
            this->ligado = false;
            cout << "fail: não foi possível ligar\n";
            }
        }

        void desligar(){
            this->ligado = false;
        }

        void usar(int tempo){
            this->tempo += tempo;
            if(this->ligado == false){
                cout << "fail: desligado\n";
            }
            if(this->bateria != nullptr && this->carregador == nullptr){
                if(this->bateria->getCarga() <= tempo){
                    cout << "fail: descarregou\n";
                    this->bateria->setCarga(0);
                    this->ligado = false;
                }else{
                    this->bateria->setCarga(this->bateria->getCarga() - tempo);
                    if(this->bateria->getCarga() < 0){
                        this->bateria->setCarga(0);
                    }
                }  
            }
            if(this->bateria != nullptr && this->carregador != nullptr){
                this->bateria->setCarga(this->bateria->getCarga() + (this->carregador->getPotencia() * tempo));
                
            }
        }

        void show(){
            if(ligado == false && this->bateria == nullptr && this->carregador == nullptr){
            cout << "Notebook: desligado\n";
            }
            if(ligado == false && this->bateria != nullptr && this->carregador != nullptr){
            cout << "Notebook: desligado,Bateria " << this->bateria << ", " << 
            this->carregador->str() << endl;
            }
            if(ligado == false && this->bateria != nullptr && this->carregador == nullptr){
            cout << "Notebook: desligado, Bateria " << this->bateria->str() << endl;
            }
            if(ligado == false && this->bateria == nullptr && this->carregador != nullptr){
            cout << "Notebook: desligado, " << this->carregador->str() << endl;
            }
            if(ligado == true && this->bateria == nullptr && this->carregador == nullptr){
            cout << "Notebook: ligado\n";
            }
            if(ligado == true && this->bateria != nullptr && this->carregador != nullptr){
            cout << "Notebook: ligado por " << this->tempo << " min, Carregador "<< this->carregador->getPotencia() 
            << "W, Bateria " << this->bateria->str() <<endl;
            }
            if(ligado == true && this->bateria != nullptr && this->carregador == nullptr){
            cout << "Notebook: ligado por " << this->tempo << " min, Bateria " << this->bateria->str() << endl;
            }
            if(ligado == true && this->bateria == nullptr && this->carregador != nullptr){
            cout << "Notebook: ligado por " << this->tempo << " min, " << this->carregador->str() << endl;
            }
        }

};

int main() {
    Notebook notebook;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "show") { notebook.show();
        } else if (cmd == "turn_on") { notebook.ligar();
        } else if (cmd == "turn_off") { notebook.desligar();
        } else if (cmd == "use") { 
            int tempo;
            ss >> tempo;
            notebook.usar(tempo) ;
        } else if (cmd == "set_charger") {
            int potencia;
            ss >> potencia;
            auto carregador = make_shared<Carregador>(potencia);
            notebook.setCarregador(carregador);
        } else if (cmd == "rm_charger") {
            notebook.removeCarregador();
        } else if (cmd == "set_battery") {
            int capacidade;
            ss >> capacidade;
            auto bateria = make_shared<Bateria>(capacidade);
            notebook.setBateria(bateria);
        } else if (cmd == "rm_battery") {
            notebook.removeBateria();
        } else if (cmd == "end") {
            break;
        } else {
            cout << "fail: comando inválido\n";
        }
    }    
}