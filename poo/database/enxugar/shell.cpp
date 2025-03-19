#include <iostream>
#include <sstream>

using namespace std;

// classe Toalha `Towel` com os atributos cor `color`, tamanho `size` e umidade `wetness`.
class Towel{
    private:
        string cor;
        string size;
        int wetness=0; // umidade
    public:
        Towel(string cor = "", string size = "" ){
            this->cor = cor;
            this->size = size;
            this->wetness = 0; 
        }
        // chama os get
        string getCor(){
            return this->cor;
        }

        string getSize(){
            return this->size;
        }
        // chama os set
        void setWetness(int newWetness){
            this->wetness = newWetness;
        }
        
        void setSize(string newSize){
            this->size = newSize;
        }
        int getWetness(){
            return wetness;
        }
        
        void setCor(string novaCor){
            this->cor = novaCor;
        }

        

        
        // método enxugar `dry` que recebe um valor inteiro quantidade `amout` e AUMENTA o atributo umidade da toalha.
        void dry(int amout){
            setWetness(this->wetness += amout);
        }
        // método torcer `wringOut` que zera o atributo umidade da towel.
        void wringOut(){
            setWetness(this->wetness = 0);
        }
        // método toalhaa pegar máximo de umidade `getMaxWetness` que retorna o valor máximo de umidade que essa toalha pode ter.
        int getMaxWetness(){
            if(getSize() == "P"){
                return 10;
            }
            if(getSize() == "M"){
                return 20;
            }
            if(getSize() == "G"){
                return 30;
            }
            return 0;
        }
        // método que retorna se a toalha esta seca `isDry`, que retorna `true` se a umidade da toalha for 0 e `false` caso contrário.
        bool isDry(){
            if(getWetness() == 0){
                return true;
            }
            return false;
        }

        void toalha(int enxugar){
            setWetness(this->wetness += enxugar);
            if(getWetness() >= getMaxWetness()){ 
                setWetness(getMaxWetness());
                cout << "toalha encharcada\n" ;
            }
        }

        string str() {
            ostringstream oss;
            oss << "Cor: " << this->getCor()
            << ", Tamanho: " << this->getSize()
            << ", Umidade: " << this->getWetness();
            return oss.str();
        }

        void creatingTowel(){
            cout << "$criar " << this->getCor() << " " << this->getSize() << endl;
        }
        void show(){
            cout << "$mostrar\n" << str() << endl;
        }

        void end() {
            cout << "$end\n";
        }

        void seca() {
            cout << "$seca\n";
        }

        void enxugar(int value){
            cout << "$enxugar" << " " << value << endl;
        }

        void torcer(){
            cout << "$torcer" << endl;
        }
};

int main() {
    Towel towel;
    while (true) {
        string line, aux;
        getline(cin, line);

        stringstream toalha(line);
        toalha >> aux;

        if (aux == "mostrar") { towel.show();
        } else if (aux == "criar") { 
            string cor, size;
            toalha >> cor >> size;
            towel.setCor(cor);
            towel.setSize(size);
            towel.creatingTowel();
        } else if (aux == "enxugar") { 
            int umidade {};
            toalha >> umidade;
            towel.enxugar(umidade);
            towel.toalha(umidade);
        } else if (aux == "torcer") {
        towel.torcer();
        towel.wringOut(); // zera atributo umidade
        } else if (aux == "seca") { towel.seca();
            if(towel.isDry() == true){ 
                cout << "sim\n";
            }
            if(towel.isDry() == false){ 
                cout << "nao\n";
            }
        } else if (aux == "end") {
            towel.end();
            break;
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}