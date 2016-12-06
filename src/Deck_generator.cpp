#include "Deck_generator.h"

// List constants
const char Deck_Generator::alphanum[] = "0123456789";
const char Deck_Generator::operators[] = "+-*/!()";
const char Deck_Generator::simple_ops[] = "+-*/";

Deck_Generator::Deck_Generator(int level)
: level(level)
/*
    Constructor for Deck_Generator
    Takes input of level and generates deck
    of that many elements
*/
{}

void Deck_Generator::generate_deck()
/*
    generates deck of numbers and operators for 
*/
{
    std::srand(std::time(0)); // seed rng

    int ops = level/2 + level%2 - 1; // number of operators
    int nums = level - ops; // number of numbers

    for(const char num : gen_random_nums(nums)) // get random numbers
        deck.push_back(std::string(1,num));

    for(const char op : gen_random_ops(ops)) // ger random operators
        deck.push_back(std::string(1,op));
}

std::vector<std::string> Deck_Generator::get_deck()
/*
    return deck
*/
{
    return deck;
}

std::string Deck_Generator::gen_random_nums(const int len)
/*
    return string of random numbers
*/
{
    std::string ret; // return string

    for (int i = 0; i < len; ++i) { // set of randum nums
        ret.push_back(alphanum[std::rand() % (sizeof(alphanum) - 1)]);
    }

    return ret; // return value
}


std::string Deck_Generator::gen_random_ops(const int len)
/*
    return string of random ops
*/
{
    std::string ret; // return 

    for (int i = 0; i < len; i++) {
        char op;
        if(i == 0) { // full op set
            op = operators[std::rand() % (sizeof(operators) - 1)]; // get random op

            switch(op){ // pair parens
                case '(':
                    ret.push_back(')');
                    i++;
                    break;
                case ')':
                    ret.push_back('(');
                    i++;
                    break;
            }
        } else // user simpler op set to make expression more likely to be solvable
            op = simple_ops[std::rand() % (sizeof(simple_ops) - 1)]; // get random op

        ret.push_back(op); // push back character
    }

    return ret; // return value
}