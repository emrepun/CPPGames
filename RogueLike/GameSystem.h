//
// Created by Emre HAVAN on 16.02.2019.
//

#include <iostream>
#include "Player.h"
#include "Level.h"
#include <string>
#include <curses.h>

using namespace std;

class GameSystem {
public:
    GameSystem(string levelFileName);

    void playGame();
    void playerMove();
private:
    Player _player;
    Level _level;
};

