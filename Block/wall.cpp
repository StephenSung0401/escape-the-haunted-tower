#include "Block/wall.h"

Wall::Wall(int _row, int _col, QWidget* _parent):
    Block(_row, _col, _parent)
{}

QString Wall::getImage() const {
    return IMAGE;
}
