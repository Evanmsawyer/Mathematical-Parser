#include <iostream>
#include <string>



enum {
    ADD = 0, 
    SUB = 1, 
    MUL = 2, 
    DIV = 3, 
    L_PAREN = 4,
    R_PAREN = 5,
    NUM = 6, 
    END = 7 
};



/**
 * @brief check if a char is a mathematic symbol
 * @returns true if c is a symbol, false otherwise
 */
int categorizeCharForMath(char c) {
    if (c == '+') {
        return ADD;
    } else if (c == '-') {
        return SUB;
    } else if (c == '*') {
        return MUL;
    } else if (c == '/') {
        return DIV;
    } else if (c == '(') {
        return L_PAREN;
    } else if (c == ')') {
        return R_PAREN;
    } else if (isdigit(c)) {
        return NUM;
    } else {
        return END;
    }
    return -1;
}

/**
 * @brief takes user input and returns indexes of mathematic symbols
*/
std::string parseInput(std::string input) {
    std::string result;
    for (std::string::size_type i = 0; i < input.size(); i++) {
        char c = input[i];
        int charType = categorizeCharForMath(c);     
        result += std::to_string(charType); 
        
    }
    return result;
}

    

int execute() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::cin >> input;
    std::string values = parseInput(input);

    printf("input: %s\n", input);  
    printf("value: %d\n", values.c_str());
    return 0;
}

int main() {
    execute();
    return 0;
}