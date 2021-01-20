#ifndef DIAMOND_H
#define DIAMOND_H

#include "items/Item.h"

/*
   The diamond can increase
   the power of the player.
*/

class Diamond : public Item
{
public:
    Diamond();
    Diamond(QWidget* parent, int row, int col, char type = 'A', bool picked = false);

    virtual QString getImage() const override;

    int getValue() const;
    char getType() const;

private:
    const QString ATTACK_IMAGE = ":/images/diamond-attack.png";
    const QString DEFENSE_IMAGE = ":/images/diamond-defense.png";

    int value = 3;   // The value of power increased (either Attack/Defense)
    char type;  // The type of power of the diamond ('A' for attack, 'D' for defense)
};

#endif // DIAMOND_H
