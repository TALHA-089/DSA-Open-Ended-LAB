#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class Player {
private:
    Player* prev;
    Player* next;
    string Name;
    int ODI, Test, T20;

public:
    Player(string Name = "", int ODI = 0, int Test = 0, int T20 = 0) {
        this->Name = Name;
        this->ODI = ODI;
        this->Test = Test;
        this->T20 = T20;
        prev = next = nullptr;
    }

    void setNext(Player* p) { next = p; }
    Player* getNext() { return next; }
    void setPrev(Player* p) { prev = p; }
    Player* getPrev() { return prev; }
    string getName() { return Name; }
    int getODIs() { return ODI; }
    int getTests() { return Test; }
    int getT20s() { return T20; }

    void updateData(string Name, int ODI, int Test, int T20) {
        this->Name = Name;
        this->ODI = ODI;
        this->Test = Test;
        this->T20 = T20;
    }

    friend ostream& operator<<(ostream& o, const Player& p);
};

ostream& operator<<(ostream& o, const Player& p) {
    o << p.Name << "\t" << p.ODI << "\t" << p.T20 << "\t" << p.Test;
    return o;
}