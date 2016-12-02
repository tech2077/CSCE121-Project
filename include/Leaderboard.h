#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include "Player.h"

class Leaderboard {
public:
    Leaderboard(std::string filename);
    void loadFile();
    void writeFile();
    void addPlayer(Player p);
    std::vector<Player> getPlayers() {return players;};
private:
    std::string filename;
    std::vector<Player> players;
};

#endif