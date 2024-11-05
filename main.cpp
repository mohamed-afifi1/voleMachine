#include "VoleMachine.h"

map<int, char> decimalToHex = {
        {10, 'A'},
        {11, 'B'},
        {12, 'C'},
        {13, 'D'},
        {14, 'E'},
        {15, 'F'}
};

string ConvertToLower(string& s) {
    for (char& ch : s)ch = tolower(ch);
    return s;
}


int main()
{

    bool f = true;
    while (f) {
        cout << "Welcome to our vole machine.\n";
        while (true) {
            cout << "1 - Start the program\n2 - Exit the program\n";
            int ans;
            cin >> ans;
            while (cin.fail() || (ans != 1 && ans != 2)) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invalid input\n";
                cout << "1 - Start the program\n2 - Exit the program\n";
                cin >> ans;
            }
            if (ans == 1) {
                int  choice;
                cout << "Enter 1 to load instructions from file and 2 to take from terminal : ";
                cin >> choice;
                while (cin.fail() || (choice != 1 && choice != 2)) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "invalid input\n";
                    cout << "Enter 1 to load instructions from file and 2 to take from terminal : ";
                    cin >> choice;
                }
                if (choice == 1) {
                    Machine machine;
                    if (machine.OpenFileAndGetInstructions()) {
                        machine.runProgram();
                        machine.output();
                    }

                }
                else if (choice ==  2) {
                    Machine machine;
                    if (machine.GetInputFromTerminal()) {
                        machine.runProgram();
                        machine.output();
                    }
                }
            }
            else if (ans == 2) {
                f = false;
                break;
            }
        }
    }
    return 0;
}
