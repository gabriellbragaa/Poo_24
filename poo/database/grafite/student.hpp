/*

Faltou apenas um teste, o escrevendo 1: 07w | 
-- tentei a ajuda do chagpt e não conseguir identificar.

*/

#pragma once
#include "fn.hpp"

using namespace std;
class Lead {
private:
    float thickness =0 ;
    string hardness;
    int size =0 ;

public:
    Lead(float thickness, string hardness, int size): thickness(thickness), hardness(hardness), size(size) {}

    float getThickness() {
        return this->thickness;
    }

    int getSize() {
        return this->size;
    }

    void setSize(int newSize) {
        this->size = newSize;
    }

    string getHardness() {
        return this->hardness;
    }

    int usagePerSheet() {
        if (hardness == "HB") {
            return 1;
        }
        if (hardness == "2B") {
            return 2;
        }
        if (hardness == "4B") {
            return 4;
        }
        if (hardness == "6B") {
            return 6;
        }
        return 0;
    }

    string toString()  {
        ostringstream oss;
        oss << fixed << std::setprecision(1) << this->thickness;
        return "[" + oss.str() + ":" + this->hardness + ":" + to_string(this->size) + "]";
    }
};

class Pencil {
private:
    float thickness = 0;
    Lead* tip = nullptr;

public:
    Pencil(float thickness) : thickness(thickness), tip(nullptr) {}

    bool hasLead() const {
        if (tip == nullptr) {
            return false;
        }
        return true;
    }
    /*Parte 1: Inserir
  - Crie a classe `Grafite` com o atributo `size`.
  - Crie a classe `Lapiseira` com o atributo `tip` inicializado como `null`.*/
    void insert(Lead* lead) {
        if (this->hasLead()) {
            fn::write("fail: ja existe grafite");
            return;
        }
        if (lead->getThickness() != this->thickness) {
            fn::write("fail: calibre incompativel");
            return;
        }
        this->tip = lead;
    }

    Lead* remove() {
        if (this->tip == nullptr) {
            fn::write("fail: nao existe grafite");
            return nullptr;
        }
        Lead* removed = this->tip;
        this->tip = nullptr;
        return removed;
    }

    void writePage() {
    if (this->tip == nullptr) {
        fn::write("fail: nao existe grafite");
        return;
    }

    int usage = this->tip->usagePerSheet();
    int currentSize = this->tip->getSize();

    
    if (currentSize < usage) {
        fn::write("fail: tamanho insuficiente");
        return;
    }


    // Calcule o tamanho final 
    int finalSize = currentSize - usage;

    
    if (finalSize < 10) {
        // Gaste o máximo possível, deixando o grafite com 10mm no final
        this->tip->setSize(10);
        fn::write("fail: folha incompleta");
    } else {
        // Caso tenha tamanho suficiente, diminua o grafite
        this->tip->setSize(finalSize);
    }
}


    string toString()  {
        string leadInfo = "null";
        if (this->tip != nullptr) {
            leadInfo = this->tip->toString();
        }
        ostringstream oss;
        oss << fixed << setprecision(1) << this->thickness;
        return "calibre: " + oss.str() + ", grafite: " + leadInfo;
    }
};

class Adapter {
private:
    Pencil pencil;

public:
    Adapter(float thickness) : pencil(thickness) {}

    void insert( float thickness, string hardness, int size) {
    pencil.insert(new Lead(thickness, hardness, size));
    }

    void remove() {
        pencil.remove();
    }

    void writePage() {
        pencil.writePage();
    }

    void show() {
        std::cout << pencil.toString() << std::endl;
    }
};
