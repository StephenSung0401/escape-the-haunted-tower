#include "Block/door.h"

Door::Door(Color _DoorColor, int _row, int _col, QWidget* _parent):
    Block (_row, _col, _parent),
    DoorColor(_DoorColor)
{}

Color Door::getColor() const {
    return DoorColor;
}

QString Door::getImage() const {
    if(DoorColor == YELLOW){
        return YELLOW_IMAGE;
    }
    else if(DoorColor == BLUE){
        return BLUE_IMAGE;
    }
}
