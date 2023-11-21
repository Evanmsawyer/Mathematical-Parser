#include <iostream>
#include <string>





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

/**
 * @brief takes user input and returns indexes of mathematic symbols
*/
int getIndexOfMathSymbols(std::string input) {
    std::string result;
    for (std::string::size_type i = 0; i < input.size(); i++) {
        char c = input[i];
        // look for char that is + - * / ( )
        if (isSymbol(c)) {
            // add index number to result string
            result += std::to_string(i);
        }

    }
    // convert string to int and return
    int resultInt = std::stoi(result);
    return resultInt;
}

int parseInput(std::string input, int symbolIndexes) {
    //TODO: break up String into tokens based on symbolIndexes
    
 }
    

    return -1;

int exeucte() {
    // create a REPL for a calculator

    // 0. read input from user
    std::string input;
    std::cout << "Enter an expression: ";

    // 1. parse the input
    std::cin >> input;
    int index = getIndexOfMathSymbols(input);

    printf("index: %d\n", index);
    // 2. evaluate the input
    // 3. print the result
    return -1;
}

int main() {
    exeucte();
    return 0;
}