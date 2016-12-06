#include "Leaderboard.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

Leaderboard::Leaderboard(std::string filename)
: filename(filename) {}

void Leaderboard::loadFile()
/*
Load leaderboard from file
*/
{
    std::ifstream infile;
    infile.open(filename);
    Player p;

    // Load players from file
    while(infile >> p) {
        addPlayer(p);
    }

    infile.close();

    // Ensure players are sorted
    std::sort(players.begin(), players.end(), Player().cmp);
}
void Leaderboard::loadString(std::string in)
/*
Load leaderboard from string
*/
{
    std::stringstream buf;
    buf.str(in);
    Player p;

    // Load players from file
    while(buf >> p) {
        addPlayer(p);
    }

    // Ensure players are sorted
    std::sort(players.begin(), players.end(), Player().cmp);
}

void Leaderboard::writeFile()
/*
Write leaderboard to file
*/
{
    std::ofstream outfile;
    outfile.open(filename);

    // Sort players by score
    std::sort(players.begin(), players.end(), Player().cmp);

    int i = 0;
    for(auto p : players) {
        outfile << p << std::endl;
        if(++i >= 5) // Top five playeres
            break;
    }

    outfile.close();
}

std::string Leaderboard::writeString()
/*
Write leaderboard to file
*/
{
    std::stringstream buf;

    // Sort players by score
    std::sort(players.begin(), players.end(), Player().cmp);

    int i = 0;
    for(auto p : players) {
        buf << p << std::endl;
        if(++i >= 5) // Top five playeres
            break;
    }

    return buf.str();
}

void Leaderboard::addPlayer(Player p)
/*
Add player to leaderboard
*/
{
    players.push_back(p); // push back player onto internal vector
    std::sort(players.begin(), players.end()); // sort player
}
