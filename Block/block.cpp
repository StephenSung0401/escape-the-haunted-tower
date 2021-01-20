#include "Block/block.h"

Block::Block(int _row, int _col, QWidget* _parent):
    QLabel(_parent),
    row(_row),
    col(_col)
{
    setGeometry(QRect(0 + 70 * this->col, 70 + 70 * (7-this->row), 70, 70));
}

int Block::getCol() const {
    return col;
}

int Block::getRow() const {
    return row;
}
