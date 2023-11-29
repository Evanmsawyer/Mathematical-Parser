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
/**
 * @brief a node in the expression tree. has a token and pointers to its left and right children
*/
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

    /**
     * @brief gets the next token in the input. works as follows:
     *     1. while the current character is whitespace, increment index
     *     2. if index is equal to the length of the input, set currentToken to {END, 0} and return
     *     3. store the current character in curr
     *     4. a.) if curr is a digit, store the number in number by incrementing index until the current character is not a digit, 
     *            then set currentToken to {NUM, number}
     *        b.) otherwise, set currentToken to the appropriate token based on curr
    */
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

/**
 * @brief parses an expression, works as follows:
 *      1. call term() and store the result in node
 *      2. while the current token is ADD or SUB:
 *         a. create a new node with the current token
 *         b. call nextToken()
 *         c. set the left child of the new node to node and the right child to term()
 *         d. set node to the new node
 *  @return the node, which is the root of the expression tree
*/
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
/**
 * @brief parses a term, works as follows:
 *     1. call factor() and store the result in node
 *     2. while the current token is MUL or DIV:
 *        a. create a new node with the current token
 *        b. call nextToken() 
 *        c. set the left child of the new node to node and the right child to factor()
 *        d. set node to the new node
 * @return the node, which is the root of the term tree
*/
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
/**
 * @brief parses a factor, works as follows:
 *     1. store the current token in token
 *     2.  a.) if the current token is a number, call nextToken() and return a new node with token as the token
 *         b.) if the current token is a left parenthesis, call nextToken(), set node to expr(), and call nextToken() again to account for the right parenthesis
 * 
 * @return the node, which is the root of the factor tree
 * @throw std::runtime_error if the current token is not a number or left parenthesis
*/
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

/**
 * @brief evaluates an expression tree, works as follows:
 *    1. if node is null, return 0
 *    2. if the token of node is a number, return the value of the token
 *    3. if it is not a number, it is an operator, so we evaluate the left and right children by recursively calling evaluateTree()
 *    4. depending on the operator, we return the sum, difference, product, or quotient of the left and right children
*/
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


