#ifndef PARSER_H    // guard
#define PARSER_H
#include <cstdlib>
using namespace std;
namespace Parser
{
    enum TokenType {
        ADD,SUB,MUL,DIV,L_PAREN,R_PAREN,NUM,END
    };
    struct Token {
        TokenType type;
        double value;
    };
    class Parser
}
#endif