#include <iostream>
#include <string>
using namespace std;

// Functions to generate expressions for 3, 4, and 5 variable K-maps
void generateExpression3(int a, int b, string* expression) {
    string values[2][4] = {"A'B'C'", "A'B'C", "A'BC", "A'BC'", "AB'C'", "AB'C", "ABC", "ABC'"};
    for (int i = 0; i < 8; i++) {
        if (*(expression + i) == "") {
            *(expression + i) = values[a][b];
            break;
        }
    }
}

void generateExpression4(int a, int b, string* expression) {
    string values[4][4] = {"A'B'C'D'", "A'B'C'D", "A'B'CD", "A'B'CD'", "A'BC'D'", "A'BC'D", "A'BCD", "A'BCD'",
                           "ABC'D'", "ABC'D", "ABCD", "ABCD'", "AB'C'D'", "AB'C'D", "AB'CD", "AB'CD'"};
    for (int i = 0; i < 16; i++) {
        if (*(expression + i) == "") {
            *(expression + i) = values[a][b];
            break;
        }
    }
}

void generateExpression5(int a, int b, string* expression) {
    string values[4][8] = {"A'B'C'D'E'", "A'B'C'D'E", "A'B'C'DE", "A'B'C'DE'", "A'B'CD'E'", "A'B'CD'E",
                           "A'B'CDE", "A'B'CDE'", "A'BC'D'E'", "A'BC'D'E", "A'BC'DE", "A'BC'DE'", "A'BCD'E'", "A'BCD'E", "A'BCDE",
                           "A'BCDE'", "ABC'D'E", "ABC'D'E", "ABC'DE", "ABC'DE'", "ABCD'E'", "ABCD'E", "ABCDE", "ABCDE'", "AB'C'D'E'",
                           "AB'C'D'E", "AB'C'DE", "AB'C'DE'", "AB'CD'E'", "AB'CD'E", "AB'CDE", "AB'CDE'"};
    for (int i = 0; i < 32; i++) {
        if (*(expression + i) == "") {
            *(expression + i) = values[a][b];
            break;
        }
    }
}

// Functions to display the K-map for 3, 4, and 5 variables
void displayKMap3(int size, int* minterms, int* counter, int i, int j, string* expression) {
    bool found = false;
    for (int k = 0; k < size; k++) {
        if (*(minterms + k) == *counter) {
            cout << 1;
            found = true;
            generateExpression3(i, j, expression);
            break;
        }
    }
    if (!found) {
        cout << 0;
    }
    *counter += 1;
}

void displayKMap4(int size, int* minterms, int* counter, int i, int j, string* expression) {
    bool found = false;
    for (int k = 0; k < size; k++) {
        if (*(minterms + k) == *counter) {
            cout << 1;
            found = true;
            generateExpression4(i, j, expression);
            break;
        }
    }
    if (!found) {
        cout << 0;
    }
    *counter += 1;
}

void displayKMap5(int size, int* minterms, int* counter, int i, int j, string* expression) {
    bool found = false;
    for (int k = 0; k < size; k++) {
        if (*(minterms + k) == *counter) {
            cout << 1;
            found = true;
            generateExpression5(i, j, expression);
            break;
        }
    }
    if (!found) {
        cout << 0;
    }
    *counter += 1;
}

// Function to print the minimized Boolean expression
void printExpression(string* expression, int exprSize) {
    bool firstTerm = true;
    for (int i = 0; i < exprSize; i++) {
        if (*(expression + i) != "") {
            if (!firstTerm) {
                cout << " + ";
            }
            cout << *(expression + i);
            firstTerm = false;
        }
    }
    cout << endl;
}

// Function to iterate through the K-map cells
void iterateKMap(int* counter, int size, int choice, int row, string* expression, int* minterms) {
    int loopCount = (choice == 3) ? 8 : 4;
    for (int col = 0; col < loopCount; col++) {
        if (col == 2 || col == 6) {
            *counter += 1;
        } else if (col == 3 || col == 7) {
            *counter -= 1;
        }

        if (choice == 1) {
            displayKMap3(size, minterms, counter, row, col, expression);
        } else if (choice == 2) {
            displayKMap4(size, minterms, counter, row, col, expression);
        } else if (choice == 3) {
            displayKMap5(size, minterms, counter, row, col, expression);
        }

        if (col == 2 || col == 6) {
            *counter -= 1;
        } else if (col == 3 || col == 7) {
            *counter += 1;
        }

        cout << "   ";
        if (choice == 3) {
            cout << " ";
        }
    }
}

int main() {
    int choice;
    cout << "Enter 1 for 3 variables K-map, 2 for 4 variables K-map, 3 for 5 variables K-map: ";
    cin >> choice;

    int size;
    cout << "Enter the number of minterms you want to enter: ";
    cin >> size;

    int minterms[size];
    for (int i = 0; i < size; i++) {
        cout << "Enter the value of " << i + 1 << " minterm: ";
        cin >> minterms[i];
    }

    const int exprSize = 32;
    string expression[exprSize] = {""};

    int counter = 0;

    if (choice == 1) {
        cout << "\n BC  00  01  11  10\nA\n\n";
        for (int row = 0; row < 2; row++) {
            cout << row << "     ";
            iterateKMap(&counter, size, choice, row, expression, minterms);
            cout << endl;
        }
    } else if (choice == 2) {
        cout << "\n  CD  00  01  11  10\nAB\n\n";
        for (int row = 0; row < 4; row++) {
            cout << (row == 0 ? "00" : row == 1 ? "01" : row == 2 ? "11" : "10") << "     ";
            if (row == 3) counter -= 4;
            if (row == 2) counter += 4;
            iterateKMap(&counter, size, choice, row, expression, minterms);
            if (row == 3) counter += 4;
            if (row == 2) counter -= 4;
            cout << endl;
        }
    } else if (choice == 3) {
        cout << "\n  CDE  000  001  011  010  100  101  111  110\nAB\n\n";
        for (int row = 0; row < 4; row++) {
            cout << (row == 0 ? "00" : row == 1 ? "01" : row == 2 ? "11" : "10") << "      ";
            if (row == 3) counter -= 4;
            if (row == 2) counter += 4;
            iterateKMap(&counter, size, choice, row, expression, minterms);
            if (row == 3) counter += 4;
            if (row == 2) counter -= 4;
            cout << endl;
        }
    }

    cout << "\nExpression\n";
    printExpression(expression, exprSize);
    cout << "\n\n";
    return 0;
}
