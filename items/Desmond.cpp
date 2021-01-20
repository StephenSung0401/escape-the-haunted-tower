#include "Desmond.h"

Desmond::Desmond(QWidget* parent, int row, int col, bool picked) :
    Item(parent, row, col, picked)
{}

QString Desmond::getImage() const { return DESMOND_IMAGE; }
