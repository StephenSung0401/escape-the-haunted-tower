#include "items/Diamond.h"

Diamond::Diamond(QWidget* _parent, int row, int col, char type, bool picked):
    Item(_parent, row, col, picked),
    type(type)
{};

QString Diamond::getImage() const
{
    if (type == 'A')
        return ATTACK_IMAGE;
    else if (type == 'D')
        return DEFENSE_IMAGE;
}

int Diamond::getValue() const { return value; }

char Diamond::getType() const { return type; }
