#ifndef DOOR_H
#define DOOR_H

#include "Block/block.h"

//there are two kinds of doors whcih requires corresponding keys to open,
//otherwise the player cannot go through it
class Door: public Block {
public:
    Door(Color DoorColor, int row, int col, QWidget* parent);
    virtual QString getImage() const override;
    Color getColor() const;

private:
    const QString BLUE_IMAGE = ":/images/door-blue.png";
    const QString YELLOW_IMAGE = ":/images/door-yellow.png";
    Color DoorColor;
};

#endif // DOOR_H
