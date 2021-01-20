#include "items/Potion.h"

Potion::Potion(QWidget* _parent, int row, int col, char type, bool picked) :
    Item(_parent, row, col, picked),
    type(type)
{
    if (type == 'S')
        heal = 100;
    else
        heal = 250;
};

QString Potion::getImage() const
{
    if (type == 'S')
        return SMALL_IMAGE;
    else if (type == 'L')
        return LARGE_IMAGE;
}

int Potion::get_heal() const { return heal; }

char Potion::get_type() const { return type; }
