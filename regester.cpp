#include "voleMachine.hpp"

using namespace std;


class Regester {
protected:
    int size = 16;
    vector<string> memory;
public:
    Regester() {
        memory.resize(size, "00");
    }
    void setcell(int index, string value) {
        if (index >= 0 && index < size) {
            memory[index] = value;
        }
    }
    string getcell(int index) {
        if (index >= 0 && index < size) {
            return memory[index];
        }
        return "Memory out of bounds";
    }
    void printRegester() {
        cout << "register cells 16 \n";
        for (int i = 0; i < size; i++) {
            if (i > 9 ){
                cout << "Register " << decimalToHex[i] << ":" << "   " << memory[i] << "\n";
                continue ;
            }
            cout << "Register " << i << ":" << "   " << memory[i] << "\n";
        }
        cout << endl;
    }
};