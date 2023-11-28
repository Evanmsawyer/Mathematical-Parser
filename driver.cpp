#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stack>



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

/**
 * @brief converts vector of tokens to postfix notation
*/
std::vector<Token> toPostfix(const std::vector<Token>& tokens) {
    std::vector<Token> postfix;
    std::stack<Token> stack;

    for (const auto& token : tokens) {
        switch (token.type) {
            case NUM: 
                postfix.push_back(token); // if it's a number, push it to the postfix vector
                break;
            case ADD: 
            case SUB: 
            case MUL: 
            case DIV: { // if it's an operator, pop all operators with higher precedence off the stack and push them to the postfix vector
                while (!stack.empty() && getOrderOfOperations(stack.top().type) >= getOrderOfOperations(token.type)) { 
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                stack.push(token);
                break;
            }
            case L_PAREN: // if it's a left parenthesis, push it to the stack 
                stack.push(token); 
                break;
            case R_PAREN: { // if it's a right parenthesis, pop all operators off the stack until we find a left parenthesis
                while (!stack.empty() && stack.top().type != L_PAREN) {
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                if (!stack.empty()) {
                    stack.pop();
                }
                break;
            }
            default: // if it's an unexpected token, do nothing
                break;
            }
        }
        while (!stack.empty()) { // if there are still operators on the stack, pop them off and push them to the postfix vector
            postfix.push_back(stack.top());
            stack.pop();
    }  
    return postfix;
}

/**
 * @brief evaluates postfix expression
*/
double evaluatePostfix(const std::vector<Token>& postfix) {
    std::stack<double> stack;

    for (const auto& token : postfix) {
        if (token.type == NUM) { // if it's a number, push it to the stack
            stack.push(token.value);
        } else { // if it's an operator, pop two numbers off the stack, apply the operator, and push the result back to the stack
            double right = stack.top();
            stack.pop();
            double left = stack.top();
            stack.pop();

            switch (token.type) { // performs operations and pushes result to stack
                case ADD: stack.push(left + right); break;
                case SUB: stack.push(left - right); break;
                case MUL: stack.push(left * right); break;
                case DIV: stack.push(left / right); break;
                default: break; // if unexpected operator, do nothing
            }
        }
    }
    return stack.top();
}

/**
 * @brief FOR DEBUG -> turn this on to see the tokens and postfix notation
*/
void debugInfo(const std::vector<Token>& tokens, const std::vector<Token>& postfix) {
    printf("Tokens: ");
    for (const auto& token : tokens) {
        switch (token.type) {
        case ADD: printf("+ "); break;
        case SUB: printf("- "); break;
        case MUL: printf("* "); break;
        case DIV: printf("/ "); break;
        case L_PAREN: printf("( "); break;
        case R_PAREN: printf(") "); break;
        case NUM: printf("%f ", token.value); break;
        case END: printf("END "); break;
        }
    }
    printf("\nPostfix: ");
    for (const auto& token : postfix) {
        switch (token.type) {
        case ADD: printf("+ "); break;
        case SUB: printf("- "); break;
        case MUL: printf("* "); break;
        case DIV: printf("/ "); break;
        case NUM: printf("%f ", token.value); break;
        }
    }
    printf("\n");
}
    
   
int main() {

    bool running = true;

    while (running) {
        std::string input;
        std::cout << "Enter an expression: ";
        std::cin >> input;
        std::vector<Token> tokens = tokenize(input);
        std::vector<Token> postfix = toPostfix(tokens);
        debugInfo(tokens, postfix);
        double result = evaluatePostfix(postfix);
        printf("Result: %f\n", result);

        std::cout << "Continue? (y/n): ";
        std::cin >> input;
        running = input == "y";
    }
    return 0;
}


