#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>



enum TokenType {
    ADD = 0, 
    SUB = 1, 
    MUL = 2, 
    DIV = 3, 
    L_PAREN = 4,
    R_PAREN = 5,
    NUM = 6, 
    END = 7 
};

enum PEMDAS {
    PARENTHESES = 3,
    EXPONENT = 2,
    MULTIPLY_DIVIDE = 1,
    ADD_SUBTRACT = 0,
};

struct Token {
    TokenType type;
    double value;
};



/**
 * @brief check if a char is a mathematic symbol
 * @returns 
 */
TokenType categorizeCharForMath(char c) {
    switch (c) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '(': return L_PAREN;
        case ')': return R_PAREN;
        default: return isdigit(c) ? NUM : END;
    } 
}

/**
 * @brief returns order of operations for a given symbol 
 * @returns order of operations 
*/
int getOrderOfOperations(TokenType type) {
    switch (type) {
        case ADD: case SUB: return ADD_SUBTRACT;
        case MUL: case DIV: return MULTIPLY_DIVIDE;
        case L_PAREN: case R_PAREN: return PARENTHESES;
        default: return -1;
    }
}

/**
 * @brief creates tokenized vector of input
*/
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    for (size_t i = 0; i < input.length(); i++) {
        if (isspace(input[i])) {
            continue;
        }
        TokenType type = categorizeCharForMath(input[i]);

        if (type == NUM) { // when we have numbers, we need to parse the whole number
            char* end;
            double value = std::strtod(&input[i], &end);
            tokens.push_back({NUM, value});
            i = end - &input[0] - 1;
        } else {
            tokens.push_back({type, 0});
        }
    }
    return tokens;
}
   
int main() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::cin >> input;

    std::vector<Token> tokens = tokenize(input);

    std::cout << "Tokens: ";

    for (const auto& token : tokens) {
        switch (token.type) {
            case ADD: std::cout << "+"; break;
            case SUB: std::cout << "-"; break;
            case MUL: std::cout << "*"; break;
            case DIV: std::cout << "/"; break;
            case L_PAREN: std::cout << "("; break;
            case R_PAREN: std::cout << ")"; break;
            case NUM: std::cout << token.value; break;
            case END: std::cout << "END"; break;
        }
        std::cout << ",";
    }
    return 0;
} 
