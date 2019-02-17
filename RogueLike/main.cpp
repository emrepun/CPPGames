#include <iostream>
#include <cstdlib>
#include <string>
#include <curses.h>

#include "GameSystem.h"

using namespace std;

int main() {

    GameSystem gameSystem("level1.txt");
    gameSystem.playGame();

    return 0;
}