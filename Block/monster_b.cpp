#include "Block/monster_b.h"

MonsterB::MonsterB(int _row, int _col, QWidget* parent):
    Monster(35, 26, 14, _row, _col, parent)
{}

QString MonsterB::getImage() const {
    return IMAGE;
}
