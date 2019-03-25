#ifndef MONSTERICON_H
#define MONSTERICON_H

#include <QLabel>

/*simply exists because QPushButtons cannot show good image of monsters.
 * So they are set transparent, and these icons are put underneath,
 * so that monsters are shown and can be clicked at the same time.
*/
class MonsterIcon : public QLabel
{
    Q_OBJECT
public:
    MonsterIcon(int row, int col, QString path, QWidget* parent);
};

#endif // MONSTERICON_H
