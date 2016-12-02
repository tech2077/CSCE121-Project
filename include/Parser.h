#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stdexcept>
#include "Token_stream.h"

class Parser {
public:
    Parser(){}; // Empty constructor
    double parse_expression(std::string input); // calculate expression
private:
    double expression(); // expression member
    double unary(); // process unary operators
    double primary(); // find and parse primaries w/ or w/o signs
    double term(); // parse and calculate terms
    double factorial(double n); // helper factorial function
    Token_stream ts; // internal token stream
};

#endif