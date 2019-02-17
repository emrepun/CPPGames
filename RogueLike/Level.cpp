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
    setInitialPlayerPosition(player);
}

void Level::setInitialPlayerPosition(Player &player) {
    char tile;

    for (int i = 0; i < _levelData.size(); i++) {
        for (int j = 0; j < _levelData[i].size(); j++) {
            tile = _levelData[i][j];

            switch (tile) {
                case '@': //Player
                    player.setPosition(i, j);
                    break;
                case 'S': //Snake
                    _enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
                    _enemies.back().setPosition(j,i);
                    break;
                case 'g': //goblin
                    _enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
                    _enemies.back().setPosition(j,i);
                    break;
                case 'O': //Oger
                    _enemies.push_back(Enemy("Oger", tile, 4, 20, 20, 200, 500));
                    _enemies.back().setPosition(j,i);
                    break;
                case 'B':
                    _enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
                    _enemies.back().setPosition(j,i);
                    break;
                case 'D': //Dragon
                    _enemies.push_back(Enemy("Dragon", tile, 100, 2000, 20000, 2000, 1000000));
                    _enemies.back().setPosition(j,i);
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

void Level::updateEnemies(Player &player) {
    char aiMove;
    int playerX;
    int playerY;

    int enemyX;
    int enemyY;

    player.getPosition(playerX, playerY);

    for (int i = 0; i < _enemies.size(); i++) {
        aiMove = _enemies[i].getMove(playerX, playerY);
        _enemies[i].getPosition(enemyX, enemyY);
        switch (aiMove) {
            case 'w': // up
                processEnemyMove(player, i, enemyX, enemyY - 1);
                break;
            case 's': // down
                processEnemyMove(player, i, enemyX, enemyY + 1);
                break;
            case 'a': // left
                processEnemyMove(player, i, enemyX - 1, enemyY);
                break;
            case 'd': // right
                processEnemyMove(player, i, enemyX + 1, enemyY);
                break;
        }
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
            break;
        default: //gonna be a monster
            battleMonster(player, targetX, targetY);
            break;

    }
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
    int playerX;
    int playerY;

    int enemyX;
    int enemyY;

    _enemies[enemyIndex].getPosition(enemyX, enemyY);
    player.getPosition(playerX, playerY);

    char moveTile = getTile(targetX, targetY);

    switch (moveTile) {
        case '#':
            printf("You ran into a wall!\n");
            break;
        case '.':
            _enemies[enemyIndex].setPosition(targetX, targetY);
            setTile(enemyX, enemyY, '.');
            setTile(targetX, targetY, _enemies[enemyIndex].getTile());
            break;
        case '@':
            battleMonster(player, enemyX, enemyY);
            break;
        default: //gonna be a monster
            break;

    }
}

void Level::battleMonster(Player &player, int targetX, int targetY) {
    int enemyX;
    int enemyY;
    string enemyName;

    int playerX;
    int playerY;

    player.getPosition(playerX, playerY);

    int attackRoll;
    int attackResult;

    for (int i = 0; i < _enemies.size(); i++) {
        _enemies[i].getPosition(enemyX, enemyY);
        enemyName = _enemies[i].getName();

        if (targetX == enemyX && targetY == enemyY) {
            // Battle!
            attackRoll = player.attack();
            printf("\nPlayer attacked %s with a roll of %i\n", enemyName.c_str(), attackRoll);
            attackResult = _enemies[i].takeDamage(attackRoll);

            if (attackResult != 0) {
                setTile(targetX, targetY, '.');
                print();
                printf("Monster died");

                _enemies[i] = _enemies.back(); // removing hack
                _enemies.pop_back(); //removed
                i--; // so we dont skip

                player.addExperience(attackResult);
                return;
            }

            //Monster turn

            attackRoll = _enemies[i].attack();
            printf("%s attacked player with a roll of %i\n", enemyName.c_str(), attackRoll);
            attackResult = player.takeDamage(attackRoll);

            if (attackResult != 0) {
                setTile(playerX, playerY, 'x');
                print();
                printf("You died!\n");

                exit(0); // Game Over
            }

            return;
        }
    }
}