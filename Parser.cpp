#include "Parser.h"

double Parser::parse_expression(std::string input)
/*
    parse expression input and return value
*/
{
    ts = Token_stream(input);
    return expression();
}

double Parser::factorial(double n)
/*
    compute factorial of n
    return 0 for values greater
    than 9 for reasonable ouput size
*/
{
    if(n > 9)
        return 0;
    
    int total = 1;

    for(int i = 1; i <= n; i++)
        total *= i;

    return total;
}

double Parser::primary()
/*
    deal with numbers and parentheses
*/
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {    
            double d = expression();
            t = ts.get();
            if (t.kind != ')') throw std::logic_error(") expected");
            return d;
        }
    case '+': // Deal with preceding signs
        return primary();
    case '-': // Deal with negative preceding sign
        return -primary();
    case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
    case 'x':            // exit case
        ts.putback('x');
        return 0;
    default: throw std::logic_error("primary expected"); // error checking
    }
}

double Parser::unary()
/*
    Deal with ! and number
*/
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '!':
            left = factorial(left); // calculate factorial
            t = ts.get();
            break;
        case '8': throw std::logic_error("term expected"); // error checking
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

double Parser::term()
/*
    deal with *, /, and %
*/
{
    double left = unary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary(); // calculate multiply from primaries around division
            t = ts.get();
            break;
        case '/': // calculate division
            {
            double d = primary(); // grab primary after divide
            if (d == 0) throw std::logic_error("divide by zero"); // error check
            left /= d; // divide
            t = ts.get();
            break;
            }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

double Parser::expression()
/*
    calculate expression in ts
    and deal with + and -
*/
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        std::cout << "Token: " << t.kind << std::endl;
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}