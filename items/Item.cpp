#include "items/Item.h"

Item::Item(QWidget* _parent, int row, int col, bool picked):
    QLabel(_parent),
    row(row),
    col(col),
    picked(picked)
{
    setGeometry(QRect(0 + 70 * this->col, 70+ 70 * (7-this->row), 70, 70));
};

QString Item::getImage() const { return " "; }

int Item::getRow() const { return row; }

int Item::getCol() const { return col; }

bool Item::isPicked() const { return picked; }

void Item::set_picked(bool picked) { this->picked = picked; }
