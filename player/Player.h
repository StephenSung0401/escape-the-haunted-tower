#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QString>
#include <QKeyEvent>

#include "block/door_color.h"
#include "player/playerinfo.h"

enum Direction { Up, Down, Left, Right };

/*
    The player is the main character
    controlled by the user.
*/

class Player : public QLabel
{
    Q_OBJECT
public:
    Player();
    Player(QWidget* parent, int mapLevel, int row, int col, int level = 1, int health = 100, int attack = 10, int defense = 10,
           int numYellowKey = 0, int numBlueKey = 0);

    QString getImage() const;

    // Operator Overloading
    void operator=(PlayerInfo* playerInfo);  // To update with the newest information of player at certain level

    // Movement related functions
    int getMapLevel() const;
    int getRow() const;
    int getCol() const;
    void movement(Direction direction);

    // Getter functions
    int getLevel() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;
    int getNumYellowKey() const;
    int getNumBlueKey() const;
    Direction getOrientation() const;

    // Mutator functions
    void upgrade(); // Increase the level of the player
    void health_change(int value);
    void attack_change(int value);
    void defense_change(int value);
    void setOrientation(Direction new_orientation);

    // Key actions functions
    void pickKey(Color key_color); // Pick up a key from the map
    void unlockDoor(Color door_color);    // Use a key to unlock the corresponding colored door

private:
    const QString PLAYER_UP_IMAGE = ":/images/player-up.png";
    const QString PLAYER_DOWN_IMAGE = ":/images/player-down.png";
    const QString PLAYER_LEFT_IMAGE = ":/images/player-left.png";
    const QString PLAYER_RIGHT_IMAGE = ":/images/player-right.png";

    // Position and orientation of the player
    int mapLevel;   // The level of the map that player currently is in
    int row;    // The row of player currently in the map
    int col;    // The column of player currently in the map
    Direction orientation = Direction::Up;  // The direction that the player is facing

    // The attributes of the player
    int level;      // The player's level can be upgraded through going to the next level, also affect the other abilities
    int health;     // The HP of the player
    int attack;     // The attack point indicates the damages can be given
    int defense;    // The defense point indicates how much damages can be reduced from monsters' attack
    int numYellowKey;   // The number of yellow keys that player holds
    int numBlueKey; // The number of blue keys that player holds

};

#endif // PLAYER_H
