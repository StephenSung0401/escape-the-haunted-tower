#ifndef POTION_H
#define POTION_H

#include "items/Item.h"

/*
   The potion can heal the player
   upon picking up.
*/

class Potion : public Item
{
public:
    Potion();
    Potion(QWidget* parent, int row, int col, char type = 'S', bool picked = false);

    virtual QString getImage() const override;

    int get_heal() const;
    char get_type() const;

private:
    const QString SMALL_IMAGE = ":/images/potion-blue.png";
    const QString LARGE_IMAGE = ":/images/potion-red.png";

    int heal;   // The amount of HP the potion can heal, based on the type of potion
    char type;  // The type of potion, either 'S'(Blue) or 'L'(Red)

};

#endif // POTION_H
