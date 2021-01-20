#ifndef MONSTER_A_H
#define MONSTER_A_H

#include"Block/monster.h"

class MonsterA: public Monster {
public:
    MonsterA (int row, int col, QWidget* parent);
    virtual QString getImage() const override;
private:
    QString const IMAGE = ":/images/monster1.png";
};

#endif // MONSTER_A_H
