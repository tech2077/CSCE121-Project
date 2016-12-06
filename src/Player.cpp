#include "Player.h"

std::ostream& operator<<(std::ostream& os, Player& p)
/*
    Override stream out operator in order to easily write to file
*/
{
    os << p.name << " " << p.score; // write out formatted 
    return os; // return stream for stacking
}

std::istream& operator>>(std::istream& is, Player& p)
/*
    Override stream in operator in order to easily read from file
*/
{
    is >> p.name; // read in name
    is >> p.score; // read in score
    return is; // return stream for stacking
}