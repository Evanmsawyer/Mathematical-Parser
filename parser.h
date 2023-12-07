#ifndef PARSER_H    // guard
#define PARSER_H

#include <cstdlib>
#include <string>
#include <memory>
#include <stdexcept>

using namespace std;

namespace parser
{
    enum TokenType
    {
        ADD,SUB,MUL,DIV,L_PAREN,R_PAREN,NUM,END
    };

    struct Token
    {
        TokenType type;
        double value{0.0};
    };

    /**
    * @brief a node in the expression tree. has a token and pointers to its left and right children
    */
    struct TreeNode
    {
        // members
        Token token;
        shared_ptr<TreeNode> left{nullptr}, right{nullptr};
        
        // Constructor for the TreeNode struct
        TreeNode(Token token);
    };

    class Parser
    {
    private:

        string input;
        size_t index;
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
        void nextToken();

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
        shared_ptr<TreeNode> expr();

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
        shared_ptr<TreeNode> term();

        /**
         * @brief parses a factor, works as follows:
         *     1. store the current token in token
         *     2.  a.) if the current token is a number, call nextToken() and return a new node with token as the token
         *         b.) if the current token is a left parenthesis, call nextToken(), set node to expr(), and call nextToken() again to account for the right parenthesis
         * 
         * @return the node, which is the root of the factor tree
         * @throw std::runtime_error if the current token is not a number or left parenthesis
        */
        shared_ptr<TreeNode> factor();

    public:
        Parser(const string& input);
        shared_ptr<TreeNode> parse();
    };
}
#endif