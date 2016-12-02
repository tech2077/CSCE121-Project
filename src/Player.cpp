#include "Player.h"

std::ostream& operator<<(std::ostream& os, Player& p)
/*
*/
{
    os << p.name << " " << p.score;
    return os;
}

std::istream& operator>>(std::istream& is, Player& p)
/*
*/
{
    is >> p.name;
    is >> p.score;
    return is;
}