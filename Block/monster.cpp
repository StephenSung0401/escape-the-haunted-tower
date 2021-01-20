#include "Block/monster.h"

Monster::Monster(int _HP, int _attack, int _denfense, int _row, int _col, QWidget* parent):
    QPushButton(parent),
    HP(_HP),
    attack(_attack),
    defense(_denfense),
    row(_row),
    col(_col)
{
    setGeometry(QRect(0 + 70 * this->col, 70 + 70 * (7-this->row), 70, 70));
    setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    connect(this, &Monster::clicked, this, &Monster::clicked_handler);
}

int Monster::getRow() const {
    return col;
}

int Monster::getCol() const {
    return col;
}

int Monster::getHP() const {
    return HP;
}

int Monster::getAttack() const {
    return attack;
}

int Monster::getDefense() const {
    return defense;
}

//emit a signal to tell the coordinates of the monster clicked
void Monster::clicked_handler()
{
    emit clicked_with_pos(this->row, this->col);
}
