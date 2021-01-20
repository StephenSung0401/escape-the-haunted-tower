#ifndef ITEM_H
#define ITEM_H

#include <QLabel>
#include <QString>

/*
   This is the Base Class for all the items
   including potions, diamonds, keys and desmond.
*/

class Item : public QLabel {
    Q_OBJECT
protected:
    int row;    // Row of the item corresponding to the map
    int col;    // Column of the item corresponding to the map
    bool picked;    // Variable to indicate if the item has been picked up

public:
    Item(QWidget* parent, int row, int col, bool picked = false);
    virtual ~Item() = default;
    virtual QString getImage() const;
    int getRow() const;
    int getCol() const;
    bool isPicked() const;
    void set_picked(bool picked);
};

#endif // ITEM_H
