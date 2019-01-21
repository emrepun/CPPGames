//
// Created by Emre HAVAN on 21.01.2019.
//
#include "TicTacToeGame.h"
#include <iostream>

using namespace std;

TicTacToeGame::TicTacToeGame() {
    clearBoard();

}

void TicTacToeGame::playGame() {
    char player1 = 'X';
    char player2 = 'O';

    char currentPlayer = player1;

    bool isDone = false;

    int x, y;

    int turn = 0;

    while (!isDone) {
        printBoard();

        x = getXCoord();
        y = getYCoord();

        if (placeMarker(x, y, currentPlayer) == false) {
            cout << "That spot is occupied!\n";
        } else {
            turn++;

            if (checkForVictory(currentPlayer)) {
                cout << "The game is over! Player " << currentPlayer <<" has won!\n";
                clearBoard();
                isDone = true;
            } else if (turn == 9) {
                cout << "Its a tie game!\n";
                isDone = true;
            }
            // Switch players
            if (currentPlayer == player1) {
                currentPlayer = player2;
            } else {
                currentPlayer = player1;
            }
        }
    }
}

int TicTacToeGame::getXCoord() {
    bool isInputBad = false;
    int x;
    while (!isInputBad) {
        cout << "Enter the X coordinate: ";
        cin >> x;

        isInputBad = isValid(x);
    }

    return x - 1;

}

int TicTacToeGame::getYCoord() {
    bool isInputBad = false;
    int y;
    while (!isInputBad) {
        cout << "Enter the Y coordinate: ";
        cin >> y;

        isInputBad = isValid(y);
    }

    return y - 1;

}

bool TicTacToeGame::isValid(int input) {
        if (input < 1 || input > 3) {
            cout << "Invalid Coordinate!\n";
            return false;
        } else {
            return true;
        }
}

bool TicTacToeGame::placeMarker(int x, int y, char currentPlayer) {
    if (board[x][y] != ' ') {
        return false;
    }

    board[x][y] = currentPlayer;
    return true;
}

bool TicTacToeGame::checkForVictory(char currentPlayer) {


    for (int i = 0; i < 3; i++) {
        // Check for rows and columns
        if ((board[i][0] == currentPlayer) && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2])) {
            return true;
        } else if ((board[0][i] == currentPlayer) && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i])) {
            return true;
        //Check for diagonals
        } else if (i == 0) {
            if ((board[i][0] == currentPlayer) && (board[i][0] == board[i+1][1]) && (board[i+1][1] == board[i+2][2])) {
                return true;
            } else if ((board[i][2] == currentPlayer) && (board[i][2] == board[i+1][1]) && (board[i+1][1] == board[i+2][0])) {
                return true;
            }
        }
    }

    return false;

}

void TicTacToeGame::clearBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void TicTacToeGame::printBoard() {
    cout << endl;
    cout << " |1 2 3|\n";
    for (int i = 0; i < 3; i++) {
        cout << "---------\n";
        cout << i+1 << "|" << board[i][0] << "|" << board[i][1] << "|" << board[i][2] << "|\n";
    }
    cout << "--------\n";
}

