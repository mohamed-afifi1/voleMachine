#include "VoleMachine.h"

Regester::Regester() {
    memory.resize(size, "00");
}

void Regester::setcell(int index, string value) {
    if (index >= 0 && index < size) {
        memory[index] = value;
    }
}

string Regester::getcell(int index) {
    if (index >= 0 && index < size) {
        return memory[index];
    }
    return "Memory out of bounds";
}

void Regester::printRegester() {
    map<int, char> decimalToHex = {
        {10, 'A'},
        {11, 'B'},
        {12, 'C'},
        {13, 'D'},
        {14, 'E'},
        {15, 'F'}
    };
    cout << "register cells 16 \n";
    for (int i = 0; i < size; i++) {
        if (i > 9) {
            cout << "Register " << decimalToHex[i] << ": " << memory[i] << "\n";
            continue;
        }
        cout << "Register " << i << ": " << memory[i] << "\n";
    }
    cout << endl;
}
