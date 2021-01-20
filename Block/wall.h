#ifndef WALL_H
#define WALL_H

#include"Block/block.h"

//the block is a wall where the player can never be on or pass through it
class Wall: public Block {
public:
    const QString IMAGE = ":/images/wall.png";
    Wall(int row, int col, QWidget* parent);
    virtual QString getImage() const override;
};

#endif // WALL_H
