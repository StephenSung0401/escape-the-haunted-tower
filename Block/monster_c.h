#ifndef MONSTER_C_H
#define MONSTER_C_H

#include"Block/monster.h"

class MonsterC: public Monster {
public:
    MonsterC (int row, int col, QWidget* parent);
    virtual QString getImage() const override;
private:
    QString const IMAGE = ":/images/monster3.png";
};

#endif // MONSTER_C_H
