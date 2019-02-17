//
// Created by Emre HAVAN on 16.02.2019.
//

#include "Level.h"
#include <fstream>
#include <iostream>
#include <string>

Level::Level() {

}

void Level::load(string fileName, Player &player) {

    // Load level

    ifstream file;

    file.open(fileName);

    if (file.fail()) {
        perror(fileName.c_str());
        exit(1);
    }

    string line;

    while (getline(file, line)) {
        _levelData.push_back(line);
    }

    file.close();

    // Process level
    setPlayerPosition(player);
}

void Level::setPlayerPosition(Player &player) {
    char tile;

    for (int i = 0; i < _levelData.size(); i++) {
        for (int j = 0; j < _levelData[i].size(); j++) {
            tile = _levelData[i][j];

            switch (tile) {
                case '@':
                    player.setPosition(i, j);
                    break;
                default:
                    break;
            }
        }
    }
}

void Level::print() {

    cout << string(10, '\n');

    for (int i = 0; i < _levelData.size(); i++) {
        printf("%s\n", _levelData[i].c_str());
    }

    printf("\n");
}

void Level::movePlayer(char input, Player &player) {
    int playerX;
    int playerY;

    player.getPosition(playerX, playerY); //gets and sets equal to

    switch (input) {
        case 'w': // up
        case 'W':
            processPlayerMove(player, playerX, playerY - 1);
            break;
        case 's': // down
        case 'S':
            processPlayerMove(player, playerX, playerY + 1);
            break;
        case 'a': // left
        case 'A':
            processPlayerMove(player, playerX - 1, playerY);
            break;
        case 'd': // right
        case 'D':
            processPlayerMove(player, playerX + 1, playerY);
            break;
        default:
            printf("INVALID UNPUT!\n");
            break;
    }
}

char Level::getTile(int x, int y) {
    return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
    _levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
    int playerX;
    int playerY;
    player.getPosition(playerX, playerY);

    char moveTile = getTile(targetX, targetY);

    switch (moveTile) {
        case '#':
            printf("You ran into a wall!\n");
            break;
        case '.':
            player.setPosition(targetX, targetY);
            setTile(playerX, playerY, '.');
            setTile(targetX, targetY, '@');
    }
}