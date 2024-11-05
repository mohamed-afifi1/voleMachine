#include "voleMachine.hpp"

using namespace std;
class Memory {
protected:
    int size = 256;
    vector<string> memory;
public:
    Memory() {
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
 
    void printMemory() {
        int cnt = 0;
        cout << "memory cells 16 X 16 \n";
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
};