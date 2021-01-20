#include "Block/stair.h"

Stair::Stair(enum StairDirection _StairDirection, int _row, int _col, QWidget* _parent):
    Block (_row, _col, _parent),
    StairDirection(_StairDirection)
{}

QString Stair::getImage() const {
    if(StairDirection == UPSTAIR) return UPSTAIR_IMAGE;
    else if(StairDirection == DOWNSTAIR) return DOWNSTAIR_IMAGE;
}

//to tell whether it is stair for going upstairs or downstairs
StairDirection Stair::getStairDirection() const {
    return StairDirection;
}
