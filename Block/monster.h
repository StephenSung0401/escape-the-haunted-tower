#ifndef MONSTER_H
#define MONSTER_H

#include <QPushButton>
#include <QString>

//there is a monster on the block, the player can either kill it to make it disapear,
//or make a detour to pass it if possible
//if the monster's defense is higher than the player's attack,
//which means that the player can never defeat the monster,
//than the player cannot kill the monster
class Monster: public QPushButton {
    Q_OBJECT
public:
    Monster(int HP, int attack, int defense, int row, int col, QWidget* parent);
    virtual ~Monster() = default;
    virtual QString getImage() const = 0;
    int getRow() const;
    int getCol() const;

    int getHP() const;
    int getAttack() const;
    int getDefense() const;

protected:
    const int HP;
    const int attack;
    const int defense;
    int row, col;

signals:
    void clicked_with_pos(int row, int col);

private slots:
    void clicked_handler();
};

#endif // MONSTER_H
