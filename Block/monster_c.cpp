#include "Block/monster_c.h"

MonsterC::MonsterC(int _row, int _col, QWidget* parent):
    Monster(80, 35, 23, _row, _col, parent)
{}

QString MonsterC::getImage() const {
    return IMAGE;
}
