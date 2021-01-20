#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QString>
#include "Block/door_color.h"
#include "Block/stair_direction.h"

//the block include wall, door and stair
class Block : public QLabel {
    Q_OBJECT
public:
    Block(int row, int col, QWidget* parent);
    virtual ~Block() = default;
    virtual QString getImage() const = 0;
    int getRow() const;
    int getCol() const;

protected:
    int row, col;
};

#endif // BLOCK_H
