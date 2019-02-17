//
// Created by Emre HAVAN on 17.02.2019.
//
#include <string>
#include <iostream>

using namespace std;

class Enemy {
public:
    Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);

    void setPosition(int x, int y);

    void getPosition(int &x, int &y);
    string getName();
    char getTile();

    int attack();
    int takeDamage(int attack);

    //Gets AI move command.
    char getMove(int playerX, int playerY);

private:
    string _name;
    char _tile;

    int _level;
    int _attack;
    int _defense;
    int _health;
    int _experienceValue;

    //maybe add possible dropable items?

    //Coordinates:
    int _x;
    int _y;
};

