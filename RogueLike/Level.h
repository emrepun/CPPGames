//
// Created by Emre HAVAN on 16.02.2019.
//

#include <vector>
#include <string>
#include "Player.h"

using namespace std;

class Level {
public:
    Level();

    void setPlayerPosition(Player &player);
    void load(string fileName, Player &player);
    void print();
    void movePlayer(char input, Player &player);
    char getTile(int x, int y);
    void setTile(int x, int y, char tile);

private:
    void processPlayerMove(Player &player, int targetX, int targetY);

private:
    vector<string> _levelData;

};

