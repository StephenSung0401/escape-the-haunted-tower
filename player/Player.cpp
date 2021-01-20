#include "player/Player.h"
#include <iostream>

Player::Player(QWidget* _parent, int _mapLevel, int _row, int _col, int _level, int _health, int _attack, int _defense, int _numYellowKey, int _numBlueKey):
    QLabel(_parent),
    mapLevel(_mapLevel),
    row(_row),
    col(_col),
    level(_level),
    health(_health),
    attack(_attack),
    defense(_defense),
    numYellowKey(_numYellowKey),
    numBlueKey(_numBlueKey)
{
    setGeometry(QRect(0 + 70 * this->col, 70 + 70 * (7-this->row), 70, 70));
}

/*
   Operator overloading of the assignment operator.
   Assign the Player data member from the data member of playerInfo.
   Since Player has no direct set functions, this can update the
   information of the Player in changing levels accordingly.
*/
void Player::operator=(PlayerInfo* playerInfo)
{
    row = playerInfo->getRowatLevel(mapLevel - 1);
    col = playerInfo->getColatLevel(mapLevel - 1);
    level = playerInfo->getLevel();
    health = playerInfo->getHealth();
    attack = playerInfo->getAttack();
    defense = playerInfo->getDefense();
    numYellowKey = playerInfo->getNumYellowKey();
    numBlueKey = playerInfo->getNumBlueKey();
}

QString Player::getImage() const
{
    switch(orientation)
    {
    case Up:
        return PLAYER_UP_IMAGE;
    case Down:
        return PLAYER_DOWN_IMAGE;
    case Left:
        return PLAYER_LEFT_IMAGE;
    case Right:
        return PLAYER_RIGHT_IMAGE;
    }
}

// Movement related functions
int Player::getMapLevel() const { return mapLevel; }

int Player::getRow() const { return row; }

int Player::getCol() const { return col; }

void Player::movement(Direction direction)
{
    if (direction == Up)
        --row;
    else if (direction == Down)
        ++row;
    else if (direction == Left)
        --col;
    else if (direction == Right)
        ++col;
}

Direction Player::getOrientation() const { return orientation; }

// Getter functions
int Player::getLevel() const { return level; }

int Player::getHealth() const { return health; }

int Player::getAttack() const { return attack; }

int Player::getDefense() const { return defense; }

int Player::getNumYellowKey() const { return numYellowKey; }

int Player::getNumBlueKey() const { return numBlueKey; }

// Mutator functions
void Player::upgrade()
{
    ++level;
    health_change(200);
    attack_change(3);
    defense_change(3);
}

void Player::health_change(int value) { health += value; }

void Player::attack_change(int value) { attack += value; }

void Player::defense_change(int value) { defense += value; }

void Player::setOrientation(Direction new_orientation)
{
    this->orientation = new_orientation;
    return;
}

// Key actions functions
void Player::pickKey(Color key_color) { (key_color == YELLOW)? ++numYellowKey: ++numBlueKey; }

void Player::unlockDoor(Color door_color) { (door_color == YELLOW)? --numYellowKey: --numBlueKey; }
