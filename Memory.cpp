#include "VoleMachine.h"
Memory::Memory() {
    memory.resize(size, "00");
}

void Memory::setcell(int index, string value) {
    if (index >= 0 && index < size) {
        memory[index] = value;
    }
}

string Memory::getcell(int index) {
    if (index >= 0 && index < size) {
        return memory[index];
    }
    return "Memory out of bounds";
}

void Memory::printMemory() {
    map<int, char> decimalToHex = {
        {10, 'A'},
        {11, 'B'},
        {12, 'C'},
        {13, 'D'},
        {14, 'E'},
        {15, 'F'}
    };
    int cnt = 0;
    cout << "\nmemory cells 16 X 16 \n";
    int rowindex = 1;
    cout << "  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n";
    cout << "0 ";
    for (int i = 0; i < size; i++) {
        cout << memory[i] << " ";
        cnt++;
        if (cnt % 16 == 0) {
            cout << '\n';
            if (rowindex > 9) {
                cout << decimalToHex[rowindex++] << ' ';
                continue;
            }
            cout << rowindex++ << ' ';
        }
    }
    cout << endl;
}
