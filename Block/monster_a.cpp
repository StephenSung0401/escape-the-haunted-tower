#include "Block/monster_a.h"

MonsterA::MonsterA(int _row, int _col, QWidget* parent):
    Monster(15, 16, 8, _row, _col, parent)
{}

QString MonsterA::getImage() const {
    return IMAGE;
}
