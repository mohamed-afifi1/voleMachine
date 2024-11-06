#include "VoleMachine.h"

bool Machine::isvalid(char c) {
    return isdigit(c) || (tolower(c) >= 'a' && tolower(c) <= 'f');
}

bool Machine::ishexchar(char c) {
    return isdigit(c) || (tolower(c) >= 'a' && tolower(c) <= 'f');
}

bool Machine::valid(string& s) {
    return s.size() == 4 && isvalid(s[0]) && ishexchar(s[1]) && ishexchar(s[2]) && ishexchar(s[3]);
}

int Machine::indexisvalid(string x) {
    for (char c : x) {
        if (!isdigit(c)) {
            cout << "Error: Not a valid number\n";
            return -1;
        }
    }

    int y;
    try {
        y = stoi(x);
    }
    catch (...) {
        cout << "Error: Invalid number conversion\n";
        return -1;
    }

    if (y < 2 || y > 255) {
        cout << "Error: Number must be between 2 and 255\n";
        return -1;
    }

    if (y % 2 != 0) {
        cout << "Error: Number must be even\n";
        return -1;
    }

    return y;
}

int Machine::setIndex() {
    cout << "memory start storing from index 10 decimal\n";
    cout << "do you want to change the index ?\n";
    cout << "1 - Yes\n2 - No\n";
    int c; cin >> c;
    while (cin.fail() || (c != 1 && c != 2)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid input\n";
        cout << "Enter 1 if you want to start storing in another index and 2 if not : ";
        cin >> c;
    }
    if (c == 2) return 10;
    cout << "enter index in decimal (even and between 2 and 255 inclusive): ";
    string ind;
    cin >> ind;
    while (indexisvalid(ind) == -1) {
        cout << "enter index in decimal (integer , even and between 2 and 255 inclusive): ";
        cin >> ind;
    }
    return indexisvalid(ind);
}

bool Machine::OpenFileAndGetInstructions() {
    string c = "C000";
    cout << "enter file name without extensions : ";
    string filename;
    cin >> filename;
    filename += ".txt";
    ifstream file(filename);
    if (!file) {
        cout << "error opening file\n";
        return false;
    }
    string instruction;
    int memIndex = setIndex();
    bool f = false;

    while (getline(file, instruction)) {
        string s = "";
        for (int i = 0; i < instruction.size(); i++) {
            if (instruction[i] != ' ') s += instruction[i];
            else continue;
            if (s.size() == 4) {
                if (!valid(s)) {
                    cout << "error at instructions \n";
                    return false;
                }
                for (char& ch : s) ch = toupper(ch);

                string s1 = { (char)toupper(s[0]), (char)toupper(s[1]) };
                string s2 = { (char)toupper(s[2]), (char)toupper(s[3]) };
                if (memIndex >= 256) {
                    cout << "Error instructions are more than 128\n ";
                    return false;
                }
                if (memIndex <= 254) memory.setcell(memIndex++, s1), memory.setcell(memIndex++, s2);
                if (s == c) {
                    f = true; return true;
                }

                s = "";
            }
        }
        if (s.size() != 0) {
            cout << "error at instructions \n";
            return false;
        }
    }
    if (!f && memIndex <= 254) {
        memory.setcell(memIndex++, "C0"), memory.setcell(memIndex++, "00");
    }
    return true;
}

bool Machine::GetInputFromTerminal() {
    string c = "C000";
    bool f = false;
    int memIndex = setIndex();
    bool ThereISAnotherInstructions = true;
    while (ThereISAnotherInstructions) {
        cout << "Enter instructions\n";
        cin.ignore();
        string instruction;
        getline(cin, instruction);
        string s = "";
        for (int i = 0; i < instruction.size(); i++) {
            if (instruction[i] != ' ') s += instruction[i];
            else continue;
            if (s.size() == 4) {
                if (!valid(s)) {
                    cout << "Error at instructions \n";
                    return false;
                }
                for (char& ch : s) ch = toupper(ch);

                f |= s == c;
                string s1 = { (char)toupper(s[0]), (char)toupper(s[1]) };
                string s2 = { (char)toupper(s[2]), (char)toupper(s[3]) };
                if (memIndex >= 256) {
                    cout << "Error instructions are more than 128\n ";
                    return false;
                }
                if (memIndex <= 254) memory.setcell(memIndex++, s1), memory.setcell(memIndex++, s2);
                if (f) return true;
                s = "";
            }
        }
        if (s.size() != 0) {
            cout << "error at instructions \n";
            return false;
        }
        int ans;
        cout << "There are other instructions ? \n";
        cout << "1 - YES\n2 - NO\n";
        cin >> ans;
        while (cin.fail() || (ans != 1 && ans != 2)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input\n";
            cout << "Enter 1 if there are more instructionms and 2 if not : ";
            cin >> ans;
        }
        if (ans == 2) {
            ThereISAnotherInstructions = false;
            if (!f && memIndex <= 254) {
                memory.setcell(memIndex++, "C0"), memory.setcell(memIndex++, "00");
            }
        }
    }
    return true;
}

void Machine::runProgram() {
    cpu.run(memory);
}

void Machine::runOnlyOne() {
    cpu.runOnlyOne(memory);
}

void Machine::output() {
    memory.printMemory();
    cpu.output();
}
