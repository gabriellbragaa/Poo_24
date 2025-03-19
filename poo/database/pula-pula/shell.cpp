#include <iostream>
#include <memory>
#include <sstream>
#include <list>
using namespace std;


template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}




class Crianca{

private:
    string name;
    int idade;
    

public: 
    Crianca(string name, int idade): name(name) , idade(idade) {}

// chama os get
    string getName(){ return name; }

    int getIdade(){ return idade; }

    void setName(string name){ this -> name = name; }

    void setIdade(int idade){ this -> idade = idade; }

    string str(){
        return name + ":" + to_string(idade);
    }

};

class Trampolim{

private: 

    list<Crianca> playing;
    list<Crianca> waiting;

    Crianca* removeList(const string& name, list<Crianca>& lista) {
        for (auto i = lista.begin(); i != lista.end(); ++i) {
            if (i->getName() == name) {
                Crianca* removeCrianca = new Crianca(i->getName(), i->getIdade());
                lista.erase(i);// remove o elemento apontado pelo interador
                return removeCrianca;
            }
        }
        return nullptr;
    }


public:
    

    void arrive(Crianca Crianca){
        waiting.push_front(Crianca);
 // adiciona crianca no final da fila apos ela ter usado o pula pula 
    
    }


    void enter(){
    if(!waiting.empty()){
        playing.push_front(waiting.back()); // Adiciona a última criança da fila `waiting`
        waiting.pop_back(); // Remove a última criança da fila `waiting`
    }
}
    
    // inverso do enter
    void leave(){
        if(!playing.empty()){
            Crianca criancaSaiu = playing.front();
            waiting.push_back(criancaSaiu); 
            playing.pop_front(); 
         
        }
    }

    // 
    Crianca* removeCrianca(string name){
        Crianca* crianca ;
        crianca = removeList(name, playing);
            if(crianca == nullptr){
               crianca = removeList(name, waiting);
            }
        return crianca;

    }

      string toString() {
    stringstream ss;
    ss << "[";
    for (auto i = waiting.begin(); i != waiting.end(); ++ i) {
        if (i != waiting.begin()) ss << ", ";
        ss << i -> getName() << ":" << i -> getIdade();
    }
    ss << "] => [";

    for (auto i = playing.begin(); i != playing.end(); ++i) {
        if (i != playing.begin()) ss << ", ";
        ss << i->str();
    }
    ss << "]";
    return ss.str();
}


};



int main() {

    Trampolim trampolim;

    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << trampolim.toString() << endl;
        } else if (cmd == "arrive") {
             string name;
             int age;
             ss >> name >> age;
            trampolim.arrive(Crianca(name, age)); 
        } else if (cmd == "enter") {
            trampolim.enter();
        } else if (cmd == "leave") {
            trampolim.leave();
        } else if (cmd == "remove") {
             string name;
             ss >> name;
            Crianca* removed = trampolim.removeCrianca(name);
            if (removed == nullptr) {
                cout << "fail: " << name << " nao esta na fila" << endl;
            }
            delete removed; // Liberar memória se necessário
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
