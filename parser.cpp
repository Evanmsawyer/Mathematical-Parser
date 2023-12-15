#include "parser.h"

using namespace std;

namespace parser
{
    
    Parser::Parser(const string& input) : input(input), index(0), currentToken(END)
    {
        nextToken(); 
    }

    shared_ptr<TreeNode> Parser::parse()
    {
        return expr();
    }

    void Parser::nextToken()
    {
        while (index < input.length() && isspace(input[index]))
            index++;

        if (index == input.length()) {
            currentToken = END;
            return;
        }

        char curr = input[index];
        if (isdigit(curr) || curr == '.') { // Check for a digit or a decimal point
            string number;
            bool decimalPointFound = false;

            while (index < input.length() && (isdigit(input[index]) || (input[index] == '.' && !decimalPointFound))) {
                if (input[index] == '.') {
                    decimalPointFound = true; // Mark that we found a decimal point
                }
                number += input[index++];
            }

            currentToken = {NUM, stod(number)}; 
        }else 
        {
            char curr = input[index];
        switch (curr) {
            case '+': 
                currentToken = Token(ADD); 
                break;
            case '-': 
                currentToken = Token(SUB); 
                break;
            case '*': 
                currentToken = Token(MUL); 
                break;
            case '/': 
                currentToken = Token(DIV); 
                break;
            case '^': 
                currentToken = Token(EXP); 
                break;
            case '(': 
                currentToken = Token(L_PAREN); 
                break;
            case ')': 
                currentToken = Token(R_PAREN); 
                break;
            // Handle other cases if needed
            default: 
                throw runtime_error("Invalid token");
        }
        index++;
        }        
    }

    shared_ptr<TreeNode> Parser::expr()
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

    shared_ptr<TreeNode> Parser::term()
    {
        shared_ptr<TreeNode> node = exponent();

        while (currentToken.type == MUL || currentToken.type == DIV)
        {
            Token token = currentToken;
            nextToken();
            shared_ptr<TreeNode> newNode = make_shared<TreeNode>(token, node, exponent());
            node = newNode;
        }

        return node;
    }

    shared_ptr<TreeNode> Parser::exponent()
    {
        shared_ptr<TreeNode> base = factor();

        while (currentToken.type == EXP)
        {
            Token token = currentToken;
            nextToken();
            shared_ptr<TreeNode> exponentNode = exponent();
            base = make_shared<TreeNode>(token, base, exponentNode);
        }

        return base;
    }

    shared_ptr<TreeNode> Parser::factor()
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
            if (currentToken.type != R_PAREN) 
            {
                throw runtime_error("Expected ')'");
            }
            nextToken();
            return node;
        }
        else
        {
            throw runtime_error("Expected number or '('");
        }
    }  
}