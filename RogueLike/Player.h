//
// Created by Emre HAVAN on 16.02.2019.
//

#ifndef ROGUELIKE_PLAYER_H
#define ROGUELIKE_PLAYER_H


class Player {
public:
    Player();
    void init(int level, int health, int attack, int defense, int experience);

    //Setters
    void setPosition(int x, int y);

    //Getters
    void getPosition(int &x, int &y);

private:
    //Properties:
    int _level;
    int _health;
    int _attack;
    int _defense;
    int _experience;

    //Coordinates:
    int _x;
    int _y;
};


#endif //ROGUELIKE_PLAYER_H
