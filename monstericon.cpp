#include "monstericon.h"

MonsterIcon::MonsterIcon(int row, int col, QString path, QWidget* parent):
    QLabel{parent}
{
    setGeometry(QRect(0 + 70 * col, 70 + 70 * (7-row), 70, 70));
    setPixmap(path);
    show();
}
