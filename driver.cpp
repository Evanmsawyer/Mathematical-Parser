#include <iostream>
#include <string>



int exeucte() {
    // create a REPL for a calculator

    // 1. read input from user
    std::string input;
    std::cout << "Enter an expression: ";

    // 2. parse the input

    // 3. evaluate the input
    // 4. print the result
    return 0;
}

/**
 * @brief check if a char is a mathematic symbol
 * @returns true if c is a symbol, false otherwise
 */
bool isSymbol(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
        return true;
    }
    return false;
}

int inputParser(std::string input) {
    std::string result;
    for (char c : input) {
        // look for char that is + - * / ( )
        if (isSymbol(c)) {
            
        }

    }
    return 0;

}

int main() {
    exeucte();
    return 0;
}