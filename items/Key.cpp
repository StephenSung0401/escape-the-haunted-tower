#include "items/Key.h"

Key::Key(QWidget* _parent, int _row, int _col, Color _color, bool picked):
    Item(_parent, _row, _col, picked),
    key_color(_color)
{};

QString Key::getImage() const
{
    if (key_color == YELLOW)
        return YELLOW_IMAGE;
    else if (key_color == BLUE)
        return BLUE_IMAGE;
}

Color Key::getColor() const { return key_color; }
