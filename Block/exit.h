#ifndef EXIT_H
#define EXIT_H

#include "Block/block.h"

//there are two kinds of doors whcih requires corresponding keys to open,
//otherwise the player cannot go through it
class Exit: public Block {
public:
    Exit(int row, int col, QWidget* parent);
    virtual QString getImage() const override;

private:
    const QString IMAGE = ":/images/exit.png";
};

#endif // EXIT_H
