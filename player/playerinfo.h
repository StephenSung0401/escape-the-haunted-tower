#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "block/door_color.h"

/*
    PlayerInfo stores the information of the player,
    which is managed by the levelManager.
    It is used to store and retrieve the updated information
    when the game level is changed.
*/

class PlayerInfo
{
public:
    PlayerInfo(int _level, int _health, int _attack, int _defense, int _numYellowKey, int _numBlueKey);

    // Getter functions
    int getRowatLevel(int level) const;
    int getColatLevel(int level) const;
    int getLevel() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;
    int getNumYellowKey() const;
    int getNumBlueKey() const;

    // Mutator functions
    void setRowatLevel(int level, int value);
    void setColatLevel(int level, int value);
    void setLevel(int value);
    void setHealth(int value);
    void setAttack(int value);
    void setDefense(int value);

    // Key actions functions
    void setNumOfKey(Color key_color, int value);

private:
    int mapCoordinates[3][2];   // 1st coordinate = mapLevel, 2nd coordinate = row([0]) / col([1])
    int level;
    int health;
    int attack;
    int defense;
    int numYellowKey;
    int numBlueKey;
};

#endif // PLAYERINFO_H
