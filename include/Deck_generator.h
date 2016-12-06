#ifndef DECK_GENERATOR_H
#define DECK_GENERATOR_H

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Deck_Generator {
public:
    Deck_Generator(int level);
    void generate_deck();
    std::vector<std::string> get_deck();
    static const char alphanum[];
    static const char operators[];
    static const char simple_ops[];
private:
    int level;
    std::vector<std::string> deck;
    static std::string gen_random_nums(const int len);
    static std::string gen_random_ops(const int len);
};

#endif