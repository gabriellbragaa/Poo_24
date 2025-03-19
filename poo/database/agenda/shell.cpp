#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <list>
#include <map>

using namespace std;

template <class CONTAINER, class FUNC>
string map_join(const CONTAINER &cont, FUNC func, string sep = " ")
{
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        ss << (it == cont.begin() ? "" : sep) << func(*it);
    }
    return ss.str();
}

class Fone{
    string id;
    string number;

public:
    Fone(string id = "", string number = "") : id(id), number(number){}
    

    string getId(){
        return id;
    }

    string getNumber(){
        return number;
    }

    bool isValidNumber() {
        for (char c : number) {
            if (!isdigit(c) && c != '(' && c != ')' && c != '-' && c != '.') {
            
                return false;
            }
        }
        return true;
    }


    string toString() {
        return id + (number.empty() ? "" : ":" + number);
    }
    
};

class Contact{
    string name;
    bool favorited;
    vector<Fone> fones;
public:
    Contact(string name = ""){
        this->name = name;
        this->favorited = false;
    }

    string getName(){
        return name;
    }

    void add(Fone fone){
        if (!fone.isValidNumber()) {
         
             return;
        }
        fones.push_back(fone);
    
    }

    void rm(int index){
        fones.erase(fones.begin() + index);
    }

    void isFavorited(){
        favorited = !favorited;
    }
    string str() {
        stringstream ss;
        ss << (favorited ? "@ " : "- ") << getName() 
           << " [" << map_join(fones, [](Fone fone) { return fone.toString(); }, ",") << "]";
        return ss.str();
    }
    
};  

int main()
{
    map<string, Contact> contacts;
    
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "add") {
            string name, id, number;
            ss >> name >> id >> number;
            
            if (contacts.find(name) == contacts.end()) {
                contacts[name] = Contact(name);
            }
            contacts[name].add(Fone(id, number));
        } else if (cmd == "rm") {
            string name;
            int index;
            ss >> name >> index;

            if (contacts.find(name) != contacts.end()) {
                contacts[name].rm(index);
            }
        } else if (cmd == "tfav") {
            string name;
            ss >> name;

            if (contacts.find(name) != contacts.end()) {
                contacts[name].isFavorited();
            }
        } else if (cmd == "show") {
            for (auto& [key, contact] : contacts) {
                cout << contact.str() << endl;
            }
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
