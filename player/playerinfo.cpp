#include "playerinfo.h"
#include <iostream>

PlayerInfo::PlayerInfo(int _level, int _health, int _attack, int _defense, int _numYellowKey, int _numBlueKey):
    level(_level),
    health(_health),
    attack(_attack),
    defense(_defense),
    numYellowKey(_numYellowKey),
    numBlueKey(_numBlueKey)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            mapCoordinates[i][j] = 7;   // A random number for initialization, no effects for in-game process
}

int PlayerInfo::getRowatLevel(int level) const { return mapCoordinates[level][0]; }

int PlayerInfo::getColatLevel(int level) const { return mapCoordinates[level][1]; }

int PlayerInfo::getLevel() const { return level; }

int PlayerInfo::getHealth() const { return health; }

int PlayerInfo::getAttack() const { return attack; }

int PlayerInfo::getDefense() const { return defense; }

int PlayerInfo::getNumYellowKey() const { return numYellowKey; }

int PlayerInfo::getNumBlueKey() const { return numBlueKey; }

void PlayerInfo::setRowatLevel(int level, int value) { mapCoordinates[level][0] = value; }

void PlayerInfo::setColatLevel(int level, int value) { mapCoordinates[level][1] = value; }

void PlayerInfo::setLevel(int value) { level = value; }

void PlayerInfo::setHealth(int value) { health = value; }

void PlayerInfo::setAttack(int value) { attack = value; }

void PlayerInfo::setDefense(int value) { defense = value; }

void PlayerInfo::setNumOfKey(Color key_color, int value) { key_color == YELLOW ? numYellowKey = value : numBlueKey = value; }


