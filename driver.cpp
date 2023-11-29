#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <cstdlib>



enum TokenType {
    ADD, 
    SUB, 
    MUL, 
    DIV, 
    L_PAREN,
    R_PAREN,
    NUM, 
    END 
};

struct Token {
    TokenType type;
    double value;
};

struct TreeNode {
    Token token;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(Token token) : token(token), left(nullptr), right(nullptr) {}
};

class Parser {
private:
    std::string input;
    size_t index = 0;
    Token currentToken;

    void nextToken() {
        while (index < input.length() && isspace(input[index])) {
            index++;
        }
        if (index == input.length()) {
            currentToken = {END, 0};
            return;
        }

        char curr = input[index];
        if (isdigit(curr)) {
            std::string number;
            while (index < input.length() && isdigit(input[index])) {
                number += input[index++];
            }
            currentToken = {NUM, std::stod(number)};
        } else {
            switch (curr) {
                case '+': currentToken = {ADD, 0}; break;
                case '-': currentToken = {SUB, 0}; break;
                case '*': currentToken = {MUL, 0}; break;
                case '/': currentToken = {DIV, 0}; break;
                case '(': currentToken = {L_PAREN, 0}; break;
                case ')': currentToken = {R_PAREN, 0}; break;
                default: throw std::runtime_error("Unexpected Error");
                }
            index++;
            }        
    }

    std::shared_ptr<TreeNode> expr();
    std::shared_ptr<TreeNode> term();
    std::shared_ptr<TreeNode> factor();

public:
    Parser(const std::string& input) : input(input), index(0) {
        nextToken();
    }
    std::shared_ptr<TreeNode> parse() {
        return expr();
    }
};

std::shared_ptr<TreeNode> Parser::expr() {
    std::shared_ptr<TreeNode> node = term();
    while (currentToken.type == ADD || currentToken.type == SUB) {
        Token token = currentToken;
        nextToken();
        std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>(token);
        newNode->left = node;
        newNode->right = term();
        node = newNode;
    }
    return node;
}

std::shared_ptr<TreeNode> Parser::term() {
    std::shared_ptr<TreeNode> node = factor();
    while (currentToken.type == MUL || currentToken.type == DIV) {
        Token token = currentToken;
        nextToken();
        std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>(token);
        newNode->left = node;
        newNode->right = factor();
        node = newNode;
    }
    return node;
}

std::shared_ptr<TreeNode> Parser::factor() {
    Token token = currentToken;
    if (token.type == NUM) {
        nextToken();
        return std::make_shared<TreeNode>(token);
    } else if (token.type == L_PAREN) {
        nextToken();
        std::shared_ptr<TreeNode> node = expr();
        if (currentToken.type != R_PAREN) {
            throw std::runtime_error("Expected ')'");
        }
        nextToken();
        return node;
    } else {
        throw std::runtime_error("Expected number or '('");
    }
}

double evaluateTree(const std::shared_ptr<TreeNode>& node) {
    if (!node) {
        return 0;
    }

    if (node->token.type == NUM) {
        return node->token.value;
    } else {

        double left = 0;
        if (node->left) {
            left = evaluateTree(node->left);
        }
        double right = 0;
        if (node->right) {
            right = evaluateTree(node->right);
        }
        switch (node->token.type) {
            case ADD: return left + right;
            case SUB: return left - right;
            case MUL: return left * right;
            case DIV: 
                if (right == 0) { 
                    throw std::runtime_error("Division by zero");
                }
                return left / right;
            default: throw std::runtime_error("Unexpected Error");
        }
    }
}
/**
 * @brief wraps the entire process of parsing and evaluating an expression
 * @param input the expression to evaluate
 * @return the result of the expression
 * @throw std::runtime_error if the expression is invalid 
 */
double evaluate(const std::string& input) {
    try {
        Parser parser(input);
        std::shared_ptr<TreeNode> root = parser.parse();
        return evaluateTree(root);
    } catch (const std::exception& e) {
        throw std::runtime_error("Invalid expression (" + std::string(e.what()) + ")"); 
    }
}
/**
 * @brief a shell for the user to enter expressions to evaluate
 */
void shell() {
    bool isDone = false;
    while (!isDone) {
        std::string input;
        std::cout << "Enter an expression: (or 'q' to quit) ";
        std::getline(std::cin, input);
        if (input == "q") {
            isDone = true;
        } else {
            try {
                double result = evaluate(input);
                std::cout << "Result: " << result << std::endl;
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}
   
int main() {
    shell();
    return 0;
}


