# Mathematical-Parser

## Components

There are four main parts to this parser: The REPL shell, the lexer/tokenizer, the parser itself, and the interpreter. The role/implementation of each of these parts is
explained in detail in the corresponding section below.

### REPL Shell

The REPL (short for read evaluate print loop) shell is responsible for taking in user input, sending it to the lexer/tokenizer, sending the result from the lexer/
tokenizer to the parser, sending the results from the parser to the interpreter, then printing the results of the interpreter for the user. It is also responsible for
catching and printing any exceptions raised by the other components, whether those be caused by syntax errors in user input, or bugs.

The simplified logic loop for the REPL shell is this:
1. Read from user input
2. Send user input to lexer
3. Send output of lexer to parser
4. Send output of parser to interpreter
5. Send output of interpreter to output
6. Repeat

### Lexer/Tokenizer

The lexer is responsible for splitting its input into a list of discrete tokens to be parsed by the parser. In this process, it will remove any whitespace and raise
an exception if the token is invalid.

### Parser

The parser works based on a set of grammatical rules to build a parse tree that will then be sent to the interpreter for evaluation. The parser works by implementing
the following context-free grammar rules:
```
command := expr
expr := term {add term}
add := + | -
term := factor {mul factor}
mul := * | /
factor := (expr) | number
number := digit {digit}
digit := 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```
For this grammar, command is the start variable, and expressions in curly brackets indicate that an arbitrary amount of that expression can be appended, and the rule would
still be valid.

### Interpreter

The interpreter takes the parse tree from the parser as input, and evaluates it. More on this once I know how we're implementing it.
