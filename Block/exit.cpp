#include "Block/exit.h"

Exit::Exit(int _row, int _col, QWidget* _parent):
    Block (_row, _col, _parent)
{}

QString Exit::getImage() const {
    return IMAGE;
}
