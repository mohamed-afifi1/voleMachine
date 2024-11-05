#include "voleMachine.hpp"
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

class CPU {
protected:
    int ProgramCounter;
    string InstructionRegister;
    ALU alu;
    Regester regester;
    bool NotTerminated;
public:
    CPU() {
        ProgramCounter = 0;
        InstructionRegister = "";
        NotTerminated = true;
    }
    void setcell(int index, string value) {
        regester.setcell(index, value);
    }
    void output()
    {
        regester.printRegester();
    }
    string getcell(int index) {
        return regester.getcell(index);
    }
 
    void fetch(Memory memory) {
        InstructionRegister = memory.getcell(ProgramCounter) + memory.getcell(ProgramCounter + 1);
        ProgramCounter += 2;
    }
    vector<string> decode() {
        vector<string> operands;
        string opcode = InstructionRegister.substr(0, 1);
        string operand1 = InstructionRegister.substr(1, 1);
        string operand2 = InstructionRegister.substr(2, 1);
        string operand3 = InstructionRegister.substr(3, 4);
        operands.push_back(opcode);
        operands.push_back(operand1);
        operands.push_back(operand2);
        operands.push_back(operand3);
        return operands;
    }
    void execute(Memory& memory, vector<string> operands)
    {
        string opcode = operands[0];
        if (opcode == "1") {
 
            int regesterIdx = alu.hextodec(operands[1]);
            int memoryIdx = alu.hextodec(operands[2] + operands[3]);
            regester.setcell(regesterIdx, memory.getcell(memoryIdx));
        }
        else if (opcode == "2") {
            int regesterIdx1 = alu.hextodec(operands[1]);
            string num = operands[2] + operands[3];
            regester.setcell(regesterIdx1, num);
        }
        else if (opcode == "3") {
            int regesterIdx = alu.hextodec(operands[1]);
            int memoryIdx = alu.hextodec(operands[2] + operands[3]);
            memory.setcell(memoryIdx, regester.getcell(regesterIdx));
            if (memoryIdx == 0)
            {
                cout << regester.getcell(regesterIdx);
            }
        }
        else if (opcode == "4") {
            if (operands[1] == "0")
            {
                int regesterIdx1 = alu.hextodec(operands[2]);
                int regesterIdx2 = alu.hextodec(operands[3]);
                regester.setcell(regesterIdx2, regester.getcell(regesterIdx1));
            }
        }
        else if (opcode == "5") {
            int regesterResult = alu.hextodec(operands[1]);
            int regesterIdx1 = alu.hextodec(operands[2]);
            int regesterIdx2 = alu.hextodec(operands[3]);
            alu.add(regesterResult, regesterIdx1, regesterIdx2, regester);
        }
        else if (opcode == "6") {
            int regesterResult = alu.hextodec(operands[1]);
            int regesterIdx1 = alu.hextodec(operands[2]);
            int regesterIdx2 = alu.hextodec(operands[3]);
            alu.addFloat(regesterResult, regesterIdx1, regesterIdx2, regester);
        }
        else if (opcode == "7") {
            int regesterResult = alu.hextodec(operands[1]);
            int regesterIdx1 = alu.hextodec(operands[2]);
            int regesterIdx2 = alu.hextodec(operands[3]);
            alu.bitwise_Or(regesterResult, regesterIdx1, regesterIdx2, regester);
 
        }
        else if (opcode == "8") {
 
            int regesterResult = alu.hextodec(operands[1]);
            int regesterIdx1 = alu.hextodec(operands[2]);
            int regesterIdx2 = alu.hextodec(operands[3]);
            alu.bitwise_And(regesterResult, regesterIdx1, regesterIdx2, regester);
        }
        else if (opcode == "9") {
            int regesterResult = alu.hextodec(operands[1]);
            int regesterIdx1 = alu.hextodec(operands[2]);
            int regesterIdx2 = alu.hextodec(operands[3]);
            alu.bitwise_Xor(regesterResult, regesterIdx1, regesterIdx2, regester);
        }
        else if (opcode == "A") {
            int regNum = alu.hextodec(operands[1]);
            int op = alu.hextodec(operands[2]);
            int num_of_rotations = alu.hextodec(operands[3]);
            if (op == 0) {
                alu.rotate(regNum, num_of_rotations, regester);
            }
        }
        else if (opcode == "B") {
            int regesterIdx = alu.hextodec(operands[1]);
            int memoryIdx = alu.hextodec(operands[2] + operands[3]);
            if (regester.getcell(regesterIdx) == regester.getcell(0)) {
                ProgramCounter = memoryIdx;
            }
        }
        else if (opcode == "C") {
            if (operands[1] == "0" && operands[2] == "0" && operands[3] == "0")
            {
                NotTerminated = false;
            }
        }
        else if (opcode == "D") {
            int regesterIdx = alu.hextodec(operands[1]);
            int memoryIdx = alu.hextodec(operands[2] + operands[3]);
            if (alu.jump_to_location(regesterIdx, regester)) {
                ProgramCounter = memoryIdx;
            }
 
        }
    }
 
    void run(Memory& memory) {
        while (ProgramCounter < 256 && NotTerminated) {
            fetch(memory);
            vector<string> operands = decode();
            execute(memory, operands);
        }
    }
};