#ifndef MONSTER_B_H
#define MONSTER_B_H

#include"Block/monster.h"

class MonsterB: public Monster {
public:
    MonsterB (int row, int col, QWidget* parent);
    virtual QString getImage() const override;
private:
    QString const IMAGE = ":/images/monster2.png";
};

#endif // MONSTER_B_H
