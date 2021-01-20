#ifndef DESMOND_H
#define DESMOND_H

#include "items/Item.h"

/*
    Desmond is the character to be rescued.
    Inheritance from Item class is to allow for
    the pick up settings.
    Rescue is optional, and will cause the ending
    to be different.
*/

class Desmond : public Item
{
public:
    Desmond();
    Desmond(QWidget* parent, int row, int col, bool picked = false);

    virtual QString getImage() const override;

private:
    const QString DESMOND_IMAGE = ":/images/desmond.png";
};

#endif // DESMOND_H
