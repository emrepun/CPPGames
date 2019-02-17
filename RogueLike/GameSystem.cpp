//
// Created by Emre HAVAN on 16.02.2019.
//

#include "GameSystem.h"


GameSystem::GameSystem(string levelFileName) {
    _player.init(1, 100, 10, 10, 0);
    _level.load(levelFileName, _player);
}

void GameSystem::playGame() {
    bool isDone = false;

    while (isDone != true) {
        _level.print();
        playerMove();
    }
}

void GameSystem::playerMove() {
    char input;
    printf("Enter a move command (w/s/a/d): ");
    cin >> input;
    //input = static_cast<char>(getch());

    _level.movePlayer(input, _player);
}