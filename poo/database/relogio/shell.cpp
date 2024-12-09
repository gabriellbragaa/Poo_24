#include "fn.hpp"

using namespace std;

class Relogio
{
private:
    int hour=0;
    int minute=0;
    int second=0;
public:
     Relogio(int h, int m, int s) {

      setHour(h); 
      setMinute(m); 
      setSecond(s);
      }
    
// como os parametris sao privados, devo criar os metodos gets
    int getHour()  {
     
    return hour; 
    }
    int getMinute() {
    return minute; 
    }
    int getSecond() {
    return second; 
    }

void setHour(int h){
    if ( h < 0 || h > 23){
        cout << "fail: hora invalida" << endl; 
        return;
    }
     this->hour = h;
}
void setMinute(int m){
    if(m < 0 || m > 59){
        cout << "fail: minuto invalido" << endl; 
        return;
    }
    this-> minute = m;
}
void setSecond(int s){
    if(s < 0 || s > 59){
        cout << "fail: segundo invalido" << endl; 
        return;
    }
     this-> second = s;
}
// Parte 5: nextSecond
    // - Crie um método nextSecond que incrementa o segundo em 1.
    // - Crie um objeto relógio, atribua valores para hora, minuto e segundo e imprima a hora.
    // - Teste o método nextSecond criando horas com os seguintes valores e testando:
    // - 10:02:30
    // - 15:50:59
    // - 21:59:59
    // - 23:59:59
     void nextSecond() {    // ajuda do chat
        second++;
        if (second > 59) {
            second = 0;
            minute++;
            if (minute > 59) {
                minute = 0;
                hour++;
                if (hour > 23) {
                    hour = 0; 
                }
            }
        }
    }
    string toString() { // ajuda do chat
    string h = (hour < 10 ? "0" : "") + std::to_string(hour);
    string m = (minute < 10 ? "0" : "") + std::to_string(minute);
    string s = (second < 10 ? "0" : "") + std::to_string(second);
    return h + ":" + m + ":" + s;
}
};

class Adapter {
private:
    Relogio time;

public:
    // criar o Construtor
    Adapter(int hour = 0, int minute = 0, int second = 0) : time(hour, minute, second) {}

    // inicialização
    void init(int hour = 0, int minute = 0, int second = 0) {
        
        this->time = Relogio(hour, minute, second);
    }
    void setHour(int hour) {
        (void) hour;
        this-> time.setHour(hour);
    }

    void setMinute(int minute) {
        time.setMinute(minute);
    }

    void setSecond(int second) {
        time.setSecond(second);
    }

    // Método para incrementar o segundo
    void nextSecond() {
        time.nextSecond();
    }

    
    void show() {
        fn::write(time.toString());
    }
};

int main() {
    Adapter stu;

    while (true) {
        fn::write("$", "");

        auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write(line);

        if (args[0] == "end") {
            break;
        }
        else if (args[0] == "set") {
            stu.setHour(+args[1]);
            stu.setMinute(+args[2]);
            stu.setSecond(+args[3]);
        } 
        else if (args[0] == "init") {
            stu.init(+args[1], +args[2], +args[3]);
        }
        else if (args[0] == "show") {
            stu.show();
        }
        else if (args[0] == "next") {
            stu.nextSecond();
        }
        else {
            fn::write("fail: comando invalido");
        }
    }
    return 0;
}