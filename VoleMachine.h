#ifndef VOLE_MACHINE_H
#define VOLE_MACHINE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <bit>
#include <cstring>
#include<fstream>
#include <map>

using namespace std;

class Memory {
protected:
    int size = 256;
    vector<string> memory;

public:
    Memory();
    void setcell(int index, string value);
    string getcell(int index);
    void printMemory();
};
class Regester {
protected:
    int size = 16;
    vector<string> memory;
public:
    Regester();
    void setcell(int index, string value);
    string getcell(int index);
    void printRegester();
};
class ALU {
public:
    string intToBinary(int integerPart);
    string fracToBinary(float fractionalPart, int precision = 8);
    string floatToBinary(float num);
    float fromhextofloat(string hex);
    string fromfloattohex(float num);
    int hextodec(const string& s);
    string dectohex(int res);
    void add(int regstore, int firstReg, int secndReg, Regester& reg);
    void addFloat(int regstore, int firstReg, int secndReg, Regester& reg);
    void bitwise_Or(int regstore, int firstReg, int secndReg, Regester& reg);
    void bitwise_And(int regstore, int firstReg, int secndReg, Regester& reg);
    void bitwise_Xor(int regstore, int firstReg, int secndReg, Regester& reg);
    void rotate(int regNum, int number_of_rotations, Regester& reg);
    bool jump_to_location(int regnum, Regester& reg);

};

class CPU {
protected:
    int ProgramCounter;
    string InstructionRegister;
    ALU alu; 
    Regester regester;
    bool NotTerminated;
public:
    CPU();
    void setcell(int index, string value);
    void output();
    string getcell(int index);
    void fetch(Memory memory);
    vector<string> decode();
    void execute(Memory& memory, vector<string> operands);
    void run(Memory& memory);
};

class Machine {
    Memory memory;
    CPU cpu;
public:
    bool isvalid(char c);
    bool ishexchar(char c);
    bool valid(string& s);
    int indexisvalid(string x);
    int setIndex();
    bool OpenFileAndGetInstructions();
    bool GetInputFromTerminal();
    void runProgram();
    void output();

};
#endif
