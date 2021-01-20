#ifndef STAIR_H
#define STAIR_H

#include "Block/block.h"

//the block is a stair, if it is UPSTAIR, the player will go back to the previous floor,
//if it is DOWNSTAIR, the player will go down one floor
class Stair: public Block {
public:
    Stair(StairDirection _StairDirection, int row, int col, QWidget* parent);
    virtual QString getImage() const override;
    StairDirection getStairDirection() const;

private:
    const QString UPSTAIR_IMAGE = ":/images/stair-upright.png";
    const QString DOWNSTAIR_IMAGE = ":/images/stair-downleft.png";
    StairDirection StairDirection;
};


#endif // STAIR_H
