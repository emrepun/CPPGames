#include <iostream>
#include "TicTacToeGame.h"

using namespace std;

int main() {

    char input;
    bool isCompleted = false;

    TicTacToeGame game;

    while (!isCompleted) {
        game.playGame();
        cout << "Would you like to play again? (Y/N)";
        cin >> input;

        if (input == 'N' || input == 'n') {
            isCompleted = true;
        }
    }
}

