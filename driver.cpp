#include <iostream>
#include <cctype>
#include <cmath>
#include "parser.h"

using namespace parser;
using namespace std;

#define START_MESSAGE "Enter an expression to evaluate or 'q' to quit\n"
#define PROMPT ">>> "

/**
 * @brief evaluates an expression tree, works as follows:
 *    1. if node is null, return 0
 *    2. if the token of node is a number, return the value of the token
 *    3. if it is not a number, it is an operator, so we evaluate the left and right children by recursively calling evaluateTree()
 *    4. depending on the operator, we return the sum, difference, product, or quotient of the left and right children
*/
double evaluateTree(const shared_ptr<TreeNode>& node)
{
    if (!node)
        return 0;

    if (node->token.type == NUM)
        return node->token.value;
    else
    {

        double left = 0;
        if (node->left)
            left = evaluateTree(node->left);

        double right = 0;
        if (node->right)
            right = evaluateTree(node->right);
        
        switch (node->token.type)
        {
            case ADD: return left + right;
            case SUB: return left - right;
            case MUL: return left * right;
            case DIV: 
                if (right == 0) 
                    throw runtime_error("Division by zero");
                return left / right;
            case EXP:
                return pow(left, right); // handle expo
            default: throw runtime_error("Unrecognized command");
        }
    }
}
/**
 * @brief wraps the entire process of parsing and evaluating an expression
 * @param input the expression to evaluate
 * @return the result of the expression
 * @throw std::runtime_error if the expression is invalid 
 */
double evaluate(const string& input)
{
    try
    {
        Parser parser(input);
        shared_ptr<TreeNode> root = parser.parse();
        return evaluateTree(root);
    }
    catch (const exception& e)
    {
        throw runtime_error("Invalid expression (" + string(e.what()) + ")"); 
    }
}
/**
 * @brief a shell for the user to enter expressions to evaluate
 */
void shell()
{
    printf(START_MESSAGE);
    while (true)
    {
        string input;
        cout << PROMPT;
        getline(cin, input);
        if (input == "q")
            break;
        else if (input == "") 
            continue;
        else
        {
            try
            {
                double result = evaluate(input);
                cout << result << endl;
            }
            catch (const exception& e)
            {
                cout << e.what() << endl;
            }
        }
    }
}
   
int main() {
    shell();
    return 0;
}


