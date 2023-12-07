#include "parser.h"

using namespace parser;
using namespace std;

TreeNode::TreeNode(Token token) : token(token) {}

class Parser
{
private:
    string input;
    size_t index;
    Token currentToken;

    void nextToken()
    {
        while (index < input.length() && isspace(input[index]))
            index++;

        if (index == input.length())
        {
            currentToken = {END};
            return;
        }

        char curr = input[index];
        if (isdigit(curr))
        {
            string number;
            while (index < input.length() && isdigit(input[index])) {
                number += input[index++];
            }
            currentToken = {NUM, stod(number)};
        } 
        else 
        {
            switch (curr)
                {
                case '+': currentToken = {ADD}; break;
                case '-': currentToken = {SUB}; break;
                case '*': currentToken = {MUL}; break;
                case '/': currentToken = {DIV}; break;
                case '(': currentToken = {L_PAREN}; break;
                case ')': currentToken = {R_PAREN}; break;
                default: throw runtime_error("Invalid token");
                }
            index++;
        }        
    }

    shared_ptr<TreeNode> expr()
    {
        shared_ptr<TreeNode> node = term();
        while (currentToken.type == ADD || currentToken.type == SUB) 
        {
            Token token = currentToken;
            nextToken();
            shared_ptr<TreeNode> newNode = make_shared<TreeNode>(token);
            newNode->left = node;
            newNode->right = term();
            node = newNode;
        }
        return node;
    }

    shared_ptr<TreeNode> term()
    {
        shared_ptr<TreeNode> node = factor();
        while (currentToken.type == MUL || currentToken.type == DIV)
        {
            Token token = currentToken;
            nextToken();
            shared_ptr<TreeNode> newNode = make_shared<TreeNode>(token);
            newNode->left = node;
            newNode->right = factor();
            node = newNode;
        }
        return node;
    }

    shared_ptr<TreeNode> factor()
    {
        Token token = currentToken;
        if (token.type == NUM)
        {
            nextToken();
            return make_shared<TreeNode>(token);
        } 
        else if (token.type == L_PAREN)
        {
            nextToken();
            shared_ptr<TreeNode> node = expr();
            if (currentToken.type != R_PAREN) {
                throw runtime_error("Expected ')'");
            }
            nextToken();
            return node;
        }
        else
            throw runtime_error("Expected number or '('");
    }

public:
    Parser(const string& input) : input(input), index(0) { nextToken(); }

    shared_ptr<TreeNode> parse() { return expr(); }
};