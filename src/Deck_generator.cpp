#include "Deck_Generator.h"

Deck_Generator::Deck_Generator(int level)
: level(level)
/*
    Constructor for Deck_Generator
    Takes input of level and generates deck
    of that many elements
*/
{
}

void Deck_Generator::generate_deck()
/*
    generates deck of numbers and operators for 
*/
{

    std::srand(std::time(0));
    int ops = level/2 + level%2 - 1;
    int nums = level - ops;
    for(int i = 0; i < ops; i++)
    {
        deck.push_back(gen_random_ops(1));
    }
    for(int i = 0; i < nums; i++)
    {
        deck.push_back(gen_random_nums(1));
    }
    randomize();
}

std::vector<std::string> Deck_Generator::get_deck()
/*
    return deck
*/
{
    return deck;
}

void Deck_Generator::randomize()
/*
    randomize generated deck
*/
{

}

std::string Deck_Generator::gen_random_nums(const int len) {
    static const char alphanum[] = "0123456789";

    std::string ret;

    for (int i = 0; i < len; ++i) {
        ret.push_back(alphanum[std::rand() % (sizeof(alphanum) - 1)]);
    }

    return ret;
}


std::string Deck_Generator::gen_random_ops(const int len) {
    static const char alphanum[] = "+-*/!";

    std::string ret;

    for (int i = 0; i < len; ++i) {
        ret.push_back(alphanum[std::rand() % (sizeof(alphanum) - 1)]);
    }

    return ret;
}