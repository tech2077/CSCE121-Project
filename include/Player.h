#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player {
public:
    Player() {};
    Player(std::string name, double score): name(name), score(score){};
    void setScore(double score){ this->score = score; };
    double getScore(){ return this->score; };
    bool operator==(Player b) {return this->getScore() == b.getScore();} ;
    bool operator<(Player b) {return this->getScore() < b.getScore();} ;
    bool operator>(Player b) {return this->getScore() > b.getScore();} ;
    static bool cmp(Player a, Player b) {return a.getScore() > b.getScore();} ;
private:
    friend std::ostream& operator<<(std::ostream& os, Player& p);
    friend std::istream& operator>>(std::istream& is, Player& p);
    std::string name;
    double score;
};

#endif