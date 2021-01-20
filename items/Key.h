#ifndef KEY_H
#define KEY_H

#include "items/Item.h"
#include "Block/door_color.h"

/*
    The key can open the door.
    The color of the key and the door
    needs to be matched.
*/

class Key : public Item
{
public:
    Key();
    Key(QWidget* parent, int row, int col, Color _color, bool picked = false);

    virtual QString getImage() const override;

    Color getColor() const;

private:
    const QString YELLOW_IMAGE = ":/images/key-yellow.png";
    const QString BLUE_IMAGE = ":/images/key-blue.png";

    Color key_color;  // The color of the key
};

#endif // KEY_H
