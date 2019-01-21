//
// Created by Emre HAVAN on 21.01.2019.
//

#ifndef TICTACTOE_TICTACTOEGAME_H
#define TICTACTOE_TICTACTOEGAME_H


class TicTacToeGame {
public:
    TicTacToeGame();

    void playGame();


private:

    int getXCoord();
    int getYCoord();
    bool isValid(int input);

    bool placeMarker(int x, int y, char currentPlayer);

    bool checkForVictory(char currentPlayer);


    void clearBoard();
    void printBoard();
    char board[3][3];

};


#endif //TICTACTOE_TICTACTOEGAME_H
